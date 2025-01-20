#pragma once

#include <list>

#include <SFML/Graphics.hpp>
#include <json.hpp>

namespace tk
{
	/**
	 * @brief Simplifies loading and managing of a spritesheet.
	 *
	 * This assumes the spritesheet was exported from Aseprite and two files were created:
	 *
	 * - <file>.png
	 * - <file>.json
	 *
	 * For example: `aseprite --batch --sheet out.png in.aseprite > out.json
	 */
	class SpriteSheet
	{
	public:
		SpriteSheet() noexcept						   = default;
		SpriteSheet(const SpriteSheet &other) noexcept = default;
		SpriteSheet(SpriteSheet &&other) noexcept	   = default;
		~SpriteSheet()								   = default;

	public:
		/**
		 * @brief Loads the asset from the file.
		 *
		 * @param asset Asset filename relative to assets folder
		 * @return Returns true if successful, false otherwise
		 */
		bool load(std::string filename);

	public:
		sf::Texture &texture() { return m_texture; }
		std::list<sf::IntRect> &frames() { return m_frames; }

	private:
		sf::Texture m_texture;
		std::list<sf::IntRect> m_frames;
	};

} // namespace tk
