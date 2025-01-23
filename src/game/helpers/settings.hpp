#pragma once

#include <SFML/Graphics.hpp>

namespace tk::game
{
	namespace settings
	{
		struct KeyboardSettings
		{
			sf::Keyboard::Scancode LeftKey	= sf::Keyboard::Scancode::A;
			sf::Keyboard::Scancode RightKey = sf::Keyboard::Scancode::D;
		} Keyboard;

		struct PlayerSettings
		{
			/** @brief Rotation speed in degrees per second. */
			double RotateSpeed = 100.0;

			/** @brief Maximum rotation in degrees from vertical. */
			double RotateMax = 80.0;

			/** @brief The angle relative from straight down direction within which the skier gains velocity. anything more than this and the skier will start loosing velocity. Velocity gain or decrease is linear compared to the angle and is maximal when going straight down (angle = 0), 0 when at this angle and negative when angle is higher. */
			double VelocityGainAngle = 25.0;

			/** @brief Maximum acceleration, when skiing straight down. In pixels per second. */
			double VelocityAcceleration = 1.0;

			/** @brief Maximum deceleration, when skiing at the maximum angle. In pixels per second. */
			double VelocityDeceleration = 4.0;

			/** @brief Minimum velocity when skiing at the max angle. In pixels per second. */
			double VelocityMin = 5.0;

			/** @brief Maximum velocity when skiing straight down slope (parallel). In pixels per second. */
			double VelocityMax = 30.0;
		};

		PlayerSettings Player{};

	} // namespace settings

} // namespace tk::game
