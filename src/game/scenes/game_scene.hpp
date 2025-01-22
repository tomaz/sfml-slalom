#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <scene.hpp>

namespace tk::game
{
	/**
	 * @brief Implements the main game loop.
	 */
	class GameScene : public Scene
	{
	public:
		GameScene() noexcept;
		GameScene(const GameScene &other) noexcept = default;
		GameScene(GameScene &&other) noexcept	   = default;
		~GameScene()							   = default;

	public:
		sf::Vector2u viewSize(sf::Vector2u windowSize) override;
		void onActivated() override;
	};

} // namespace tk::game
