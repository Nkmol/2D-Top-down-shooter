//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_HELPER_H
#define SHOOTER_HELPER_H
#include <memory>

class Helper{
public:
    static int CalculateAngle(float x1, float y1, float x2, float y2);
    static float DegreesToRadians(double degrees);
    static int Distance(float x1, float y1, float x2, float y2);
    static int CorrectAngle(int angle);
    static float RadiansToDegrees(double radians);
};

namespace HelperClasses
{

	// CRTP idiom - https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
	// Cloneable impl - https://katyscode.wordpress.com/2013/08/22/c-polymorphic-cloning-and-the-crtp-curiously-recurring-template-pattern/
	template <class Base, class Derived>
	class CloneableBase : public Base
	{
	public:
		//http://www.stroustrup.com/C++11FAQ.html#inheriting
		using Base::Base;

		virtual std::unique_ptr<Base> Clone() const
		{
			return std::make_unique<Derived>(static_cast<Derived const &>(*this)); // call the copy ctor.
		}
	protected:
		~CloneableBase() {};
		friend Derived;
	};
}



#endif //SHOOTER_HELPER_H
