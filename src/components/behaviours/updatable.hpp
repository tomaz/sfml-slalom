#pragma once

namespace tk
{
	namespace updatable
	{
		enum class Status {
			Active,
			Paused,
			Completed
		};
	}

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
		Updatable(updatable::Status status) noexcept;

		Updatable() noexcept					   = default;
		Updatable(const Updatable &other) noexcept = default;
		Updatable(Updatable &&other) noexcept	   = default;
		~Updatable()							   = default;

	protected:
		/**
		 * @brief Called when object needs to update.
		 *
		 * @param delta Delta for multiplying all measures with.
		 */
		virtual void onUpdate(double delta) = 0;

		/**
		 * @brief Called when status changes.
		 *
		 * @param status The new status.
		 */
		virtual void onStatus(updatable::Status status);

	public:
		/**
		 * @brief Updates the object. If needed also updates @see status().
		 *
		 * @param delta Delta for multiplying all measures with.
		 */
		void update(double delta);

	public:
		void setStatus(updatable::Status status);
		updatable::Status status() { return m_status; }

	private:
		updatable::Status m_status{ updatable::Status::Active };
	};

} // namespace tk
