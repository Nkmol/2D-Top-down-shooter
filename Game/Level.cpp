#include "Level.h"

Level::Level(const int level) : _level(level) {
    Init();
}

void Level::Init() {
    MapManager::Instance().Init("../content/map/halflife.tmx");


    auto player = make_shared<Player>("soldier", 100, 300);
    auto uzi = make_unique<Weapon>(Uzi());
    auto handgun = make_unique<Weapon>(Handgun(10));

    player->addWeapon(*uzi);
    player->addWeapon(*handgun);
    player->changeWeapon(1);

    _objs.emplace_back(player);

    // save pointer seperate
    _player = player;
    _flockController.generateFlock(20, 100, 900, _player, 50.0f);
}

void Level::HandleEvents(SDL_Event event) {
    if (InputManager::instance().isMouseMoved(event)) {
        // RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
        int angle = InputManager::instance().recalculateMouseAngle(*_player);

        // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
        _player->setAngle(angle);
    }

    if (InputManager::instance().isMouseClicked(event)) {
        _player->shoot();
    }


    int key = 0;
    if (InputManager::instance().isNumericKeyPressed(event, key)) {
        _player->changeWeapon(key);
    }


    Point direction = InputManager::instance().getDirection(event);

    int angle = InputManager::instance().calculateMouseAngle(*_player);

    _player->setAngle(angle);
    _player->Move(direction);
}

void Level::Update(float time) {
    for (auto &&obj : _objs) {
        obj->update(time);
    }
    _flockController.updateFlocks(time);
}

void Level::Draw() {
    for (auto &&obj : _objs) {
        obj->draw();
    }
    _flockController.drawFlocks();
}

const shared_ptr<Player> &Level::getPlayer() const {
    return _player;
}
