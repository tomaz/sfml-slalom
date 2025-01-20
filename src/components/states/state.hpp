#pragma once

#include <SFML/Graphics.hpp>
#include <activatable.hpp>
#include <updatable.hpp>

namespace tk
{
	using namespace sf;

	class Application;

	/**
	 * @brief Declares a state.
	 *
	 * State is a way to split larger algorithm into smaller chunks. States are @see Activatable but also @see Updatable and @see Drawable as convenience. To simplify states handling, you can override your class from @see StateMachine.
	 */
	class State
		: public Activatable
		, public Updatable
		, public Drawable
	{
	public:
		/**
		 * @brief Default constructor.
		 */
		State();

		/**
		 * @brief Default dtor
		 */
		virtual ~State();

	public:
		void onActivated() override;
		void onDeactivated() override;
		bool onUpdate(double delta) override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	public:
		void setApplication(tk::Application *application) { m_application = application; }
		tk::Application *application() { return m_application; }

	private:
		tk::Application *m_application;
	};

} // namespace tk
