#pragma once

#include <SFML/Graphics.hpp>
#include <updatable.hpp>

namespace tk
{
	using namespace sf;

	/**
	 * @brief Defines a physical body that interacts to external forces.
	 *
	 * Physics body also implements hit detection. Hit detection is based on rectangles using AABB (Axis Aligned Bounding Box) method. However it does take into account the rotation of the object.
	 *
	 * Note: if subclasses override @see onUpdate, they must call base implementation otherwise physics will not be handled.
	 */
	class Physical
		: public Updatable
		, virtual public Transformable
	{
	public:
		Physical() noexcept						 = default;
		Physical(const Physical &other) noexcept = default;
		Physical(Physical &&other) noexcept		 = default;
		~Physical()								 = default;

	public:
		/**
		 * @brief Sets the acceleration in pixels per second.
		 */
		void setAcceleration(sf::Vector2<double> value) { m_acceleration = value; }

		/**
		 * @brief Adds the given value representing pixels per second to current acceleration.
		 */
		void updateAcceleration(sf::Vector2<double> diff) { m_acceleration += diff; }

		/**
		 * @brief Gets current acceleration in pixels per second.
		 */
		sf::Vector2<double> &acceleration() { return m_acceleration; }

	public:
		/**
		 * @brief Sets the velocity in pixels per second.
		 */
		void setVelocity(sf::Vector2<double> value) { m_velocity = value; }

		/**
		 * @brief Adds the given value representing pixels per second to current velocity.
		 */
		void updateVelocity(sf::Vector2<double> diff) { m_velocity += diff; }

		/**
		 * @brief Gets current velocity in pixels per second.
		 */
		sf::Vector2<double> &velocity() { return m_velocity; }

	protected:
		void onUpdate(double delta) override;

	private:
		sf::Vector2<double> m_acceleration{ 0.0, 0.0 };
		sf::Vector2<double> m_velocity{ 0.0, 0.0 };
	};

} // namespace tk
