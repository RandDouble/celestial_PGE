#include "Balls.h"

// Draws the Ball, takes in input the game engine
// this version randomizes ball color
void Balls::SelfDraw(olc::PixelGameEngine* game) const
{
	olc::Pixel color(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
	game->DrawCircle(choords[0], rad, color);
}

// Draws the Ball, takes in input the game engine and a color
void Balls::SelfDraw(olc::PixelGameEngine* game, olc::Pixel p) const
{
	game->DrawCircle(choords[0], rad, p);
}


// create a ball of random radius in a random position
void Balls::Redo(olc::PixelGameEngine* game)
{
	choords[0] = {(float)rand() / RAND_MAX * game->ScreenWidth(), (float)rand() / RAND_MAX * game->ScreenWidth()};
	rad = rand() % 5 + 1;
}

// Changes the ball position based on user input and the natural behaviour of the ball
void Balls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime, Engines::MovementEngine* engine)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld) choords[0].y -= choords[1].y * fElapsedTime;
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld) choords[0].x -= choords[1].x * fElapsedTime;
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld) choords[0].y += choords[1].y * fElapsedTime;
	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld) choords[0].x += choords[1].x * fElapsedTime;
}

// Reset the ball changing its position to the window center
void Balls::Reset(olc::PixelGameEngine* game)
{
	m_pos.x = game->ScreenWidth() / 2.f;
	m_pos.y = game->ScreenHeight() / 2.f;
}


std::vector<olc::vd2d> GravityBalls::operator() (const float fElapsedTime, const std::vector<olc::vd2d>& choord) const
{
	std::vector<olc::vd2d> d_state{ {0., 0.} ,{0., 0.} };
	// Changing position	
	d_state[0] += choord[1];
	// Changing Velocity
	d_state[1] += m_gravity;
	return d_state;
}


// Changes the ball position based on user input and the natural behaviour of the ball
void GravityBalls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime, Engines::MovementEngine* engine)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld)
		// Moves UP with a constant velocity -m_vel.y
		// At the end of User input changes the ball velocity to m_vel.y 
	{
		choords[0].y -= m_no_grav_vel.y * fElapsedTime;
		choords[1] = {0, -m_no_grav_vel.y};
	}
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld)
		// Moves to the left with constant velocity -m_vel.x
	{
		choords[0].x -= m_no_grav_vel.x * fElapsedTime;
		choords[1] = {-m_no_grav_vel.x, 0.};
	}

	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld)
		// Moves to the right with +m_vel.x
	{
		choords[0].x += m_no_grav_vel.x * fElapsedTime;
		choords[1] = {+m_no_grav_vel.x, 0};
	}
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld)
	{
		// Moves Down with constant velocity +m_vel.y
		choords[0].y += m_no_grav_vel.y * fElapsedTime;
		choords[1] = {0, -5.f};
	}
	else
		//Natural ball movement, in theory uses engine capabilities, actually it doesn't work anymore
	{
		engine->movement(fElapsedTime, choords, *this);
		ManageCollision(game, fElapsedTime);
	}
}

// Display current stats as position and velocity
void GravityBalls::DisplayStats(olc::PixelGameEngine* game) const
{
	game->DrawStringDecal({ 5.,5. }, "Position " + choords[0].str());
	game->DrawStringDecal({ 5. , 15. }, "Velocity " + choords[1].str());
}

bool GravityBalls::CheckFloorCollision(olc::PixelGameEngine* game) const
{
	return (choords[0].y + rad > game->ScreenHeight() || choords[0].y - rad < 0.f);
}

bool GravityBalls::CheckLateralCollision(olc::PixelGameEngine* game) const
{
	return choords[0].x + rad > game->ScreenWidth() || choords[0].x - rad < 0.f;
}

void GravityBalls::ManageCollision(olc::PixelGameEngine* game, float fElapsedTime)
{
	if (CheckFloorCollision(game))
	{
		// Inverses the velocity in respect to y direction
		choords[1] = olc::vd2d(choords[1].x, -choords[1].y);
	}
	if (CheckLateralCollision(game))
	{
		// Inverses the velocity in respect to x direction
		choords[1] = olc::vd2d(-choords[1].x, choords[1].y);
	}
}
