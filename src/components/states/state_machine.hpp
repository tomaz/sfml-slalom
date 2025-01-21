#pragma once

#include <list>
#include <memory>

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
		StateMachine() noexcept							 = default;
		StateMachine(const StateMachine &other) noexcept = default;
		StateMachine(StateMachine &&other) noexcept		 = default;
		~StateMachine()									 = default;

	protected:
		bool onUpdate(double delta) override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	public:
		void setApplication(std::shared_ptr<tk::Application> application);
		tk::Application *application();

	protected:
		void setState(tk::State *state);
		void setState(tk::State &state);
		tk::State *state() { return m_state; }
		tk::NodesList &nodes() { return m_nodes; }

	private:
		std::weak_ptr<tk::Application> m_application;
		tk::State *m_state;
		tk::NodesList m_nodes;
	};

} // namespace tk
