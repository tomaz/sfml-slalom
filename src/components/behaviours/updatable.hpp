#pragma once

namespace tk
{
	/**
	 * @brief Specifies an object that is updatable.
	 *
	 * Updatable objects are called on each event loop tick.
	 */
	class Updatable
	{
	protected:
		/**
		 * @brief Constructor that allows setting initial active flag.
		 */
		Updatable(bool active) noexcept;

		Updatable() noexcept					   = default;
		Updatable(const Updatable &other) noexcept = default;
		Updatable(Updatable &&other) noexcept	   = default;
		~Updatable()							   = default;

	protected:
		/**
		 * @brief Called when object needs to update.
		 *
		 * @param delta Delta for multiplying all measures with.
		 * @return Returns true if run loop can continue, false otherwise.
		 */
		virtual bool onUpdate(double delta) = 0;

		/**
		 * @brief Called when active status changes.
		 */
		virtual void onActive(bool active);

	public:
		/**
		 * @brief Called when object needs to update.
		 *
		 * @param delta Delta for multiplying all measures with.
		 * @return Returns true if run loop can continue, false otherwise.
		 */
		bool update(double delta);

	public:
		void setActive(bool active);
		bool active() { return m_active; }

	private:
		bool m_active{ true };
	};

} // namespace tk
