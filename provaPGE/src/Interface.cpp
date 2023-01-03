#include "../incs/Interface.h"
#include "../incs/MovementEngine.h"

bool Interface::OnUserCreate()
{
	//Initializing transformed view
	tv.Initialise(GetScreenSize());

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
	if (GetMouse(0).bPressed)  tv.StartPan(GetMousePos());
	if (GetMouse(0).bHeld)     tv.UpdatePan(GetMousePos());
	if (GetMouse(0).bReleased) tv.EndPan(GetMousePos());
	// Maybe in a future version adding a VIM style movement with HJKL

	// Zoom
	// Changed to a Switch to change zoom style from Gravity Balls and Celestial.
	switch (mode)
	{
	case EULER:
	case RK4:
		if (GetKey(olc::Key::M).bPressed) tv.ZoomAtScreenPos(2.0f, static_cast<olc::vf2d> (GetScreenSize()) / 2.f /*tv.WorldToScreen(ball.GetPos())*/);
		if (GetKey(olc::Key::N).bPressed) tv.ZoomAtScreenPos(0.5f, static_cast<olc::vf2d> (GetScreenSize()) / 2.f /*tv.WorldToScreen(ball.GetPos())*/);
		break;
	case CELESTIAL:
		if (GetKey(olc::Key::M).bPressed) tv.ZoomAtScreenPos(2.0f, GetMousePos());
		if (GetKey(olc::Key::N).bPressed) tv.ZoomAtScreenPos(0.5f, GetMousePos());
		break;
	}
	tv.DrawStringDecal(tv.ScreenToWorld({ 5, 35 }), "Mouse Position : " + tv.ScreenToWorld(GetMousePos()).str(), olc::YELLOW, tv.ScaleToWorld({ 1.f, 1.f }));

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
		tv.DrawStringDecal(tv.ScreenToWorld({ 5., 25. }), "Mode " + std::to_string(mode) + ":\tEuler", olc::GREEN, tv.ScaleToWorld({ 1.f, 1.f }));
		Clear(olc::BLACK);
		// Checking if mode Changed
		if (mode_changed)
		{
			mode_changed = false;
			tv.SetWorldScale({ 1.f, 1.f });
			delete engine;
			engine = new Engines::Euler();
		}

		ball.ChangePos(tv, fElapsedTime, this->engine);
		// Balls Drawer
		ball.SelfDraw(tv, olc::RED);
		ball.DisplayStats(tv);
		break;
	case RK4:
		/* Testing Runge Kutta 4 Integration Methods */
		Clear(olc::DARK_BLUE);
		tv.DrawStringDecal(tv.ScreenToWorld({ 5., 25. }), "Mode " + std::to_string(mode) + ":\tRK4", olc::GREEN, tv.ScaleToWorld({ 1.f, 1.f }));
		// checking if Mode changed
		if (mode_changed)
		{
			mode_changed = false;
			tv.SetWorldScale({ 1.f, 1.f });
			delete engine;
			engine = new Engines::RK4();
		}
		ball.ChangePos(tv, fElapsedTime, engine);
		// Balls Drawer
		ball.SelfDraw(tv, olc::RED);
		ball.DisplayStats(tv);
		break;

	case CELESTIAL:
		/* Celestial Movement  WIP */
		// Changing World Scale to Draw planets... it still doesn't function
		if (mode_changed)
		{
			mode_changed = false;
			tv.SetWorldScale(olc::vd2d (1.f / (2. * 5906.4e6), 1.f / (2. * 5906.4e6)));
		}
		// Documenting Mouse Position for debugging
		tv.DrawStringDecal(tv.ScreenToWorld({ 5., 5. }), "Mode " + std::to_string(mode) + ":\tCelestial", olc::GREEN, tv.ScaleToWorld({ 1.f, 1.f }));
		tv.DrawStringDecal(tv.ScreenToWorld({ 5. , 15. }), "Scaling : " + tv.GetWorldScale().str(), olc::DARK_MAGENTA, tv.ScaleToWorld({ 1.f, 1.f }));
		// Background
		Clear(olc::DARK_CYAN);
		// Hoping to get a circle in some part of the world
		tv.FillCircle(tv.ScreenToWorld(static_cast< olc::vd2d>(GetScreenSize()) / 2.f), tv.ScaleToWorld({10., 0.}).x, olc::DARK_RED);

		break;
	}

	// Reset Button
	if (GetKey(olc::Key::SPACE).bPressed) ball.Reset();

	// Exit Button
	if (GetKey(olc::Key::F4).bPressed) return false;

	return true;
}