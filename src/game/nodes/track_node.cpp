#include <randomizer.hpp>

#include "track_node.hpp"

namespace tk::game
{
#pragma region Construction & destruction

	TrackNode::TrackNode() noexcept
		: Node::Node() {
		m_redFlagSheet	= SpriteSheet::create("flag-red");
		m_blueFlagSheet = SpriteSheet::create("flag-blue");
		m_treesSheet	= SpriteSheet::create("trees");
	}

#pragma endregion

#pragma region Public

	//-------------------------------------------------------------------------
	void TrackNode::populate(sf::Vector2f viewSize, uint16_t difficulty) {
		nodes().clear();
		auto edges{ populateTrack(viewSize, difficulty) };
		populateTrees(viewSize, edges);
	}

#pragma endregion

#pragma region Helpers

	//-------------------------------------------------------------------------
	std::vector<track::Edge> TrackNode::populateTrack(sf::Vector2f viewSize, uint16_t difficulty) {
		std::vector<track::Edge> result{};

		// Common setup.
		Randomizer randomizer{};

		// Convert difficulty level 0..100 to ratio 0..1.
		double difficultyRatio = (difficulty < 100 ? difficulty : 100) / 100.0;

		// Calculate common base line values based on difficulty. This mostly makes the code below less repeating. The higher the difficulty, the lower the baseline.
		double gateBaseline	 = 15.0 + 10.0 * (1.2 - difficultyRatio);
		double poleBaseline	 = 20.0 + 10.0 * (1.0 - difficultyRatio);
		double trackBaseline = viewSize.x / 6.0 + viewSize.x / 10.0 * (1.0 - difficultyRatio);

		// Prepare minimum and maximum horizontal distance between poles of each gate, and between gates.
		auto poleSize  = (float)m_redFlagSheet->frames().front().size.y;
		auto poleDist  = tk::Range<double>::range(poleBaseline, poleBaseline / 2.0);
		auto gateDistY = tk::Range<double>::range(gateBaseline, gateBaseline / 2.0);
		auto gateDistX = tk::Range<double>{ -gateBaseline, gateBaseline };

		// Prepare offsets for track edge relative to gates.
		auto trackEdgeOffset = tk::Range<double>::range(30.0, 50.0);

		// Prepare top and bottom edges of the track.
		auto trackRangeY = tk::Range<double>{
			randomizer.getRealRange(gateDistY.min, 10.0),
			viewSize.y - gateDistY.min * 2.0 - randomizer.getRealRange(0.0, 10.0)
		};

		// Prepare left and right edges of the track.
		auto trackRangeX = tk::Range<double>{
			trackBaseline,
			viewSize.x - trackBaseline * 2.0
		};

		// Prepare gate coordinates for the loop.
		double gateTop	  = trackRangeY.min + randomizer.getReal(gateDistY);
		double gateBottom = trackRangeY.max - randomizer.getReal(gateDistY);
		double gateLeft	  = viewSize.x / 2.0 + randomizer.getReal(gateDistX);

		// Setup for gate direction.
		double gateDirection = ((double)randomizer.getInt(0, 1) - 0.5) * 2.0; // Either -1.0 or 1.0

		// Helpers for less verbose code later on.
		auto animSpeed = [&]() { return randomizer.getRealRange(0.4, 0.6); };

		// Helper lambda that creates pole node at the given coordinates and adds it to all required data structures.
		auto createPoleNode = [&](double left, bool isLeft) {
			auto spritesheet = gateDirection < 0.0 ? m_redFlagSheet : m_blueFlagSheet;
			auto animSpeed	 = randomizer.getRealRange(0.4, 0.6);

			// Create the pole node.
			auto poleNode = std::make_unique<tk::SpriteNode>();
			poleNode->setSpriteSheet(spritesheet);
			poleNode->setAnimation(animSpeed, animator::Type::RepeatingBounce);
			poleNode->setPosition({ (float)left, (float)gateTop });

			// Create collision tester for the pole.
			auto poleData = std::make_unique<track::Pole>();
			poleData->tester.setArea({ { poleSize / 2.f, poleSize - 2.f }, { 1.f, 1.f } });
			poleData->tester.update(*poleNode);
			poleData->isLeft  = isLeft;
			poleData->isRight = !isLeft;
			poleData->node	  = poleNode.get();

			// Add both objects to lists.
			m_poles.emplace_back(std::move(poleData));
			nodes().emplace_back(std::move(poleNode));
		};

		// Prepare the initial edges from top of screen to start of track.
		auto startCenter	 = gateLeft + randomizer.getReal(gateDistX);
		auto startTrackLeft	 = startCenter - randomizer.getReal(trackEdgeOffset);
		auto startTrackRight = startCenter + randomizer.getReal(trackEdgeOffset);
		result.emplace_back(
			track::Edge{
				.y = Range<double>(
					0.0,
					gateTop
				),
				.xTop = Range<double>(
					startCenter - randomizer.getReal(trackEdgeOffset),
					startCenter + randomizer.getReal(trackEdgeOffset)
				),
				.xBottom = Range<double>(
					startTrackLeft,
					startTrackRight
				) //
			}
		);

		// Setup the track and prepare the positions for edge of track.
		m_poles.clear();
		while (gateTop <= gateBottom) {
			// Calculate next gate vertical coordinate; this simplifies trees calculations.
			auto nextGateTop = gateTop + randomizer.getReal(gateDistY);

			// Determine the horizontal coordinate of the other pole
			auto outerLeft	 = gateLeft + gateDirection * randomizer.getReal(poleDist);
			auto spritesheet = gateDirection < 0.0 ? m_redFlagSheet : m_blueFlagSheet;

			// Calculate track left/right for this gate.
			auto trackLeft	= std::min(gateLeft, outerLeft) - randomizer.getReal(trackEdgeOffset);
			auto trackRight = std::max(gateLeft, outerLeft) + randomizer.getReal(trackEdgeOffset);

			// If we have prior egde, update its bottom to match our top.
			if (result.size() > 0) {
				result.back().xBottom.min = trackLeft;
				result.back().xBottom.max = trackRight;
			};

			// Store track edge position at this coordinate; this will be used for placing trees later on.
			result.emplace_back(
				track::Edge{
					.y		 = { gateTop, nextGateTop },  //
					.xTop	 = { trackLeft, trackRight }, //
					.xBottom = { trackLeft, trackRight }  //
				}
			);

			// Create the inner and outer pole.
			createPoleNode(gateLeft, gateDirection > 0.0);
			createPoleNode(outerLeft, gateDirection < 0.0);

			// Prepare for next gate.
			gateTop		   = nextGateTop;
			gateLeft	  += randomizer.getReal(gateDistX);
			gateDirection *= -1.0;
		}

		// Prepare start and end center coordinate based on the last gates. Note that we end the tracks loop by setting up for next gate, so we can simply use that for horizontal direction!
		auto treeSize = m_treesSheet->frames().front().size.y;
		m_startCenter = { (float)startCenter, (float)treeSize };
		m_endCenter	  = { (float)gateLeft, (float)(viewSize.y - treeSize) };

		return result;
	} // namespace tk::game

