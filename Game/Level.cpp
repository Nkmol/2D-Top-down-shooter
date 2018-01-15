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
#include "../Engine/UIText.h"
#include "Hud.h"
#include "AudioManager.h"

Level::Level(const int level, const ::std::string savedGame) :
        _level(level),
        _savedGame(savedGame),
        _levelSpeed(1)
{
    Init();
    Level::_explosion = {};		
}

Level::~Level() {
	Hud::Instance().RemoveComponent(_UIBullets.get());
	Hud::Instance().RemoveComponent(_UIWeapon.get());
	Hud::Instance().RemoveComponent(_UIHealth.get());
	Hud::Instance().RemoveComponent(_miniBackground.get());
	for (auto &w : _weaponSlots)
		Hud::Instance().RemoveComponent(w.get());
}

void Level::Init() {
    LoadLevel();

	LoadUIElements();

    MapManager::Instance().Init(_map);
    LoadPlayer();

    _waveController.Init(_waves, _player, &_npcs);

    PhysicsManager::Instance().SetStaticObjects();
    PhysicsManager::Instance().SetMoveableObjects(&_objsNoEnemies);
	//AudioManager::Instance().PlayEffect("level3");
}

void Level::LoadUIElements()
{
	_UIWeapon = std::make_unique<UIText>(UIText("", 24, { config::width - 200, 0 }));
	_UIBullets = std::make_unique<UIText>(UIText("", 24, { config::width - 200, 40 }));
	_UIHealth = std::make_unique<UIText>(UIText("", 23, { config::width - 200, 80 }));
	_weaponSlots.emplace_back(std::make_unique<UIIcon>(UIIcon("handgun", { 50, 20 }, 120)));
	_weaponSlots.emplace_back(std::make_unique<UIIcon>(UIIcon("rifle", { 120, 20 }, 170)));
	_weaponSlots.emplace_back(std::make_unique<UIIcon>(UIIcon("shotgun", { 190, 20 }, 120)));
	_miniBackground = std::make_unique<UIIcon>(UIIcon("hudkader", { config::width / 6 *5, 0 }, 200));

	Hud::Instance().AddComponent(_miniBackground.get());
	Hud::Instance().AddComponent(_UIHealth.get());
	Hud::Instance().AddComponent(_UIBullets.get());
	Hud::Instance().AddComponent(_UIWeapon.get());
	for (auto &w : _weaponSlots)
		Hud::Instance().AddComponent(w.get());
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
    player->AddWeapons({Handgun(), Rifle(), Shotgun()});

    _player = player;
	ChangeWeapon(0);

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
	_player->SetSaveName(_savedGame);
    _objsNoEnemies.emplace_back(_player);
}

const Player& Level::GetPlayer() const
{
	return *_player.get();
}

void Level::HandleEvents(Event event) {
    this->HandleMouseEvents(event);
    this->HandleKeyboardEvents(event);

    Point direction = InputManager::Instance().GetDirection(event);
    int angle = InputManager::Instance().CalculateMouseAngle(*_player);
	direction.Normalize();

    _player->SetAngle(angle);
    _player->Move(direction);
}


void Level::HandleMouseEvents(Event &event) {
    if (InputManager::Instance().IsMouseMoved(event)) {
        // RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
        int angle = InputManager::Instance().RecalculateMouseAngle(*_player);
    }


    if (InputManager::Instance().IsMousePressed(event)) {
		// No need to do anything here anymore :)
    }

    if (InputManager::Instance().IsMouseReleased(event)) {
		InputManager::Instance().HandleMouseReleased();
		_player->GetWeapon()->ReleaseTrigger();
    }
}


void Level::HandleKeyboardEvents(Event &event) {

    int key = 0;

    if (InputManager::Instance().IsNumericKeyPressed(event, key)) {
        ChangeWeapon(key - 1);
    }

    if (InputManager::Instance().IsKeyDown(event)) {

        if (InputManager::Instance().IsKeyDown(event, "[")) {
            _levelSpeed -= .1;
            if (_levelSpeed < 0) _levelSpeed = 0;
            return;
        }

        if (InputManager::Instance().IsKeyDown(event, "]")) {
            _levelSpeed += .1;
            return;
        }

        if (InputManager::Instance().IsKeyDown(event, "F5")) {
            // Quicksave prittified json
            std::ofstream o("../content/saves/quicksave.json"); // TODO refactor AssetManager
            o << std::setw(4) << nlohmann::json(*_player.get()) << std::endl;
            return;
        }

        if (InputManager::Instance().IsKeyDown(event, "R")) {
            _player->ChangeState("reload");
            return;
        }

        if (InputManager::Instance().IsKeyDown(event, "K")) {
            _player->ToggleCheats();
            return;
        }

        if (InputManager::Instance().IsKeyDown(event, "N")) {
            if (_player->IsCheatActive()) {
                for (auto &npc : _npcs) {
                    npc.get()->Hide();
                }
            }
            return;
        }
    }
}

