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
	void State::onStatus(updatable::Status status) {
		// Notify all sub-nodes.
		for (auto &node : m_nodes) {
			node->setStatus(status);
		}
	}

	//-------------------------------------------------------------------------
	void State::onUpdate(double delta) {
		for (auto &node : m_nodes) {
			node->update(delta);
		}
	}

	//-------------------------------------------------------------------------
	void State::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		for (auto &node : m_nodes) {
			target.draw(*node);
		}
	}

#pragma endregion

#pragma region Getters & setters

	void State::setApplication(std::shared_ptr<tk::Application> application) {
		m_application = std::weak_ptr<tk::Application>(application);
	}

	tk::Application *State::application() {
		return m_application.lock().get();
	}

#pragma endregion

} // namespace tk
