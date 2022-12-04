#include "olcPixelGameEngine.h"

#include <vector>
#include <functional>

#include "VectorOp.h"

#pragma once
namespace Engines {
	class MovementEngine
	{
	public:
		virtual void movement(const float fElapsedTime, std::vector<olc::vd2d>& start, const std::function< std::vector<olc::vd2d>(const float, const std::vector<olc::vd2d>&)>) = 0;

	};

	class Euler : public MovementEngine
	{
	public:
		void movement(const float fElapsedTime, std::vector<olc::vd2d>& start, const std::function < std::vector<olc::vd2d>(const float, const std::vector<olc::vd2d>&)>) override;
	};

	class RK4 : public MovementEngine
	{
	public:
		void movement(const float fElapsedTime, std::vector<olc::vd2d>& start, const std::function < std::vector<olc::vd2d>(const float, const std::vector<olc::vd2d>&)>) override;
	};
}