#pragma once

#include <SFML/Graphics.hpp>

namespace tk
{
	class Scene;

	/**
	 * @brief The main application class.
	 *
	 * This is the wrapper over the application window.
	 *
	 * There's only one instance allowed and @see create() takes care of that.
	 */
	class Application
	{
	public:
		/**
		 * @brief Creates a new application instance, or returns exiting one.
		 *
		 * @param title Title of the window.
		 * @param width Width of the window in pixels.
		 * @param height Height of the window in pixels.
		 * @param antiAliasingLevel Anti aliasing level.
		 */
		static std::shared_ptr<Application> create(
			std::string title,
			uint32_t width			   = 800u,
			uint32_t height			   = 600u,
			uint32_t antiAliasingLevel = 16
		);

		~Application();

	private:
		Application(std::string title, uint32_t width, uint32_t height, uint32_t antiAliasingLevel) noexcept;

	public:
		/**
		 * @brief Runs the application loop.
		 *
		 * @param scene The scene to start running with.
		 */
		void run(Scene &scene);

		/**
		 * @brief Sets the next scene.
		 *
		 * @param scene The scene to run with from now on.
		 */
		void setScene(Scene &scene);

		/**
		 * @brief Returns current view size in pixels.
		 */
		sf::Vector2f viewSize() { return m_viewSize; }

	private:
		/**
		 * @brief Handles all window events.
		 *
		 * @return Returns true if further processing is needed, false to exit.
		 */
		bool handleEvents();

		/**
		 * @brief Updates internal data and current scene.
		 *
		 * @return Returns true if further processing is needed, false to exit.
		 */
		bool update();

		/**
		 * @brief Renders all the data to the window.
		 */
		void render();

		/**
		 * @brief Updates view to maintain aspect ratio but show letter box if needed.
		 *
		 * @param width Width of the window.
		 * @param height Height of the window.
		 */
		void letterBoxView(const float width, const float height);

	private:
		sf::RenderWindow m_window;
		sf::View m_view;
		sf::Vector2f m_viewSize;
		sf::Clock m_frameClock;
		tk::Scene *m_scene;
	};

} // namespace tk