void Level::SetCompleted()
{
	_isDone = true;
	const auto highest = _player->GetHighestLevel();
	const auto current = GetId();
	if(highest <= current)
	{
		_player->SetHighestLevel(current + 1);
	}
}

bool Level::IsCompleted() const
{
	return _isDone;
}

void Level::Update(float time) {
    const auto accSpeed = time * _levelSpeed;

	if (_player->CanShoot() && InputManager::Instance().LMBState()) {
		_player->ChangeState("shoot");
		auto bullet = make_shared<Bullet>(_player->shoot()); // returns a bullet
		_objsNoEnemies.emplace_back(bullet);
	}

    AnimationManager::Instance().Update(*_player, accSpeed);

    for (auto &&objNoEnemie : _objsNoEnemies) {
        objNoEnemie->Update(accSpeed);
    }

    if (!_waveController.Update(accSpeed, _level)) {
		SetCompleted();
		std::cout << "Level af, maak iets leuks om dit op te vangen" << std::endl;
		return;
    }

    for (auto &npc : _npcs) {
        npc->UpdatePosition(accSpeed);
        if (!npc->IsVisible()) {
            this->AddExplosion(npc->GetCoordinates());
        }
    }

    for (auto &explosion : _explosion) {
        AnimationManager::Instance().Update(explosion, accSpeed);
    }

    RemoveHiddenObjects(_objsNoEnemies);
    RemoveHiddenNpcs();
    RemoveHiddenExplosionObjects(_explosion);

	auto totalBullets = _player->GetWeapon()->TotalBullets();
	auto remainingBullets = totalBullets - _player->GetWeapon()->GetShot();
	auto weaponName = _player->GetWeapon()->GetName();

	_UIWeapon->ChangeText("Weapon: " + weaponName);

	_UIBullets->ChangeText("Bullets: " +
		to_string(remainingBullets) + "/" +
		to_string(totalBullets));

	_UIHealth->ChangeText("Health: " +
		std::to_string(_player->GetLifepoints()) + "/" + 
		std::to_string(_player->GetMaxLifepoints()));
}

void Level::AddExplosion(const Point &point) {
    auto explosion = ExplosionFactory::Instance().GetRandomExplosion(point);
    _explosion.push_back(explosion);
}

void Level::RemoveHiddenObjects(std::vector<std::shared_ptr<MoveableObject>> &_objects) {
    auto y(std::remove_if(_objects.begin(), _objects.end(),
                          [](shared_ptr<MoveableObject> &o) { return !o->IsVisible(); }));
    _objects.erase(y, _objects.end());
}

void Level::RemoveHiddenNpcs() {
    auto y(std::remove_if(_npcs.begin(), _npcs.end(),
                          [](std::unique_ptr<EnemyBase> &o) { return !o->IsVisible(); }));
    _npcs.erase(y, _npcs.end());
}

void Level::RemoveHiddenExplosionObjects(std::vector<Explosion> &_objects) {
    auto y(std::remove_if(_objects.begin(), _objects.end(),
                          [](MoveableObject &o) { return !o.IsVisible(); }));
    _objects.erase(y, _objects.end());
}

void Level::Draw() {
    for (auto &&obj : _objsNoEnemies) {
        obj->Draw();
    }

    for (auto &&obj : _npcs) {
        obj->Draw();
    }

    for (auto &explosion : _explosion) {
        explosion.Draw();
    }
}

void Level::ChangeWeapon(const int num)
{
	_player->ChangeWeapon(num);
	for (size_t i = 0; i < _player->GetWeapons().size(); i++)
	{
		if (i == num)
			_weaponSlots.at(i)->SetOpacity(250);
		else
			_weaponSlots.at(i)->SetOpacity(120);
	}
}

void from_json(const nlohmann::json &j, Level &value) {
    value.SetId(j.at("id").get<int>());
    value.SetMap(j.at("map").get<std::string>());
    value.SetWaves(j.at("waves").get < std::forward_list < Wave >> ());
}
