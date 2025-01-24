#include "updatable.hpp"

namespace tk
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	Updatable::Updatable(updatable::Status status) noexcept
		: m_status{ status } {
	}

#pragma endregion

#pragma region Subclass

	//-------------------------------------------------------------------------
	void Updatable::onStatus(updatable::Status status) {
		// Nothing to do by default.
	}

#pragma endregion

#pragma region Public

	//-------------------------------------------------------------------------
	void Updatable::update(double delta) {
		if (m_status == updatable::Status::Active) {
			onUpdate(delta);
		}
	}

	//-------------------------------------------------------------------------
	void Updatable::setStatus(updatable::Status status) {
		m_status = status;
		onStatus(status);
	}

#pragma endregion

} // namespace tk
