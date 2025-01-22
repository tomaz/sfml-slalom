#pragma once

namespace tk
{
	/**
	 * @brief Describes a range of values.
	 */
	template<class T>
	class Range
	{
	public:
		/**
		 * @brief Creates a range from minimum value and range where max=min+range.
		 */
		static Range range(T min, T length) {
			return Range{ min, min + length };
		}

	public:
		/**
		 * @brief Constructor that allows settings the ranges.
		 */
		Range(T m, T M)
			: min{ m }, max{ M } {
		}

		Range() noexcept				   = default;
		Range(const Range &other) noexcept = default;
		Range(Range &&other) noexcept	   = default;
		~Range()						   = default;

	public:
		/**
		 * @brief Calculates the length, aka max - min.
		 */
		T length() {
			return max - min;
		}

	public:
		T min{};
		T max{};
	};

} // namespace tk
