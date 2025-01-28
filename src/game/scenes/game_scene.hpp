#pragma once

#include <memory>

#include <SFML/Graphics.hpp>
#include <scene.hpp>
#include <skier_node.hpp>
#include <track_node.hpp>

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
		void onUpdate(double delta) override;

	protected:
#if DEBUG_DRAW_COLLISION_AREA
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
#endif

	private:
		void testHitWithPoles();

	private:
		TrackNode *m_track;
		SkierNode *m_skier;
	};

} // namespace tk::game
