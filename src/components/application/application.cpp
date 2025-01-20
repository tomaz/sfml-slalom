#include "application.hpp"
#include <scene.hpp>

namespace tk
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	Application::Application(
		std::string title,
		uint32_t width,
		uint32_t height,
		uint32_t antiAliasingLevel
	) noexcept
		: m_scene{ nullptr }
		, m_frameClock{}
		, m_view{ { 0, 0 }, { (float)width, (float)height } }
		, m_window{
			sf::VideoMode({ width, height }),
			title,
			sf::State::Windowed,
			sf::ContextSettings{ 0, 0, antiAliasingLevel }
		} {
		// Nothing else to do...
	}

	//-------------------------------------------------------------------------
	Application::~Application() {
		m_scene = nullptr;
	}

#pragma endregion

#pragma region Running

	//-------------------------------------------------------------------------
	void Application::run(Scene &scene) {
		setScene(scene);

		while (m_scene && m_window.isOpen()) {
			if (!handleEvents()) break;
			if (!update()) break;
			render();
		}
	}

	//-------------------------------------------------------------------------
	void Application::setScene(Scene &scene) {
		// Notify current scene it's ending.
		if (m_scene) {
			m_scene->onDeactivated();
			m_scene->setApplication(nullptr);
		}

		// Assign new scene.
		m_scene = &scene;

		// Setup new scene.
		m_scene->setApplication(this);
		m_scene->onActivated();

		// Ask the scene for its desired view size.
		auto viewSize  = m_scene->viewSize(m_window.getSize());
		auto viewSizeF = sf::Vector2f{ (float)viewSize.x, (float)viewSize.y };

		// Setup the view for the scene.
		m_view = sf::View(sf::FloatRect({ 0.f, 0.f }, viewSizeF));
		m_window.setView(m_view);

		// Reset other values.
		m_frameClock.restart();
	}

#pragma endregion

#pragma region Helpers

	//-------------------------------------------------------------------------
	bool Application::handleEvents() {
		while (const std::optional event = m_window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				m_window.close();
				return false;
			} else if (const auto *resized = event->getIf<sf::Event::Resized>()) {
				letterBoxView(resized->size.x, resized->size.y);
				return true;
			}
		}
		return true;
	}

	//-------------------------------------------------------------------------
	bool Application::update() {
		// Determine current frame timing.
		auto micros		= m_frameClock.restart().asMicroseconds();
		auto frameTime	= micros / 1000.0;
		auto frameDelta = micros / 1'000'000.0;
		auto fps		= micros > 0.0 ? 1'000'000.0 / micros : 0.0;

		// Ask scene to update.
		return m_scene->onUpdate(frameDelta);
	}

	//-------------------------------------------------------------------------
	void Application::render() {
		m_window.clear(m_scene->backgroundColor());
		m_window.draw(*m_scene);
		m_window.display();
	}

	//-------------------------------------------------------------------------
	void Application::letterBoxView(const float width, const float height) {
		auto windowRatio	   = width / height;
		auto viewRatio		   = (float)m_view.getSize().x / m_view.getSize().y;
		auto horizontalSpacing = windowRatio >= viewRatio;

		float sizeX = 1.f;
		float sizeY = 1.f;
		float posX	= 0.f;
		float posY	= 0.f;

		// Prepare for letterboxing.
		if (horizontalSpacing) {
			sizeX = viewRatio / windowRatio;
			posX  = (1 - sizeX) / 2.f;
		} else {
			sizeY = windowRatio / viewRatio;
			posY  = (1 - sizeY) / 2.f;
		}

		// Update viewport and assign view again to window (without this no change is applied).
		m_view.setViewport({ { posX, posY }, { sizeX, sizeY } });
		m_window.setView(m_view);
	}

#pragma endregion

} // namespace tk
