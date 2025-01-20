#include "game_scene.hpp"

namespace tk::game
{
#pragma region Overrides

	sf::Vector2u GameScene::viewSize(sf::Vector2u windowSize) {
		return sf::Vector2u{ windowSize.x / 2, windowSize.y / 2 };
	}

	//-------------------------------------------------------------------------
	void GameScene::onActivated() {
		m_redFlagSheet.load("flag-red");
		nodes().emplace_back(std::make_unique<tk::SpriteNode>(&m_redFlagSheet));
		nodes().front()->setPosition({ 8.f, 8.f });
	}

	//-------------------------------------------------------------------------
	bool GameScene::onUpdate(double delta) {
		return Scene::onUpdate(delta);
	}

#pragma endregion

} // namespace tk::game
