#include "state_machine.hpp"
#include <application.hpp>

namespace tk
{
#pragma region Overrides

	bool StateMachine::onUpdate(double delta) {
		// Update all nodes.
		for (auto &node : m_nodes) {
			node->onUpdate(delta);
		}

		// Update state if we have one.
		return m_state ? m_state->onUpdate(delta) : true;
	}

	void StateMachine::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		// Draw all nodes.
		for (auto &node : m_nodes) {
			target.draw(*node);
		}

		// Ask state to draw itself, if we have one.
		if (m_state) {
			m_state->draw(target, states);
		}
	}

#pragma endregion

#pragma region Application handling

	void StateMachine::setApplication(std::shared_ptr<tk::Application> application) {
		m_application = std::weak_ptr<tk::Application>(application);
	}

	tk::Application *StateMachine::application() {
		return m_application.lock().get();
	}

#pragma endregion

#pragma region States handling

	//-------------------------------------------------------------------------
	void StateMachine::setState(tk::State *state) {
		// Inform current state it's being deactivated.
		if (m_state) {
			m_state->onDeactivated();
			m_state->setApplication(nullptr);
		}

		// Update new state.
		m_state = state;

		// Notitfy new state it's being activated.
		m_state->setApplication(m_application.lock());
		m_state->onActivated();
	}

	//-------------------------------------------------------------------------
	void StateMachine::setState(tk::State &state) {
		setState(&state);
	}

#pragma endregion

} // namespace tk
