#include "game_scene.hpp"

double pos = 0.f;

namespace tk::game
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	GameScene::GameScene() noexcept {
		m_redFlagSheet = SpriteSheet::create();
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

		auto flag = std::make_unique<tk::SpriteNode>();
		flag->setSpriteSheet(m_redFlagSheet);
		flag->setAnimation(0.5, animator::Type::RepeatingBounce);
		flag->animate();

		// nodes().emplace_back(std::make_unique<tk::SpriteNode>(m_redFlagSheet, 1.0, animator::Type::RepeatingBounce));
		nodes().emplace_back(std::move(flag));
	}

	//-------------------------------------------------------------------------
	bool GameScene::onUpdate(double delta) {
		auto &flag = nodes().front();
		auto pos   = flag->getPosition();
		auto n	   = pos.x + 10.f * (float)delta;
		flag->setPosition({ n, n });
		return Scene::onUpdate(delta);
	}

#pragma endregion

} // namespace tk::game
