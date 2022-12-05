#pragma once

#include <vector>

#include "Balls.h"
#include "MovementEngine.h"

namespace Celestial {
	//Useful Constant
	constexpr double G = 6.67e-11;

	// Class that represents planets
	class Celestial : public Balls
	{
	protected:
		// Mass
		double m_mass{1.};
		// Container for neighbours
		std::vector<Celestial> m_neighbours{};

	public:
		// Constructors
		Celestial(olc::PixelGameEngine* game) : Balls(game) { ; }
		Celestial(olc::vd2d pos, olc::vd2d vel, double mass) : Balls(pos, vel), m_mass(mass) { ; }
		// Differential Equation
		std::array<olc::vd2d, 2> operator() (const float fElapsedTime, const std::array<olc::vd2d, 2>& choord) const override;
		// Getter
		double getMass()const { return m_mass; }

		olc::vd2d getPos() const { return coords[0]; }
		olc::vd2d getVel() const { return coords[1]; }
		// Setters
		void setNeighbours(std::vector<Celestial>& neigh) { m_neighbours = neigh; }

	};



	class Sun : public Celestial
	{
	public:
		Sun(olc::PixelGameEngine* game) : Celestial({ game->ScreenWidth() / 2.f, game->ScreenHeight() / 2.f }, { 0.,0. }, 1.989e30) {}

		void SelfDraw(olc::PixelGameEngine* game) { game->DrawCircle(coords[0], 10, olc::YELLOW); }
		std::array<olc::vd2d, 2> operator()(const float fElapsedTime, const std::array<olc::vd2d, 2>& coords) const override {
			std::array<olc::vd2d, 2> zero{ olc::vd2d{0.,0.}, olc::vd2d{0.,0.} };
			return zero;
		}
	};

}
