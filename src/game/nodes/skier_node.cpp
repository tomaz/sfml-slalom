#include <iostream>

#include <settings.hpp>
#include <sprite_node.hpp>

#include "skier_node.hpp"

namespace tk::game
{
#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	SkierNode::SkierNode() noexcept
		: Node::Node() {
		// Setup defaults.
		m_maxSpeed = settings::Player.VelocityMax;

		// Create the spreadsheet.
		m_spritesheet = SpriteSheet::create("skier");
		auto size	  = m_spritesheet->frames().front().size;

		// Create the sprite. We could override this class from SpriteNode as well, but this way we don't expose sprite specific functionality to external code.
		auto sprite = std::make_unique<SpriteNode>();
		sprite->setSpriteSheet(m_spritesheet);
		sprite->setFrame(0);
		sprite->setPosition({ -size.x / 2.f, -size.y / 2.f }); // so rotations will work seamlessly
		nodes().emplace_back(std::move(sprite));
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	void SkierNode::onUpdate(double delta) {
		Node::onUpdate(delta);

		if (sf::Keyboard::isKeyPressed(settings::Keyboard.LeftKey)) {
			// Turn left.
			rotateSkier(delta, -1.0);
		} else if (sf::Keyboard::isKeyPressed(settings::Keyboard.RightKey)) {
			// Turn right.
			rotateSkier(delta, 1.0);
		}

		// Update the skier.
		updateVelocity();
	}

#pragma endregion

#pragma region Helpers

	//-------------------------------------------------------------------------
	void SkierNode::rotateSkier(double delta, double direction) {
		static auto rotationSpeed = settings::Player.RotateSpeed;
		static auto maxRotation	  = settings::Player.RotateMax;
		static auto Vmin		  = settings::Player.VelocityMin;
		static auto Vmax		  = settings::Player.VelocityMax;

		// Calculate new angle.
		m_angle += (direction * rotationSpeed) * delta;

		// Restrict it to both limits.
		if (m_angle > maxRotation) {
			m_angle = maxRotation;
		} else if (m_angle < -maxRotation) {
			m_angle = -maxRotation;
		}

		// Calculate maximum velocity at this angle.
		m_maxSpeed = Vmax * std::abs(std::cos(sf::degrees(m_angle).asRadians()));
		if (m_maxSpeed < Vmin) {
			m_maxSpeed = Vmin;
		} else if (m_maxSpeed > Vmax) {
			m_maxSpeed = Vmax;
		}

		// Rotate the sprite.
		setRotation(sf::degrees(m_angle));
	}

	//-------------------------------------------------------------------------
	void SkierNode::updateVelocity() {
		static auto gainAngle = settings::Player.VelocityGainAngle;
		static auto maxAngle  = settings::Player.RotateMax;

		static auto Amax = settings::Player.VelocityAcceleration;
		static auto Amin = settings::Player.VelocityDeceleration;
		static auto Vmin = settings::Player.VelocityMin;

		auto acceleration{ 0.0 };
		auto angle{ std::abs(m_angle) };

		if (angle <= gainAngle) {
			// Player is accelerating. Acceleration is max at angle 0 and none (0) at gain angle. Linear in between.
			auto angleDiff = gainAngle - angle;
			acceleration   = angleDiff * Amax;
		} else {
			// Player is decelerating. Deceleration is none (0) at gain angle and max at gain angle. Linear in between.
			auto rangleDiff = maxAngle - gainAngle;
			auto angleDiff	= angle - gainAngle;
			acceleration	= -angleDiff / rangleDiff * Amin;
		}

		// Prepare the angle; it's the reverse of what we keep.
		sf::Angle vectorAngle{ sf::degrees(m_angle) };

		// Apply acceleration in the direcion of the skiing.
		sf::Vector2<double> normalized{ 0.0, acceleration };
		sf::Vector2<double> rotated{ normalized.rotatedBy(vectorAngle) };
		setAcceleration(rotated);

		// If velocity is below or above the limit, reset it.
		// Note: we still have to manage acceleration/deceleration since that's how we'll change velocity from the limit.
		auto speed = velocity().length();
		if (speed < Vmin) {
			speed = Vmin;
		} else if (speed > m_maxSpeed) {
			speed = m_maxSpeed;
		}
		normalized = { 0.0, speed };
		rotated	   = { normalized.rotatedBy(vectorAngle) };
		setVelocity(rotated);
	}

#pragma endregion

} // namespace tk::game
