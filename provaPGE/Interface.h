#include "MovementEngine.h"
#include "olcPixelGameEngine.h"

#include "Balls.h"
//#include "Celestial.h"


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
	GravityBalls ball{ { static_cast<double> (this->ScreenWidth()) , static_cast<double>(this->ScreenHeight()) }, {0., 0.} };
	enum Integrators mode = EULER;
	bool mode_changed = false;
	Engines::MovementEngine* engine;
	//static const Celestial::Celestial
	//	Mercury(this, {,0}, {0,0}, 0.330e24),
	//	Venus(this, {,}, {0,0}, 4.87e24),
	//	Earth(this, {,}, {0.,}, 5.97e24),
	//	Mars(this,  {,}, {,}, 0.642e24),
	//	Saturn(this, {,}, {,}, 1898e24),
	//	Jupyter(this, {,}, {,}, 568e24),
	//	Uranus(this, {,}, {,}, 86.8e24),
	//	Neptune(this, {,}, {,}, 102e24),
	//	Pluto(this, {,}, {,}, 0.0130e24);
	//
	//Celestial::Sun sun(this);
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
