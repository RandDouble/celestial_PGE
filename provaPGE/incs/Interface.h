#include "MovementEngine.h"
#include "olcPixelGameEngine.h"

#include "Balls.h"
#include "Celestial.h"


#ifndef __INTERFACE__
#define __INTERFACE__

enum Integrators {
	EULER = 1,
	RK4 ,
	CELESTIAL ,
};

enum planets {
	MERCURY,
	VENUS,
	EARTH,
	MARS,
	SATURN,
	JUPYTER,
	URANUS,
	NEPTUNE,
	PLUTO
};



class Interface : public olc::PixelGameEngine
{
protected:
	GravityBalls ball{ { static_cast<double> (this->ScreenWidth()) , static_cast<double>(this->ScreenHeight()) }, {0., 0.} };
	enum Integrators mode = EULER;
	bool mode_changed = false;
	Engines::MovementEngine* engine;
	Celestial::Celestial
		Mercury{ { this->ScreenWidth() / 2. - 40, 0. }, { 0 , 0 }, 0.330e24 },
		Venus{ { this->ScreenWidth() / 2. - 40, 0. }, { 0 , 0 }, 4.87e24 },
		Earth{ { this->ScreenWidth() / 2. - 40, 0. }, { 0., 0.}, 5.97e24 },
		Mars{ { this->ScreenWidth() / 2. - 40, 0. }, { 0., 0.}, 0.642e24 },
		Saturn{ { this->ScreenWidth() / 2. - 40, 0. }, { 0., 0.}, 1898e24 },
		Jupyter{ { this->ScreenWidth() / 2. - 40, 0. }, { 0., 0.}, 568e24 },
		Uranus{ { this->ScreenWidth() / 2. - 40, 0. }, { 0., 0.}, 86.8e24 },
		Neptune{ { this->ScreenWidth() / 2. - 40, 0. }, { 0., 0.}, 102e24 },
		Pluto{ { this->ScreenWidth() / 2. - 40, 0. }, { 0., 0.}, 0.0130e24 };

	Celestial::Sun SUN{ this };
public:
	//constructor
	Interface()
	{
		sAppName = "Balls with Gravity";
	}

	~Interface() { if (engine) delete engine; };

public:
	//creation
	bool OnUserCreate() override;
	//frame update
	bool OnUserUpdate(float fElapsedTime) override;


};

#endif
