#pragma once

#include <functional>
#include <vector>

#include <updatable.hpp>

namespace tk
{
	namespace animator
	{
		/** @brief Callback called during animation lifetime. */
		using Callback = std::function<void(double)>;

		/**
		 * @brief Internal data for storing progress callbacks.
		 */
		struct ProgressData
		{
			double progress;
			Callback callback;
		};

		enum class Type {
			/** @brief Animation only happens once from 0 to 1, then completes. */
			OneShot,

			/** @brief Animation happens from 0 to 1, then back to 0, then completes. */
			OneShotBounce,

			/** @brief Animation is repeating 0 to 1, 0 to 1 etc. until manually stopped. */
			Repeating,

			/** @brief Animation is repeating 0 to 1 to 0 to 1 etc. until manually stopped. */
			RepeatingBounce
		};
	} // namespace animator

	/**
	 * @brief Manages changes through time.
	 *
	 * To use, create an instance, assign callbacks you're interested in, then call @see update() during updating. You also have to @see start() the animator otherwise @see update() will be ignored.
	 */
	class Animator
		: public Updatable
	{
	public:
		/**
		 * @brief Default constructor.
		 *
		 * @param time Time of the whole animation.
		 * @param type Type of the animation to use.
		 */
		Animator(
			double time			= 0.0,
			animator::Type type = animator::Type::OneShot
		);

	public:
		/**
		 * @brief Sets multiple callbacks, each the given @see diff progress apart.
		 *
		 * Difference is provided in 0..1 ratio. This always installs progress at 0, then as many as can fit to 1, each offset from previous by the given @see diff ratio. However it's not guaranteed that the progress at 1 will also be added, it all depends on whether 1 is divisible by given @see diff.
		 *
		 * Note: any pre-existing callbacks are cleared before adding new ones!
		 *
		 * Examples for diff:
		 * - 0.5: installs callbacks at 0.0, 0.5 and 1.0
		 * - 0.3: installs callbacks at 0.0, 0.3, 0.6, 0.9 (but not 1.0)
		 *
		 * @param diff Difference between callbacks.
		 * @param callback Callback to be called.
		 */
		void addCallbacksEvery(double diff, animator::Callback callback);

		/**
		 * @brief Sets given number of callbacks.
		 *
		 * Difference is evenly divided within the whole range. This always installs progress at 0 and 1.
		 *
		 * Note: any pre-existing callbacks are cleared before adding new ones!
		 *
		 * Examples for count:
		 * - 0: removes all callbacks but doesn't install any new one!
		 * - 1: special case, only installs callback at 0.0
		 * - 2: installs callbacks at 0.0 and 1.0
		 * - 3: installs callbacks at 0.0, 0.5 and 1.0
		 *
		 * @param count Number of callbacks to install.
		 * @param callback Callback to be called.
		 */
		void addCallbacksCount(int count, animator::Callback callback);

		/**
		 * @brief Adds the given callback to be called when the time reaches the given ratio.
		 *
		 * Note: only 1 callback is allowed per any given progress. If adding a second one for exactly the same progress, the previous one will be removed. This can even be used to remove existing callback at the given progress by passing in nullptr for callback (but it's preferred to use @see removeCallback() instead).
		 *
		 * @param progress Progress as ratio of the total time (0..1).
		 * @param callback Callback to be called at the given point in time.
		 */
		void addCallback(double progress, animator::Callback callback);

		/**
		 * @brief Removes previously added callback at the given progress.
		 *
		 * If there's no callback associated with the given progress, nothing happens.
		 *
		 * @param progress Progress as ratio of the total time (0..1).
		 */
		void removeCallback(double progress);

	public:
		/**
		 * @brief Starts the animator.
		 */
		void start();

		/**
		 * @brief Stops or pauses the animator.
		 *
		 * @param reset If true, also resets the time to 0.
		 */
		void stop(bool reset = true);

		/**
		 * @brief Resets the time to 0 but doesn't change it's active state.
		 */
		void reset();

	protected:
		bool onUpdate(double delta) override;

	public:
		void setType(animator::Type type) { m_type = type; }
		void setTime(double time) { m_total = time; }
		int32_t current() { return m_currentIndex; }

	private:
		animator::Type m_type;
		double m_total;
		double m_time;
		double m_prefix;

		double m_nextProgress;
		int32_t m_currentIndex;
		std::vector<animator::ProgressData>::iterator m_current;
		std::vector<animator::ProgressData> m_callbacks;
	};

} // namespace tk
