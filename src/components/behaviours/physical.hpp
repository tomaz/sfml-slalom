#pragma once

#include <SFML/Graphics.hpp>
#include <updatable.hpp>

namespace tk
{
	using namespace sf;

	/**
	 * @brief Defines a physical body that interacts to external forces.
	 *
	 * Note: if subclasses override @see onUpdate, they must call base implementation otherwise physics will not be handled.
	 */
	class Physical
		: public Updatable
		, public Transformable
	{
	public:
		Physical() noexcept						 = default;
		Physical(const Physical &other) noexcept = default;
		Physical(Physical &&other) noexcept		 = default;
		~Physical()								 = default;

	public:
		void setAcceleration(sf::Vector2<double> value) { m_acceleration = value; }
		void updateAcceleration(sf::Vector2<double> diff) { m_acceleration += diff; }

		void setVelocity(sf::Vector2<double> value) { m_velocity = value; }
		void updateVelocity(sf::Vector2<double> diff) { m_velocity += diff; }

		sf::Vector2<double> &acceleration() { return m_acceleration; }
		sf::Vector2<double> &velocity() { return m_velocity; }

	protected:
		void onUpdate(double delta) override;

	private:
		sf::Vector2<double> m_acceleration{ 0.0, 0.0 };
		sf::Vector2<double> m_velocity{ 0.0, 0.0 };
	};

} // namespace tk
