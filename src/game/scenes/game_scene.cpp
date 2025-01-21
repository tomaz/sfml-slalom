#include "game_scene.hpp"

namespace tk::game
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	GameScene::GameScene() noexcept
		: Scene::Scene() {
		m_redFlagSheet	= SpriteSheet::create();
		m_blueFlagSheet = SpriteSheet::create();
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	sf::Vector2u GameScene::viewSize(sf::Vector2u windowSize) {
		return sf::Vector2u{ windowSize.x / 2, windowSize.y / 2 };
	}

	//-------------------------------------------------------------------------
	void GameScene::onActivated() {
		m_redFlagSheet->load("flag-red");
		m_blueFlagSheet->load("flag-blue");

		auto redFlag = std::make_unique<tk::SpriteNode>();
		redFlag->setSpriteSheet(m_redFlagSheet);
		redFlag->setAnimation(0.5, animator::Type::RepeatingBounce);
		redFlag->setPosition({ 0.f, 0.f });
		redFlag->setVelocity({ 10.0, 10.0 });

		auto blueFlag = std::make_unique<tk::SpriteNode>();
		blueFlag->setSpriteSheet(m_blueFlagSheet);
		blueFlag->setAnimation(0.5, animator::Type::RepeatingBounce);
		blueFlag->setPosition({ 30.f, 0.f });
		blueFlag->setVelocity({ 10.0, 10.0 });

		nodes().emplace_back(std::move(redFlag));
		nodes().emplace_back(std::move(blueFlag));
	}

#pragma endregion

} // namespace tk::game
