#include <memory>
#include <random>

#include <range.hpp>

namespace tk
{
	/**
	 * @brief Random values generator.
	 */
	class Randomizer
	{
	public:
		Randomizer() noexcept = default;
		~Randomizer()		  = default;

	public:
		/**
		 * @brief Gets a random integer number within the limits of the given @see Range.
		 */
		template<class T>
		int getInt(const Range<T> &range) { return getInt(range.min, range.max); }

		/**
		 * @brief Gets a random integer number between the givin limits.
		 */
		int getInt(int min, int max);

		/**
		 * Gets a random integer number between the given minimum and max which is min+range;
		 */
		int getIntRange(int min, int range);

		/**
		 * @brief Gets a random real number within the limits of the given @see Range.
		 */
		template<class T>
		int getReal(const Range<T> &range) { return getReal(range.min, range.max); }

		/**
		 * @brief Gets a random real number between the given limits.
		 */
		double getReal(double min, double max);

		/**
		 * @brief Gets a random real number between the given minimum and max which is min+range.
		 */
		double getRealRange(double min, double range);

	private:
		std::random_device m_device{};
		std::default_random_engine m_engine{ m_device() };
	};

} // namespace tk
