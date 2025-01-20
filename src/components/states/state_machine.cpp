#include "state_machine.hpp"

namespace tk
{
#pragma region Construction & destruction

	StateMachine::StateMachine()
		: m_application{ nullptr }
		, m_state{ nullptr } {
	}

	StateMachine::~StateMachine() {
		m_application = nullptr;
		m_state		  = nullptr;
	}

#pragma endregion

#pragma region Overrides

	bool StateMachine::onUpdate(double delta) {
		return m_state ? m_state->onUpdate(delta) : true;
	}

	void StateMachine::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		if (m_state) {
			m_state->draw(target, states);
		}
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
		m_state->setApplication(m_application);
		m_state->onActivated();
	}

	//-------------------------------------------------------------------------
	void StateMachine::setState(tk::State &state) {
		setState(&state);
	}

#pragma endregion

} // namespace tk
