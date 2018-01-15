#pragma once
#include <string>
#include "GameObject.h"
#include "Event.h"
#include <functional>


class Button : public GameObject {
	typedef function<void()> DelegateFunction;
public:
	Button(const std::string& mediatoken, const Point& startPosition, const Point& size);
	Button(const std::string& mediatoken, const Point& startPosition, const Point& size, const DelegateFunction&& del);
	Button();
	bool IsClicked(Event ev) const;
	void Click() const;
private:
	DelegateFunction _clickFuncton;
};
