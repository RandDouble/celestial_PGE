#include "../incs/MovementEngine.h"

void Engines::Euler::movement( const float fElapsedTime, std::array<olc::vd2d, 2>& start, const std::function< std::array<olc::vd2d, 2>(const float, const std::array<olc::vd2d, 2>&)> fun)
{
	double dt = fElapsedTime;
	start += (fun(fElapsedTime, start)* dt);
}

void Engines::RK4::movement(const float fElapsedTime, std::array<olc::vd2d, 2>& start, const std::function< std::array<olc::vd2d, 2>(const float, const std::array<olc::vd2d, 2>&)> fun)
{
	std::array<olc::vd2d, 2> k_1 = fun(0., start );
	std::array<olc::vd2d, 2> k_2 = fun(fElapsedTime/2.f, start + fElapsedTime/2.f * k_1);
	std::array<olc::vd2d, 2> k_3 = fun(fElapsedTime/2.f, start + fElapsedTime/2.f * k_2);
	std::array<olc::vd2d, 2> k_4 = fun(fElapsedTime, start + fElapsedTime * k_3);
 	start +=  (k_1 + k_2 * 2 + k_3 * 2. + k_4) * (fElapsedTime / 6.);
}