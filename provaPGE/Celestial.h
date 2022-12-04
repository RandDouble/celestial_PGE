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
		//std::array<olc::vd2d, 2> operator()(float fElapsedTime, std::array<olc::vd2d, 2> coords) override;

	public:
		Celestial(olc::PixelGameEngine* game) : Balls(game) {}
		Celestial(olc::PixelGameEngine* game, olc::vd2d pos, olc::vd2d vel, double mass) : Balls(pos, vel), m_mass(mass) {}

		virtual std::array<olc::vd2d,2> operator() (const float fElapsedTime, const std::array<olc::vd2d, 2>& choord) const override;

		//void ChangePos(olc::PixelGameEngine* game, float fElapsedTime);

		//std::array<olc::vd2d, 2> coords() const override;
	};



	class Sun : public Celestial
	{
	public:
		Sun(olc::PixelGameEngine* game) : Celestial(game, { game->ScreenWidth() / 2.f, game->ScreenHeight() / 2.f }, { 0.,0. }, 1.989e30) {}
	};

}
