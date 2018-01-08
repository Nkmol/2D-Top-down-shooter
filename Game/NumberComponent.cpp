#include "NumberComponent.h"
#include "RenderManager.h"

NumberComponent::NumberComponent(int* number, Point pos, int w, int h, float time, double angle)
	: IHudComponent(pos, w, h, time, angle), _number{ number }
{

}

void NumberComponent::Update(float time)
{
	_livingtime += time;
}

void NumberComponent::Draw()
{
	//RenderManager::Instance().DrawText(std::to_string(*_number), _pos.x, _pos.y, _w, _h, _angle, 122);
}
