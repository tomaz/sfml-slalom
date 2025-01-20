#include "spritesheet.hpp"
#include <assets.hpp>

namespace tk
{
	//-------------------------------------------------------------------------
	bool SpriteSheet::load(std::string filename) {
		auto path = Assets::path(filename, "png");
		return m_texture.loadFromFile(path);
	}

} // namespace tk
