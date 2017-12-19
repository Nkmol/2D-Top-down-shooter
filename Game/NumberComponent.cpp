#include "NumberComponent.h"
#include "RenderManager.h"

NumberComponent::NumberComponent(int* number, Point pos, int w, int h, double angle)
	: IHudComponent(pos, w, h, angle), _number{ number }
{

}

void NumberComponent::Update(float time)
{

}

void NumberComponent::Draw()
{
	RenderManager::Instance().DrawText(std::to_string(*_number), _pos.x, _pos.y, _w, _h, _angle, 122);
}
