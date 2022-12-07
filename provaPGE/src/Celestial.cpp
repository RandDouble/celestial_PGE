#include "../incs/Celestial.h"

std::array<olc::vd2d, 2> Celestial::Celestial::operator()(const float fElapsedTime, const std::array<olc::vd2d, 2>& choord) const
{
    std::array<olc::vd2d, 2> d_state;
    d_state[0] = choord[1];
    for (auto& other : m_neighbours) 
    {
        olc::vd2d tmp = { choord[0].x - other.getPos().x , choord[0].y - other.getPos().y };
        olc::vd2d dir = tmp.norm(); // versor
        d_state[1] -= G * other.getMass() * dir / tmp.mag2();
        // Need some thinking about Sun... Ideally -G * Mass_Sun * coords[0] / std::pow(coords[0].abs(),3)
    }
    return d_state;
}
