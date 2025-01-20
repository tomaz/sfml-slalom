#pragma once

#include <list>
#include <node.hpp>
#include <state.hpp>

namespace tk
{
	class Application;

	/**
	 * @brief State manager.
	 *
	 * This is a simple @see State manager. Designed to be used as a base class as it keeps most functionality protected. There's only one active state at any given time. State is allowed to be nullptr which simply means update and draw will do nothing.
	 */
	class StateMachine
		: public Updatable
		, public Drawable
	{
	protected:
		StateMachine() noexcept = default;
		~StateMachine()			= default;

	public:
		bool onUpdate(double delta) override;

	protected:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	public:
		void setApplication(tk::Application *application) { m_application = application; }
		tk::Application *application() { return m_application; }

	protected:
		void setState(tk::State *state);
		void setState(tk::State &state);
		tk::State *state() { return m_state; }
		tk::NodesList &nodes() { return m_nodes; }

	private:
		tk::Application *m_application;
		tk::State *m_state;
		tk::NodesList m_nodes;
	};

} // namespace tk
