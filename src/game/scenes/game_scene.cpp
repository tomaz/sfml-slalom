#include <application.hpp>
#include <track_node.hpp>

#include "game_scene.hpp"

namespace tk::game
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	GameScene::GameScene() noexcept
		: Scene::Scene() {
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	sf::Vector2u GameScene::viewSize(sf::Vector2u windowSize) {
		return sf::Vector2u{ windowSize.x / 2, windowSize.y / 2 };
	}

	//-------------------------------------------------------------------------
	void GameScene::onActivated() {
		auto track = std::make_unique<TrackNode>();
		track->initialize();
		track->populate(application()->viewSize(), 100);
		nodes().emplace_back(std::move(track));
	}

#pragma endregion

} // namespace tk::game
