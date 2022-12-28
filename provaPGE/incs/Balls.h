#include "olcPixelGameEngine.h"
#include "olcPGEX_TransformedView.h"
#include "MovementEngine.h"

#include <vector>

#pragma once

class Balls
{
protected:
	olc::vd2d m_pos{100.f , 100.f}; // In last position changing to world coordinates... It will be a lot of work
					 // Also just to remember this is the starting position... It's not the actual position, that is in coord	
	olc::vd2d m_vel{ 50.f, 50.f };

	// Trying to implement an external movement engine...
	// In this way m_pos and m_vel became the starting position and velocity and nothing more
	// So after integration cycle the reference changed are only coords and nothing more.
	// After the discussion with Mario and obseriving the code I realized that it is better to keep a
	// vector with the position and a vector with the velocity... (There is a problem with the naming convention of olc::vd2d 
	// that names its member x and y, so I think it is better to separe in {pos, vel} in respect to {{pos.x , vel.x},{ pos.y , vel.y}})
	// In a future release with 3D coords I think that we will need to implement a 3D vector different from
	// olc::vd2d, who knows, maybe it is implemented in PGEX 3D graphics... I need to check.
	std::array<olc::vd2d, 2> coords{ m_pos, m_vel };
	float rad{ 7 }; // Radius of the object
	friend class Engines::MovementEngine; // I don't know if this is usefull yet.


public:
	// This is very important, it is the functor of the class that contains
	// the differential equation throught which is described the behaviour of the class
	// I translated to public to simplicity... I do not understand friend keyword at this point...
	virtual std::array<olc::vd2d, 2> operator() (const float fElapsedTime, const std::array<olc::vd2d, 2>& coord) const = 0;
	// Constructor
	Balls() {;}

	Balls(olc::vd2d pos, olc::vd2d vel) : m_pos(pos), m_vel(vel), coords({ pos, vel }) {}

	// Methods
	//Drawing 
	void SelfDraw(olc::TransformedView& game) const;
	void SelfDraw(olc::TransformedView& game, olc::Pixel p) const;
	//Old Change Position
	void ChangePos(olc::PixelGameEngine* game, float fElapsedTime, Engines::MovementEngine* engine);
	//getting position
	olc::vd2d GetPos() const { return coords[0]; }

	//reset to Initial Parameters
	void Reset();
	//I don t remember what it does
	void Redo(olc::PixelGameEngine* game);
};

class GravityBalls : public Balls
{
private:
	olc::vd2d m_gravity = { 0.0, 10.f };
	olc::vd2d m_no_grav_vel = { 50.f, 50.f };
	double m_attr = 0.01;

public:
	std::array<olc::vd2d, 2> operator() (const float fElapsedTime, const std::array<olc::vd2d, 2>& choord) const override;
	//constructor
	GravityBalls() : Balls() {}
	GravityBalls(olc::vd2d pos, olc::vd2d vel) : Balls(pos, vel) {}

	//Methods
	//This change the position uses Movement Engine to integrate the motion
	void ChangePos(olc::TransformedView& game, float fElapsedTime, Engines::MovementEngine* engine);
	//Print to screen the ball stats
	void DisplayStats(olc::TransformedView& game) const;
	//Checks for collisions
	bool CheckFloorCollision(olc::TransformedView& game) const;
	bool CheckLateralCollision(olc::TransformedView& game) const;
	//Managing Collisions
	void ManageCollision(olc::TransformedView& game, float fElapsedTime);
};

