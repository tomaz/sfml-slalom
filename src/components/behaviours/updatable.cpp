#include "updatable.hpp"

namespace tk
{
	//-------------------------------------------------------------------------
	Updatable::Updatable(bool active) noexcept
		: m_active{ active } {
	}

	//-------------------------------------------------------------------------
	void Updatable::onActive(bool active) {
		// Nothing to do by default.
	}

	//-------------------------------------------------------------------------
	bool Updatable::update(double delta) {
		if (!m_active) return false;
		return onUpdate(delta);
	}

	//-------------------------------------------------------------------------
	void Updatable::setActive(bool active) {
		m_active = active;
		onActive(m_active);
	}

} // namespace tk
