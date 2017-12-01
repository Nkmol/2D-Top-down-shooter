#include "Level.h"
#include "monsters/BatEnemy.h"

Level::Level(const int level) : _level(level) {
    Init();
}

void Level::Init() {
    MapManager::Instance().Init("../content/map/halflife.tmx");

    auto player = make_shared<Player>("soldier", 100, 300);
    player->addWeapons({Uzi(), Handgun(), Shotgun()});
    player->changeWeapon(1); // set weapon to Uzi

    _objs.emplace_back(player);

    // save pointer seperate
    _player = player;
    _flockController.GenerateFlock<ZombieEnemy>(20, 200, 600, *_player);
    _flockController.GenerateFlock<BatEnemy>(50, 200, 600, *_player);
}

void Level::HandleEvents(SDL_Event event) {
    auto &inputManager = InputManager::instance();

    if (inputManager.isMouseMoved(event)) {
        // RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
        int angle = inputManager.recalculateMouseAngle(*_player);

        // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
        _player->SetAngle(angle);
    }

    if (inputManager.isMouseClicked(event)) {
        auto bullet = make_shared<Bullet>(_player->shoot()); // returns a bullet
        _objs.emplace_back(bullet);
    }

    int key = 0;
    if (inputManager.isNumericKeyPressed(event, key)) {
        _player->changeWeapon(key);
    }


    Point direction = inputManager.getDirection(event);

    int angle = inputManager.calculateMouseAngle(*_player);

    _player->SetAngle(angle);
    _player->Move(direction);
}

void Level::Update(float time) {
    for (auto &&obj : _objs) {
        obj->update(time);
    }
    _flockController.UpdateFlocks(time);
}

void Level::Draw() {
    for (auto &&obj : _objs) {
        obj->draw();
    }
    _flockController.DrawFlocks();


    // TODO, verplaatsen
    auto weaponName = _player->getWeapon()->getName();
    auto totalBullets = _player->getWeapon()->totalBullets();
    auto remainingBullets = totalBullets - _player->getWeapon()->getShooted();
    RenderManager::Instance().DrawText("Weapon: " + weaponName, config::width - 360, 0, 360, 40, 0);
    RenderManager::Instance().DrawText("Bullets: " +
                                       to_string(remainingBullets) + "/" +
                                       to_string(totalBullets), config::width - 360, 40, 360, 40, 0);
}