	//-------------------------------------------------------------------------
	void TrackNode::populateTrees(sf::Vector2f viewSize, std::vector<track::Edge> &edges) {
		Randomizer randomizer{};

		auto treeSize	 = m_treesSheet->frames().front().size;
		auto screenRight = viewSize.x - treeSize.x;

		// We always work on tiles of the size of a single tree.
		auto tiled = [](double measure, int size) { return (int)measure / size * size; };

		// Calculates the horizontal offset at the given vertical coordinate.
		auto horizontal = [](double y, track::Edge &edge, bool min) {
			double width  = min ? (edge.xBottom.min - edge.xTop.min) : (edge.xBottom.max - edge.xTop.max);
			double height = edge.y.max - edge.y.min;
			double ratio  = (y - edge.y.min) / height;
			return ratio * width + (min ? edge.xTop.min : edge.xTop.max);
		};

		// Places a random tree at the given coordinate.
		auto placeTree = [&](double x, double y) {
			auto tree = std::make_unique<tk::SpriteNode>();
			tree->setSpriteSheet(m_treesSheet);
			tree->setPosition({ (float)x, (float)y });
			tree->setFrame(randomizer.getInt(0, m_treesSheet->frames().size() - 1));
			nodes().emplace_back(std::move(tree));
		};

		m_trees.clear();
		for (auto &edge : edges) {
			// Prepare top and bottom tile positions, exit if the same (we'll draw trees in next loop in this case).
			double sectionTop	 = tiled(edge.y.min, treeSize.y);
			double sectionBottom = tiled(edge.y.max, treeSize.y) - treeSize.y;
			if (sectionTop == sectionBottom) continue;

			// Draw all rows for this section.
			for (double top = sectionTop; top <= sectionBottom; top += treeSize.y) {
				// Prepare horizontal edges in tile coordinates.
				double trackLeft  = tiled(horizontal(top, edge, true), treeSize.x);
				double trackRight = tiled(horizontal(top, edge, false), treeSize.x);

				// Draw trees from left screen edge to left track edge.
				for (double left = 0.0; left < trackLeft; left += treeSize.x) {
					placeTree(left, top);
				}

				// Draw trees from right track edge to right screen edge.
				for (double left = trackRight; left <= screenRight; left += treeSize.x) {
					placeTree(left, top);
				}
			}
		}
	}

#pragma endregion

} // namespace tk::game
