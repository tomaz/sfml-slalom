#pragma once

#include <SFML/Graphics.hpp>
#include <list>

namespace tk
{
	namespace collision
	{
		/**
		 * @brief Collision result. If there's collision the value can only be @see Collision, but otherwise it may be a bit field of 1 or 2 values (for example OtherLeft | OtherTop).
		 */
		enum class Result {
			/** @brief Comparison was with non-hittable object (its width or height is 0). */
			Unknown = 0,

			/** @brief The 2 objects compared are in collision! */
			Collision = 1 << 0,

			/** @brief There's no hit between objects; other object is vertically within hit area but horizontally to the left of it. */
			OtherLeft = 1 << 1,

			/** @brief There's no hit between objects; other object is vertically within hit area but horizontally to the right of it. */
			OtherRight = 1 << 2,

			/** @brief There's no hit between objects; other object is horizontally within hit area but vertically to the top of it. */
			OtherTop = 1 << 3,

			/** @brief There's no hit between objects; other object is horizontally within hit area but vertically to the bottom of it. */
			OtherBottom = 1 << 4,
		};

		inline Result operator|(Result lhs, Result rhs) {
			return static_cast<Result>(std::underlying_type<Result>::type(lhs) | std::underlying_type<Result>::type(rhs));
		}

		inline Result operator&(Result lhs, Result rhs) {
			return static_cast<Result>(std::underlying_type<Result>::type(lhs) & std::underlying_type<Result>::type(rhs));
		}

		inline Result &operator|=(Result &a, Result b) {
			return a = a | b;
		}

	} // namespace collision

	/**
	 * @brief Implements AABB (Axis Aligned Bounding Box) collision testing.
	 *
	 * This is meant to be used on target objects with composition. Each object that wants to be tested for collision should have a member variable of this class. Typically the parent object is also @see sf::Transformable which is needed for updating the position of the collision area.
	 */
	class AABBCollisionTester
	{
	public:
		AABBCollisionTester() noexcept;
		AABBCollisionTester(const AABBCollisionTester &other) noexcept = default;
		AABBCollisionTester(AABBCollisionTester &&other) noexcept	   = default;
		~AABBCollisionTester()										   = default;

	public:
		/**
		 * @brief Tests collision with another object.
		 *
		 * @param other The other object to test collision with.
		 * @return The result of the collision test.
		 */
		collision::Result test(const AABBCollisionTester &other) const;

		/**
		 * @brief Updates internal data according to the given transformable.
		 *
		 * This must be called after parent object updates. It's prerequisite for collision testing.
		 */
		void update(sf::Transformable &parent);

	public:
		/**
		 * @brief Changes collision appearance when drawing.
		 *
		 * @param fill Fill color of the rectangle.
		 * @param outline The outline of the rectangle.
		 * @param thickness Thickness of the rectangle's outline.
		 */
		void setAppearance(
			sf::Color fill	  = sf::Color::Transparent,
			sf::Color outline = sf::Color::Magenta,
			float thickness	  = 1.f
		);

		/**
		 * @brief Sets collistion area in local coordinates of the parent object.
		 *
		 * If width or height is zero or negative, collisions with this object are disabled.
		 */
		void setArea(const sf::FloatRect &area);

		/**
		 * @brief Gets collision area in local coordinates of the parent object.
		 */
		sf::FloatRect area() const { return m_area; }

		/**
		 * @brief Returns collision rectangle in world coordinate using the parent object's transform.
		 */
		sf::RectangleShape rectangle() const { return m_shape; }

		/**
		 * @brief Determines if this collision object is enabled or not.
		 *
		 * If collision is disabled, update is ignored and collision test is always negative.
		 */
		bool isEnabled() const { return m_area.size.x > 0 && m_area.size.y > 0; }

	private:
		/**
		 * @brief Returns the given point in global coordinate, taking into account current transformation.
		 */
		sf::Vector2f transformedPoint(int index) const;

	private:
		sf::FloatRect m_area;
		sf::RectangleShape m_shape;
	};

} // namespace tk
