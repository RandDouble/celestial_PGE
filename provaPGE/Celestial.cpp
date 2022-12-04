#include "Celestial.h"

//std::array<olc::vd2d, 2> Celestial::Celestial::coords() const
//{
//	return std::array<olc::vd2d, 2>{m_pos, m_vel};
//}

std::array<olc::vd2d, 2> Celestial::Celestial::operator()(const float fElapsedTime, const std::array<olc::vd2d, 2>& choord) const
{
    std::array<olc::vd2d, 2> d_state;
    d_state[0] = choord[1];
    d_state[1] = -G * choord[0]; // Need some thinking about Sun... Ideally -G * Mass_Sun * coords[0] / std::pow(coords[0].abs(),3)
    return d_state;
}
