#pragma once

#include <SFML/Graphics.hpp>
#include <node.hpp>
#include <range.hpp>
#include <spritesheet.hpp>

namespace tk::game
{
	using namespace sf;

	namespace track
	{
		// Internal structure used when setting up the track.
		struct Edge
		{
			tk::Range<double> y;
			tk::Range<double> xTop;
			tk::Range<double> xBottom;
		};

	} // namespace track

	/**
	 * @brief Represents slalom track.
	 */
	class TrackNode
		: public Node
	{
	public:
		TrackNode() noexcept;
		TrackNode(const TrackNode &other) noexcept = default;
		TrackNode(TrackNode &&other) noexcept	   = default;
		~TrackNode()							   = default;

	public:
		/**
		 * @brief Initializes all needed resources.
		 *
		 * This is only needed to be called once.
		 */
		void initialize();

		/**
		 * @brief Cleans up current and creates a new track.
		 *
		 * @param viewSize Size of the underlying view in pixels.
		 * @param difficulty The difficulty of the track 0-100.
		 */
		void populate(sf::Vector2f viewSize, uint16_t difficulty);

	private:
		std::vector<track::Edge> populateTrack(sf::Vector2f viewSize, uint16_t difficulty);
		void populateTrees(sf::Vector2f viewSize, std::vector<track::Edge> &edges);

	private:
		tk::shared_SpriteSheet m_redFlagSheet;
		tk::shared_SpriteSheet m_blueFlagSheet;
		tk::shared_SpriteSheet m_treesSheet;
	};

} // namespace tk::game
