#include "../incs/Interface.h"
#include "../incs/MovementEngine.h"

bool Interface::OnUserCreate()
{
	//Initializing transformed view
	tv .Initialise({ ScreenWidth(), ScreenHeight() });

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
	tv.DrawLineDecal(tv.ScreenToWorld({ 0.f, ScreenHeight() / 2.f }), tv.ScreenToWorld({ (float)ScreenWidth(), ScreenHeight() / 2.f }));
	tv.DrawLineDecal(tv.ScreenToWorld({ ScreenWidth() / 2.f, 0.f }), tv.ScreenToWorld({ ScreenWidth() / 2.f, ScreenHeight() * 1.f }));

	// Handling panning... I add this function in this section because I do not think it is necessary only
	// to Celestial but also and foremost to Gravity Balls
	// Movement with a mouse
	if (GetMouse(2).bPressed)  tv.StartPan (GetMousePos());
	if (GetMouse(2).bHeld)     tv.UpdatePan(GetMousePos());
	if (GetMouse(2).bReleased) tv.EndPan   (GetMousePos());
	// Maybe in a future version adding a VIM style movement with HJKL


	// Zoom
	if (GetKey(olc::Key::M).bPressed) tv.ZoomAtScreenPos(2.0f, tv.WorldToScreen(ball.GetPos()));
	if (GetKey(olc::Key::N).bPressed) tv.ZoomAtScreenPos(.5f, tv.WorldToScreen(ball.GetPos()));

	tv.DrawStringDecal(tv.ScreenToWorld({ 5, 35 }), "Mouse Position : " + GetMousePos().str(), olc::YELLOW, tv.ScaleToWorld({ 1.f, 1.f }));

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
		tv.DrawStringDecal(tv.ScreenToWorld({ 5., 25. }), "Mode " + std::to_string(mode) + ":\tEuler", olc::GREEN, tv.ScaleToWorld({1.f, 1.f}));
		Clear(olc::BLACK);
		if (mode_changed)
		{
			mode_changed = false;
			delete engine;
			engine = new Engines::Euler();
		}

		ball.ChangePos(tv, fElapsedTime, this->engine);
		break;
	case RK4:
		/* Testing Runge Kutta 4 Integration Methods */
		tv.DrawStringDecal(tv.ScreenToWorld({ 5., 25. }), "Mode " + std::to_string(mode) + ":\tRK4", olc::GREEN, tv.ScaleToWorld({ 1.f, 1.f }));
		Clear(olc::DARK_BLUE);
		if (mode_changed)
		{
			mode_changed = false;
			delete engine;
			engine = new Engines::RK4();
		}
		ball.ChangePos(tv, fElapsedTime, engine);
		break;
	case CELESTIAL:
		/* Celestial Movement  WIP */
		tv.DrawStringDecal(tv.ScreenToWorld({ 5., 25. }), "Mode " + std::to_string(mode) + ":\tCelestial", olc::GREEN, tv.ScaleToWorld({ 1.f, 1.f }));
		Clear(olc::DARK_CYAN);

		break;
	}


	// Balls Drawer
	ball.SelfDraw(tv, olc::RED);
	ball.DisplayStats(tv);

	// Reset Button
	if (GetKey(olc::Key::SPACE).bPressed) ball.Reset();

	// Exit Button
	if (GetKey(olc::Key::F4).bPressed) return false;

	return true;
}


