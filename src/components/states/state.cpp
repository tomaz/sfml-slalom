#include "state.hpp"

namespace tk
{
#pragma region Subclass

	//-------------------------------------------------------------------------
	void State::onActivated() {
		// Nothing to do by default.
	}

	//-------------------------------------------------------------------------
	void State::onDeactivated() {
		// Nothing to do by defaylt.
	}

	//-------------------------------------------------------------------------
	bool State::onUpdate(double delta) {
		for (auto &node : m_nodes) {
			node->onUpdate(delta);
		}
		return true;
	}

	//-------------------------------------------------------------------------
	void State::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		for (auto &node : m_nodes) {
			target.draw(*node);
		}
	}

#pragma endregion

} // namespace tk
