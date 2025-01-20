#pragma once

#include <SFML/Graphics.hpp>
#include <activatable.hpp>
#include <updatable.hpp>

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
		, public Updatable
		, public Drawable
	{
	protected:
		/**
		 * @brief Default constructor.
		 *
		 * @param width Width of the scene in pixels.
		 * @param height Height of the scene in pixels.
		 */
		Scene(uint32_t width = 800u, uint32_t height = 600u) noexcept;

	public:
		/**
		 * @brief Default destructor.
		 */
		virtual ~Scene();

	public:
		/**
		 * @brief Provides the background color of this scene.
		 *
		 * Color is asked for on every tick, so subclass can animate background if needed.
		 */
		virtual sf::Color backgroundColor();

	public:
		void onActivated() override;
		void onDeactivated() override;
		bool onUpdate(double delta) override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	public:
		void setApplication(Application *application) { m_application = application; }
		Application *application() { return m_application; }
		uint32_t width() { return m_width; }
		uint32_t height() { return m_height; }

	private:
		tk::Application *m_application;
		uint32_t m_width;
		uint32_t m_height;
	};

} // namespace tk
