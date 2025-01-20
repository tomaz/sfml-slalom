#pragma once

#include <SFML/Graphics.hpp>
#include <state_machine.hpp>

namespace tk
{
	using namespace sf;

	class Application;

	/**
	 * @brief Declares a scene.
	 *
	 * Each scene is responsible for updating and rendering a particular aspect of the application. Subclass could implement main menu or game loop for example.
	 */
	class Scene
		: public Activatable
		, public StateMachine
	{
	protected:
		Scene() noexcept				   = default;
		Scene(const Scene &other) noexcept = default;
		Scene(Scene &&other) noexcept	   = default;
		virtual ~Scene()				   = default;

	public:
		/**
		 * @brief Provides the background color of this scene.
		 *
		 * Color is asked for on every tick, so subclass can animate background if needed.
		 */
		virtual sf::Color backgroundColor();

		/**
		 * @brief Provides the desired size of a view.
		 *
		 * This is called when the scene becomes active. It allows the subclass to specify its desired size in the window. The parameter is window size. Default value returns the same size but subclass that wants for example have 2x resolution, can return half the size.
		 *
		 * @param windowSize Window size.
		 * @return Returns the desired size of the scene view.
		 */
		virtual sf::Vector2u viewSize(sf::Vector2u windowSize);

	public:
		void onActivated() override;
		void onDeactivated() override;
	};

} // namespace tk
