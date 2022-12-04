#pragma once
#include "Balls.h"
#include "MovementEngine.h"

#include <vector>

namespace Celestial {
	constexpr double G = 6.67e-11;

	class Celestial : public Balls
	{
	protected:
		const double m_mass{ 1. };
		//std::vector<olc::vd2d> operator()(float fElapsedTime, std::vector<olc::vd2d> choords) override;

	public:
		Celestial(olc::PixelGameEngine* game) : Balls(game) {}
		Celestial(olc::vd2d pos, olc::vd2d vel, double mass) : Balls(pos, vel), m_mass(mass) {}

		void ChangePos(olc::PixelGameEngine* game, float fElapsedTime);

		//std::vector<olc::vd2d> Choords() const override;
	};



	class Sun : public Celestial
	{
	public:
		Sun(olc::PixelGameEngine* game) : Celestial({ game->ScreenWidth() / 2.f, game->ScreenHeight() / 2.f }, { 0.,0. }, 1.989e30) {}
	};
}
