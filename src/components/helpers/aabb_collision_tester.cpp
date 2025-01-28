#include "aabb_collision_tester.hpp"

#define POINTS_COUNT 4

namespace tk
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	AABBCollisionTester::AABBCollisionTester() noexcept
		: m_shape{} {
		// Use default appearance.
		setAppearance();
	}

#pragma endregion

#pragma region Collision handling

	//-------------------------------------------------------------------------
	collision::Result AABBCollisionTester::test(const AABBCollisionTester &other) const {
		if (m_area.size.x == 0.f || m_area.size.y == 0.f) return collision::Result::Unknown;
		if (other.m_area.size.x == 0.f || other.m_area.size.y == 0.f) return collision::Result::Unknown;

		// Based off https://khorbushko.github.io/article/2021/07/15/the-area-polygon-or-how-to-detect-line-segments-intersection.html
		for (int i1 = 0; i1 < POINTS_COUNT; i1++) {
			int i1e = (i1 + 1) % POINTS_COUNT;
			auto p0{ transformedPoint(i1) };
			auto p1{ transformedPoint(i1e) };

			for (int i2 = 0; i2 < POINTS_COUNT; i2++) {
				int i2e = (i2 + 1) % POINTS_COUNT;
				auto p2{ other.transformedPoint(i2) };
				auto p3{ other.transformedPoint(i2e) };

				float denominator = (p3.x - p2.x) * (p1.y - p0.y) - (p3.y - p2.y) * (p1.x - p0.x);
				if (denominator == 0.f) continue;

				float ua = (p3.y - p2.y) * (p0.x - p2.x) - (p3.x - p2.x) * (p0.y - p2.y);
				float ub = (p1.y - p0.y) * (p0.x - p2.x) - (p1.x - p0.x) * (p0.y - p2.y);

				if (denominator < 0.f) {
					ua			= -ua;
					ub			= -ub;
					denominator = -denominator;
				}

				if (ua < 0.f || ua > denominator) continue;
				if (ub < 0.f || ub > denominator) continue;

#if 0
				// Calculate and prepare intersection point.
				float uad			   = ua / denominator;
				collisionPoint.x = p0.x + uad * (p1.x - p0.x);
				collisionPoint.y = p0.y + uad * (p1.y - p0.y);
#endif

				// Arriving here means we have a collision.
				return collision::Result::Collision;
			}
		}

		// There's no hit, calculate result flags.
		auto us	  = m_shape.getGlobalBounds().getCenter();
		auto them = other.m_shape.getGlobalBounds().getCenter();

		collision::Result result = static_cast<collision::Result>(0);

		if ((int)them.y == (int)us.y) {
			if (us.x < them.x) {
				result |= collision::Result::OtherRight;
			} else if (us.x > them.x) {
				result |= collision::Result::OtherLeft;
			}
		}

		if ((int)them.x == (int)us.x) {
			if (us.y < them.y) {
				result |= collision::Result::OtherBottom;
			} else if (us.y > them.y) {
				result |= collision::Result::OtherTop;
			}
		}

		return result;
	}

	//-------------------------------------------------------------------------
	void AABBCollisionTester::update(sf::Transformable &parent) {
		m_shape.setPosition(parent.getPosition());
		m_shape.setScale(parent.getScale());
		m_shape.setRotation(parent.getRotation());
	}

#pragma endregion

#pragma region Getters & setters

	//-------------------------------------------------------------------------
	void AABBCollisionTester::setAppearance(sf::Color fill, sf::Color color, float thickness) {
		m_shape.setFillColor(fill);
		m_shape.setOutlineColor(color);
		m_shape.setOutlineThickness(thickness);
	}

	//-------------------------------------------------------------------------
	void AABBCollisionTester::setArea(const sf::FloatRect &area) {
		m_area = area;
		m_shape.setOrigin(-area.position); // origin goes the other way compared to position...
		m_shape.setSize(area.size);
	}

	//-------------------------------------------------------------------------
	sf::Vector2f AABBCollisionTester::transformedPoint(int index) const {
		return m_shape.getTransform().transformPoint(m_shape.getPoint(index));
	}

#pragma endregion

} // namespace tk
