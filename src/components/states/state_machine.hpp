#pragma once

#include <state.hpp>

namespace tk
{
	/**
	 * @brief State manager.
	 *
	 * This is a simple @see State manager. Designed to be used as a base class as it keeps most functionality protected.
	 *
	 * Note: there's only one active state at any given time. State is allowed to be nullptr which simply means update and draw will do nothing.
	 */
	class StateMachine
		: public Updatable
		, public Drawable
	{
	protected:
		/**
		 * @brief Default constructor.
		 */
		StateMachine();

		/**
		 * @brief Default dtor.
		 */
		~StateMachine();

	public:
		bool onUpdate(double delta) override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	protected:
		void setState(tk::State *state);
		void setState(tk::State &state);
		tk::State *state() { return m_state; }

	protected:
		void setApplication(tk::Application *application) { m_application = application; }
		tk::Application *application() { return m_application; }

	private:
		tk::Application *m_application;
		tk::State *m_state;
	};

} // namespace tk
