#include "olcPixelGameEngine.h"

#include <vector>
#include <functional>

#include "VectorOp.h"

#pragma once
namespace Engines {
	class MovementEngine
	{
	public:
		virtual void movement(const float fElapsedTime, std::array<olc::vd2d, 2>& start, const std::function< std::array<olc::vd2d, 2>(const float, const std::array<olc::vd2d, 2>&)>) = 0;

	};

	class Euler : public MovementEngine
	{
	public:
		void movement(const float fElapsedTime, std::array<olc::vd2d, 2>& start, const std::function < std::array<olc::vd2d, 2>(const float, const std::array<olc::vd2d, 2>&)>) override;
	};

	class RK4 : public MovementEngine
	{
	public:
		void movement(const float fElapsedTime, std::array<olc::vd2d, 2>& start, const std::function < std::array<olc::vd2d, 2>(const float, const std::array<olc::vd2d, 2>&)>) override;
	};
}