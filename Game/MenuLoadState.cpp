#include "MenuLoadState.h"
#include <experimental/filesystem>
#include <iostream>
#include <comdef.h>

namespace fs = std::experimental::filesystem;

MenuLoadState::MenuLoadState()
{
}

MenuLoadState::~MenuLoadState()
{
}

void MenuLoadState::HandleEvents(Game & game, MenuState& state, Event & ev)
{

}

void MenuLoadState::Update(Game & game, float time)
{

}

void MenuLoadState::Draw()
{

}

void MenuLoadState::Init()
{
	for (auto& p : fs::directory_iterator("../content/saves")) {
		_bstr_t str(p.path().filename().c_str());
		_saveFiles.push_back({ str });
	}
}
