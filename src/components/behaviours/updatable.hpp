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
	public:
		/**
		 * @brief Called when object needs to update.
		 *
		 * @param delta Delta for multiplying all measures with.
		 * @return Returns true if run loop can continue, false otherwise.
		 */
		virtual bool onUpdate(double delta) = 0;
	};

} // namespace tk
