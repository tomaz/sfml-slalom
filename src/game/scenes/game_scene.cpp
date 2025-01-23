#include <application.hpp>
#include <skier_node.hpp>
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
		// Create the track.
		auto track = std::make_unique<TrackNode>();
		track->populate(application()->viewSize(), 100);

		// Create the skier.
		auto skier = std::make_unique<SkierNode>();
		skier->setPosition(track->startCenter());

		// We need to postpone adding nodes as we need to query them for some data and std::move makes the unique_ptr null.
		nodes().emplace_back(std::move(track));
		nodes().emplace_back(std::move(skier));
	}

#pragma endregion

} // namespace tk::game
