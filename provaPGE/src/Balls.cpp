#include "../incs/Balls.h"

// Draws the Ball, takes in input the game engine
// this version randomizes ball color
void Balls::SelfDraw(olc::PixelGameEngine* game) const
{
	olc::Pixel color(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
	game->DrawCircle(coords[0], rad, color);
}

// Draws the Ball, takes in input the game engine and a color
void Balls::SelfDraw(olc::PixelGameEngine* game, olc::Pixel p) const
{
	game->DrawCircle(coords[0], rad, p);
}


// create a ball of random radius in a random position
void Balls::Redo(olc::PixelGameEngine* game)
{
	coords[0] = {(float)rand() / RAND_MAX * game->ScreenWidth(), (float)rand() / RAND_MAX * game->ScreenWidth()};
	rad = rand() % 5 + 1;
}

// Changes the ball position based on user input and the natural behaviour of the ball
void Balls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime, Engines::MovementEngine* engine)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld) coords[0].y -= coords[1].y * fElapsedTime;
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld) coords[0].x -= coords[1].x * fElapsedTime;
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld) coords[0].y += coords[1].y * fElapsedTime;
	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld) coords[0].x += coords[1].x * fElapsedTime;
}

// Reset the ball changing its position to the window center
void Balls::Reset(olc::PixelGameEngine* game)
{
	coords[0].x = game->ScreenWidth() / 2.f;
	coords[0].y = game->ScreenHeight() / 2.f;
	coords[1] = { 0., 0. };
}


std::array<olc::vd2d,2> GravityBalls::operator() (const float fElapsedTime, const std::array<olc::vd2d, 2>& choord) const
{
	std::array<olc::vd2d, 2> d_state = { olc::vd2d{0., 0.} , olc::vd2d{0., 0.} };
	// Changing position	
	d_state[0] += choord[1];
	// Changing Velocity
	d_state[1] += m_gravity - m_attr * choord[1];
	return d_state;
}


// Changes the ball position based on user input and the natural behaviour of the ball
void GravityBalls::ChangePos(olc::PixelGameEngine* game, float fElapsedTime, Engines::MovementEngine* engine)
{
	if (game->GetKey(olc::Key::W).bHeld || game->GetKey(olc::Key::UP).bHeld)
		// Moves UP with a constant velocity -m_vel.y
		// At the end of User input changes the ball velocity to m_vel.y 
	{
		coords[0].y -= m_no_grav_vel.y * fElapsedTime;
		coords[1] = {0, -m_no_grav_vel.y};
	}
	if (game->GetKey(olc::Key::A).bHeld || game->GetKey(olc::Key::LEFT).bHeld)
		// Moves to the left with constant velocity -m_vel.x
	{
		coords[0].x -= m_no_grav_vel.x * fElapsedTime;
		coords[1] = {-m_no_grav_vel.x, 0.};
	}

	if (game->GetKey(olc::Key::D).bHeld || game->GetKey(olc::Key::RIGHT).bHeld)
		// Moves to the right with +m_vel.x
	{
		coords[0].x += m_no_grav_vel.x * fElapsedTime;
		coords[1] = {+m_no_grav_vel.x, 0};
	}
	if (game->GetKey(olc::Key::S).bHeld || game->GetKey(olc::Key::DOWN).bHeld)
	{
		// Moves Down with constant velocity +m_vel.y
		coords[0].y += m_no_grav_vel.y * fElapsedTime;
		coords[1] = {0, -5.f};
	}
	else
		//Natural ball movement, in theory uses engine capabilities, actually it doesn't work anymore
	{
		engine->movement(fElapsedTime, coords, *this);
		ManageCollision(game, fElapsedTime);
	}
}

// Display current stats as position and velocity
void GravityBalls::DisplayStats(olc::PixelGameEngine* game) const
{
	game->DrawStringDecal({ 5.,5. }, "Position " + coords[0].str());
	game->DrawStringDecal({ 5. , 15. }, "Velocity " + coords[1].str());
}

bool GravityBalls::CheckFloorCollision(olc::PixelGameEngine* game) const
{
	return (coords[0].y + rad > game->ScreenHeight() || coords[0].y - rad < 0.f);
}

bool GravityBalls::CheckLateralCollision(olc::PixelGameEngine* game) const
{
	return coords[0].x + rad > game->ScreenWidth() || coords[0].x - rad < 0.f;
}

void GravityBalls::ManageCollision(olc::PixelGameEngine* game, float fElapsedTime)
{
	if (CheckFloorCollision(game))
	{
		// Inverses the velocity in respect to y direction
		coords[1] = olc::vd2d(coords[1].x, -coords[1].y);
	}
	if (CheckLateralCollision(game))
	{
		// Inverses the velocity in respect to x direction
		coords[1] = olc::vd2d(-coords[1].x, coords[1].y);
	}
}
