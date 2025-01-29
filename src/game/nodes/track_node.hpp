#pragma once

#include <SFML/Graphics.hpp>
#include <aabb_collision_tester.hpp>
#include <node.hpp>
#include <range.hpp>
#include <sprite_node.hpp>
#include <spritesheet.hpp>

namespace tk::game
{
	using namespace sf;

	namespace track
	{
		// Used for collision testing with poles.
		struct Pole
		{
			AABBCollisionTester tester;
			SpriteNode *node;
			bool isLeft;
			bool isRight;
		};

		// Used for collision testing with trees.
		struct Tree
		{
			AABBCollisionTester tester;
			SpriteNode *node;
		};

		// Internal structure used when setting up the track.
		struct Edge
		{
			tk::Range<double> y;
			tk::Range<double> xTop;
			tk::Range<double> xBottom;
		};

		using PolesArray = std::vector<std::unique_ptr<Pole>>;
		using TreesArray = std::vector<std::unique_ptr<Tree>>;

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
		 * @brief Cleans up current and creates a new track.
		 *
		 * @param viewSize Size of the underlying view in pixels.
		 * @param difficulty The difficulty of the track 0-100.
		 */
		void populate(sf::Vector2f viewSize, uint16_t difficulty);

	private:
		std::vector<track::Edge> populateTrack(sf::Vector2f viewSize, uint16_t difficulty);
		void populateTrees(sf::Vector2f viewSize, std::vector<track::Edge> &edges);

	public:
		track::PolesArray &poles() { return m_poles; }
		track::TreesArray &trees() { return m_trees; }
		sf::Vector2f startCenter() { return m_startCenter; }
		sf::Vector2f endCenter() { return m_endCenter; }

	private:
		track::PolesArray m_poles;
		track::TreesArray m_trees;
		tk::shared_SpriteSheet m_redFlagSheet;
		tk::shared_SpriteSheet m_blueFlagSheet;
		tk::shared_SpriteSheet m_treesSheet;
		sf::Vector2f m_startCenter;
		sf::Vector2f m_endCenter;
	};

} // namespace tk::game
