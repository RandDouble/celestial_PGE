#include "MovementEngine.h"
#include "olcPixelGameEngine.h"

#include "Balls.h"

#ifndef __INTERFACE__
#define __INTERFACE__

enum Integrators {
	EULER = 1,
	RK4 ,
	CELESTIAL ,
};

class Interface : public olc::PixelGameEngine
{
protected:
	GravityBalls ball{ this };
	enum Integrators mode = EULER;
	bool mode_changed = false;
	Engines::MovementEngine* engine;

public:
	//constructor
	Interface()
	{
		sAppName = "Proviamo";
	}

	~Interface() { if (engine) delete engine; };

public:
	//creation
	bool OnUserCreate() override;
	//frame update
	bool OnUserUpdate(float fElapsedTime) override;


};

#endif
