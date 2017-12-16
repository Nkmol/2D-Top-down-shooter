#include <Rifle.h>
#include "Level.h"
#include "Rifle.h"
#include "Handgun.h"
#include "Shotgun.h"
#include "Bullet.h"
#include "Player.h"
#include "Config.h"
#include "InputManager.h"
#include "EnemyBase.h"
#include "Wave.h"
#include "Event.h"
#include "../Engine/AnimationManager.h"
#include "ExplosionFactory.h"

Level::Level(const int level, const ::std::string savedGame) :
        _level(level),
        _levelSpeed(1),
        _savedGame(savedGame),
        inputManager{InputManager::Instance()} {
    Init();
    Level::_explosion = {};
}

void Level::Init() {

    LoadLevel();

    MapManager::Instance().Init(_map);

    LoadPlayer();

    _waveController.Init(_waves, _player, _npcs);

    PhysicsManager::Instance().setStaticObjects();
    PhysicsManager::Instance().setMoveableObjects(&_objsNoEnemies);
}

void Level::LoadLevel() {
    std::ifstream i;
    i.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        i.open(config::levels[_level - 1]);
    }
    catch (const ifstream::failure &) {
        cout << "Exception opening/reading file" << endl;
        return;
    }
    nlohmann::json j;
    i >> j;

    from_json(j, *this);
    i.close();
}

void Level::LoadPlayer() {
    auto player = make_shared<Player>("soldier", config::width / 2, config::height / 2 + 10);
    player->addWeapons({Handgun(), Rifle(), Shotgun()});
    player->changeWeapon(0);

    _player = player;

    if (!_savedGame.empty()) {
        std::ifstream i;
        i.exceptions(ifstream::failbit | ifstream::badbit);
        try {
            i.open(_savedGame);
        }
        catch (const ifstream::failure &) {
            cout << "Exception opening/reading file" << endl;
            return;
        }
        nlohmann::json j;
        i >> j;

        from_json(j, *_player.get());
        i.close();
    }
    _objsNoEnemies.emplace_back(_player);
}

void Level::HandleEvents(Event event) {

    this->HandleMouseEvents(event);
    this->HandleKeyboardEvents(event);

    Point direction = inputManager.GetDirection(event);
    int angle = inputManager.CalculateMouseAngle(*_player);

    _player->SetAngle(angle);
    _player->Move(direction);
}

void Level::HandleMouseEvents(Event &event) {
    if (inputManager.IsMouseMoved(event)) {
        // RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
        int angle = inputManager.RecalculateMouseAngle(*_player);

        // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
        _player->SetAngle(angle);
    }

    if (inputManager.IsMouseClicked(event)) {
        _player->ChangeState("shoot");
        auto bullet = make_shared<Bullet>(_player->shoot()); // returns a bullet
        _objsNoEnemies.emplace_back(bullet);
    }
}

void Level::HandleKeyboardEvents(Event &event) {
    int key = 0;

    if (inputManager.IsNumericKeyPressed(event, key)) {
        _player->changeWeapon(key - 1);
    }

    if (inputManager.IsKeyDown(event)) {

        if (inputManager.IsKeyDown(event, "[")) {
            _levelSpeed -= .1;
            if (_levelSpeed < 0) _levelSpeed = 0;
            return;
        }

        if (inputManager.IsKeyDown(event, "]")) {
            _levelSpeed += .1;
            return;
        }

        if (inputManager.IsKeyDown(event, "F5")) {
            // Quicksave prittified json
            std::ofstream o("../content/saves/quicksave.json"); // TODO refactor AssetManager
            o << std::setw(4) << nlohmann::json(*_player.get()) << std::endl;
            return;
        }

        if (inputManager.IsKeyDown(event, "R")) {
            _player->ChangeState("reload");
            return;
        }
    }
}

void Level::Update(float time) {
    const auto accSpeed = time * _levelSpeed;

    AnimationManager::Instance().update(*_player, accSpeed);

    for (auto &&objNoEnemie : _objsNoEnemies) {
        objNoEnemie->update(accSpeed);
    }

    if (!_waveController.Update(accSpeed, _npcs, _player)) {
        _player->SetHighestLevel(_level + 1);
        std::cout << "Level af, maak iets leuks om dit op te vangen" << endl;
        cin.get();
    }

    for (auto &&npc : _npcs) {
        npc->UpdatePosition(_npcs, accSpeed);
    }

    for (auto &obj : _objs) {
        if (!obj->isVisible()) {
            this->AddExplosion(obj->GetCoordinates());
        }
    }

    for (auto &explosion : _explosion) {
        AnimationManager::Instance().update(explosion, accSpeed);
    }

    RemoveHiddenExplosionObjects(_explosion);
    RemoveHiddenObjects(_objsNoEnemies);
    //RemoveHiddenObjects(_npcs);
    RemoveHiddenObjects(_objs);
}

void Level::AddExplosion(const Point &point) {
    auto explosion = ExplosionFactory::Instance().GetRandomExplosion(point);
//            auto explosion = ExplosionFactory::Instance().GetExplosion("blood-2", obj->GetCoordinates());
    _explosion.push_back(explosion);
}

void Level::RemoveHiddenObjects(std::vector<std::shared_ptr<MoveableObject>> &objects) {
    auto y(std::remove_if(objects.begin(), objects.end(),
                          [](shared_ptr<MoveableObject> &o) { return !o->isVisible(); }));
    objects.erase(y, objects.end());
}

void Level::RemoveHiddenExplosionObjects(std::vector<Explosion> &objects) {
    auto y(std::remove_if(objects.begin(), objects.end(),
                          [](MoveableObject &o) { return !o.isVisible(); }));
    objects.erase(y, objects.end());
}

void Level::Draw() {
    for (auto &&obj : _objsNoEnemies) {
        obj->draw();
    }

    for (auto &&obj : _npcs) {
        obj->draw();
    }

    for (auto explosion : _explosion) {
        explosion.draw();
    }

    _waveController.Draw();

    // TODO, verplaatsen
    auto weaponName = _player->getWeapon()->getName();
    auto totalBullets = _player->getWeapon()->totalBullets();
    auto remainingBullets = totalBullets - _player->getWeapon()->getShooted();
    RenderManager::Instance().DrawText("Weapon: " + weaponName, config::width - 360, 0, 360, 40, 0);
    RenderManager::Instance().DrawText("Bullets: " +
                                       to_string(remainingBullets) + "/" +
                                       to_string(totalBullets), config::width - 360, 40, 360, 40, 0);

//    //PhysicsManager::Instance().DrawQTree();
}

void from_json(const nlohmann::json &j, Level &value) {
    value.SetId(j.at("id").get<int>());
    value.SetMap(j.at("map").get<std::string>());
    value.SetWaves(j.at("waves").get < std::forward_list < Wave >> ());
}
