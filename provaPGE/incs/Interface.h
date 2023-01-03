#include "MovementEngine.h"
#include "olcPixelGameEngine.h"
#include "olcPGEX_TransformedView.h"

#include "Balls.h"
#include "Celestial.h"


#ifndef __INTERFACE__
#define __INTERFACE__

enum Integrators {
	EULER = 1,
	RK4,
	CELESTIAL,
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
	//Changed to private because there won't be anything that derives from Interface
private:
	GravityBalls ball{ { static_cast<double> (this->ScreenWidth()) , static_cast<double>(this->ScreenHeight()) }, {0., 0.} };
	enum Integrators mode = EULER;
	bool mode_changed = false;
	Engines::MovementEngine* engine;
	Celestial::Celestial
		Mercury{ { 57.9e6, 0.   }, { 47.9, 0. }, 0.330e24 },
		Venus  { { 108.2e6, 0.  }, { 35.0, 0. },  4.87e24 },
		Earth  { { 149.6e6, 0.  }, { 29.8, 0.},   5.97e24 },
		Mars   { { 227.9e6, 0.  }, { 24.1, 0.},  0.642e24 },
		Saturn { { 778.6e6, 0.  }, { 13.1, 0.},   1898e24 },
		Jupyter{ { 1433.5e6, 0. }, {  9.7, 0.},    568e24 },
		Uranus { { 2872.5e6, 0. }, {  6.8, 0.},   86.8e24 },
		Neptune{ { 4495.1e6, 0. }, {  5.4, 0.},    102e24 },
		Pluto  { { 5906.4e6, 0. }, { 0., 0.}, 0.0130e24 };

	Celestial::Sun SUN{ this };
	olc::TransformedView tv;

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
