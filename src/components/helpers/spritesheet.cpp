#include <fstream>
#include <sstream>

#include <assets.hpp>
#include <json.hpp>

#include "spritesheet.hpp"

namespace tk
{
	using json = nlohmann::json; // for less verbose calls

#pragma region Construction & destruction

	//-------------------------------------------------------------------------
	std::shared_ptr<SpriteSheet> SpriteSheet::create() {
		// Private default constructor so can't use make_shared().
		return std::shared_ptr<SpriteSheet>(new SpriteSheet());
	}

	//-------------------------------------------------------------------------
	std::shared_ptr<SpriteSheet> SpriteSheet::create(std::string filename) {
		auto result = create();
		result->load(filename);
		return result;
	}

#pragma endregion

#pragma region Public

	//-------------------------------------------------------------------------
	bool SpriteSheet::load(std::string filename) {
		// Load the bitmap data.
		auto bitmapPath = Assets::path(filename, "png");
		if (!m_texture.loadFromFile(bitmapPath)) return false;

		// Load frames json data.
		auto framesPath	  = Assets::path(filename, "json");
		auto framesStream = std::ifstream(framesPath);
		json framesJson{ json::parse(framesStream) };

		// Get information about frames.
		m_frames.clear();
		auto frames = framesJson["frames"];
		for (auto &frame : frames) {
			auto rect = frame["frame"];

			int x = rect["x"];
			int y = rect["y"];
			int w = rect["w"];
			int h = rect["h"];

			m_frames.emplace_back(sf::IntRect({ x, y }, { w, h }));
		}

		return true;
	}

#pragma endregion

} // namespace tk
