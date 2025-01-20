
#pragma once

namespace tk
{
	/**
	 * @brief Specifies an object that is activatable.
	 *
	 * Activatable objects are informed when they become activated and deactivated.
	 */
	class Activatable
	{
	public:
		/**
		 * @brief Called when object is being activated.
		 */
		virtual void onActivated() = 0;

		/**
		 * @brief Called when object is being deactivated.
		 */
		virtual void onDeactivated() = 0;
	};

} // namespace tk
