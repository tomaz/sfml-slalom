#include "scene.hpp"

namespace tk
{
#pragma region Constructor & destruction

	//-------------------------------------------------------------------------
	Scene::Scene(uint32_t width, uint32_t height) noexcept
		: m_width{ width }
		, m_height{ height } {
	}

	//-------------------------------------------------------------------------
	Scene::~Scene() {
		// Nothing to do by default.
	}

#pragma endregion

#pragma region Subclass

	//-------------------------------------------------------------------------
	sf::Color Scene::backgroundColor() {
		return sf::Color::White;
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	void Scene::onActivated() {
		// Nothing to do by default.
	}

	//-------------------------------------------------------------------------
	void Scene::onDeactivated() {
		// Nothing to do by default.
	}

	//-------------------------------------------------------------------------
	bool Scene::onUpdate(double delta) {
		return StateMachine::onUpdate(delta);
	}

	//-------------------------------------------------------------------------
	void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		StateMachine::draw(target, states);
	}

#pragma endregion

#pragma region Getters & setters

	//-------------------------------------------------------------------------
	void Scene::setApplication(Application *application) {
		StateMachine::setApplication(application);
	}

	//-------------------------------------------------------------------------
	Application *Scene::application() {
		return StateMachine::application();
	}

#pragma endregion

} // namespace tk
