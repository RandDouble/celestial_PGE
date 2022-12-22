#include "../incs/Interface.h"
#include "../incs/MovementEngine.h"

bool Interface::OnUserCreate()
{
	//Initializing transformed view
	tv.Initialise({ ScreenWidth(), ScreenHeight() });
	switch (mode)
	{
	case EULER:
		this->engine = new Engines::Euler();
		break;
	case RK4:
		this->engine = new Engines::RK4();
		break;
	}
	return true;
}

bool Interface::OnUserUpdate(float fElapsedTime)
{

	// Adding a Grid
	tv.DrawLineDecal({ 0.f, ScreenHeight() / 2.f }, { (float)ScreenWidth(), ScreenHeight() / 2.f });
	tv.DrawLineDecal({ ScreenWidth() / 2.f, 0.f }, { ScreenWidth() / 2.f, ScreenHeight() * 1.f });

	// Functioning Mode selector
    if (mode != EULER && GetKey(olc::Key::K1).bPressed)
	{
		/* Testing Euler Integration Methods */
		mode = EULER;
		mode_changed = true;
	}
    if (mode != RK4 && GetKey(olc::Key::K2).bPressed)
	{
		mode = RK4;
		mode_changed = true;
	}
	if (GetKey(olc::Key::K3).bPressed)
	{
		mode = CELESTIAL;
		mode_changed = true;
	}
	// Movement
	switch (mode)
	{
	case EULER:
		tv.DrawStringDecal({ 5., 25. }, "Mode " + std::to_string(mode) + ":\tEuler", olc::GREEN);
		Clear(olc::BLACK);
		if (mode_changed)
		{
			mode_changed = false;
			delete engine;
			engine = new Engines::Euler();
		}

		ball.ChangePos(this, fElapsedTime, this->engine);
		break;
	case RK4:
		/* Testing Runge Kutta 4 Integration Methods */
		tv.DrawStringDecal({ 5., 25. }, "Mode " + std::to_string(mode) + ":\tRK4", olc::GREEN);
		Clear(olc::DARK_BLUE);
		if (mode_changed)
		{
			mode_changed = false;
			delete engine;
			engine = new Engines::RK4();
		}
		ball.ChangePos(this, fElapsedTime, engine);
		break;
	case CELESTIAL:
		/* Celestial Movement  WIP */
		Clear(olc::WHITE);
		break;
	}


	// Balls Drawer
	ball.SelfDraw(tv, olc::RED);
	ball.DisplayStats(this);

	/* V2
	ball.Redo(this);
*/

	// Reset Button
	if (GetKey(olc::Key::SPACE).bPressed) ball.Reset(this);

	// Exit Button
	if (GetKey(olc::Key::F4).bPressed) return false;

	return true;
}


