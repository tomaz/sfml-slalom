#include "state.hpp"

namespace tk
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	State::State() {
	}

	//-------------------------------------------------------------------------
	State::~State() {
	}

#pragma endregion

#pragma region Subclass

	//-------------------------------------------------------------------------
	void State::onActivated() {
		// Nothing to do by defaylt.
	}

	//-------------------------------------------------------------------------
	void State::onDeactivated() {
		// Nothing to do by defaylt.
	}

	//-------------------------------------------------------------------------
	bool State::onUpdate(double delta) {
		return false;
	}

	//-------------------------------------------------------------------------
	void State::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		// Nothing to do by defaylt.
	}

#pragma endregion

} // namespace tk
