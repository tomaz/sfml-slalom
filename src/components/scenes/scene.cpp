#include "scene.hpp"

namespace tk
{
#pragma region Subclass

	//-------------------------------------------------------------------------
	sf::Color Scene::backgroundColor() {
		return sf::Color::White;
	}

	//-------------------------------------------------------------------------
	sf::Vector2u Scene::viewSize(sf::Vector2u windowSize) {
		return windowSize;
	}

#pragma endregion

#pragma region Subclass

	//-------------------------------------------------------------------------
	void Scene::onActivated() {
		// Nothing to do by default.
	}

	//-------------------------------------------------------------------------
	void Scene::onDeactivated() {
		// Nothing to do by default.
	}

#pragma endregion

} // namespace tk
