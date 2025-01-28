#include <iostream>
#include <type_traits>

#include <application.hpp>
#include <settings.hpp>

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
		m_track = track.get();

		// Create the skier.
		auto skier = std::make_unique<SkierNode>();
		skier->setPosition(track->startCenter());
		m_skier = skier.get();

		// We need to postpone adding nodes as we need to query them for some data and std::move makes the unique_ptr null.
		nodes().emplace_back(std::move(track));
		nodes().emplace_back(std::move(skier));
	}

	//-------------------------------------------------------------------------
	void GameScene::onUpdate(double delta) {
		// Update all our nodes with subclass.
		Scene::onUpdate(delta);

		// Handle scene updates. In case of error, test functions throw Status which we then set.
		// Note: according to my testing happy case doesn't affect performance (I got basically the same FPS). But throwing an exception implies runtime cost. However since this is only used to indicate end of update loop, we're not affecting normal gameplay performance.
		// This document provides some insights into modern C++ exception implementation: https://www.open-std.org/jtc1/sc22/wg21/docs/TR18015.pdf
		try {
			testHitWithPoles();
		} catch (updatable::Status &status) {
			setStatus(status);
		}
	}

#if DEBUG_DRAW_COLLISION_AREA
	//-------------------------------------------------------------------------
	void GameScene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		Scene::draw(target, states);

		auto &poles{ m_track->poles() };
		for (auto &pole : poles) {
			target.draw(pole->tester.rectangle());
		}

		auto &skier{ m_skier->collisionTester() };
		target.draw(skier.rectangle());
	}
#endif

#pragma endregion

#pragma region Helpers

	//-------------------------------------------------------------------------
	void GameScene::testHitWithPoles() {
		auto &poles{ m_track->poles() };
		auto &skier{ m_skier->collisionTester() };

		auto showCollision = [&](track::Pole *pole) {
			pole->node->sprite()->setColor(sf::Color::Black);
		};

		// At the moment we always compare with all nodes. Since the poles list is provided from top to bottom, we could optimize this to only compare until we find a pole below possible hit area.
		for (auto &pole : poles) {
			auto result = pole->tester.test(skier);

			if (result == collision::Result::Collision) {
				showCollision(pole.get());
				throw updatable::Status::Paused;
			} else if (pole->isRight && result == collision::Result::OtherRight) {
				showCollision(pole.get());
				throw updatable::Status::Paused;
			} else if (pole->isLeft && result == collision::Result::OtherLeft) {
				showCollision(pole.get());
				throw updatable::Status::Paused;
			}
		}
	}

#pragma endregion

} // namespace tk::game
