#include "physical.hpp"

namespace tk
{
	//-------------------------------------------------------------------------
	void Physical::onUpdate(double delta) {
		// Apply acceleration.
		m_velocity += m_acceleration * delta;

		// Update position with velocity.
		auto vel = m_velocity * delta;
		move({ (float)vel.x, (float)vel.y });
	}

} // namespace tk
