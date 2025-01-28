#pragma once

#include <aabb_collision_tester.hpp>
#include <node.hpp>
#include <spritesheet.hpp>

namespace tk::game
{
	/**
	 * @brief Represents the skier, aka the player.
	 */
	class SkierNode
		: public Node
	{
	public:
		SkierNode() noexcept;
		SkierNode(const SkierNode &other) noexcept = default;
		SkierNode(SkierNode &&other) noexcept	   = default;
		~SkierNode()							   = default;

	public:
		tk::AABBCollisionTester &collisionTester() { return m_collisionTester; }

	protected:
		void onUpdate(double delta) override;

	private:
		void rotateSkier(double delta, double direction);
		void updateVelocity();

	private:
		tk::AABBCollisionTester m_collisionTester;
		tk::shared_SpriteSheet m_spritesheet;
		double m_maxSpeed{ 0.0 };
		double m_angle{ 0.0 };
	};

} // namespace tk::game
