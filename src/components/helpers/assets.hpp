#pragma once

#include <string>

namespace tk
{
	/**
	 * @brief Manages access to assets.
	 */
	class Assets
	{
	public:
		/**
		 * @brief Prepares path to the given asset filename relative to executable.
		 *
		 * @param filename Asset filename
		 * @return Returns relative path to the asset.
		 */
		static std::string path(std::string filename) {
			return "assets/" + filename;
		}

		/**
		 * @brief Prepares path to the given asset filename relative to executable.
		 *
		 * @param filename Asset filename
		 * @param extension Asset extension
		 * @return Returns relative path to the asset.
		 */
		static std::string path(std::string filename, std::string extension) {
			return path(filename + "." + extension);
		}
	};

} // namespace tk
