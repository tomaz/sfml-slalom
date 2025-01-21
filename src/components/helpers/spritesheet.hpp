#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

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
	 *
	 * Since textures should be shared, this class is designed to be used as shared_ptr. Hence it hides default constructor and only exposes it through @see create() function.
	 */
	class SpriteSheet
		: public std::enable_shared_from_this<SpriteSheet>
	{
	public:
		static std::shared_ptr<SpriteSheet> create();
		SpriteSheet(const SpriteSheet &other) noexcept = default;
		SpriteSheet(SpriteSheet &&other) noexcept	   = default;
		~SpriteSheet()								   = default;

	private:
		SpriteSheet() noexcept = default;

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
		std::vector<sf::IntRect> &frames() { return m_frames; }

	private:
		sf::Texture m_texture;
		std::vector<sf::IntRect> m_frames;
	};

	using shared_SpriteSheet = std::shared_ptr<tk::SpriteSheet>;
	using weak_SpriteSheet	 = std::weak_ptr<tk::SpriteSheet>;

} // namespace tk
