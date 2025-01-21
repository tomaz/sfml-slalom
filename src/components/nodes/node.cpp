#include "node.hpp"

namespace tk
{
#pragma region Overrides

	//-------------------------------------------------------------------------
	bool Node::onUpdate(double delta) {
		// Update all sub-nodes.
		for (auto &subnode : m_nodes) {
			subnode->update(delta);
		}

		// Pass update to base class so physics will work correctly.
		return Physical::onUpdate(delta);
	}

	//-------------------------------------------------------------------------
	void Node::onDraw(RenderTarget &target, RenderStates states) const {
		// Draw all sub-nodes.
		for (auto &subnode : m_nodes) {
			subnode->draw(target, states);
		}
	}

	//-------------------------------------------------------------------------
	void Node::draw(RenderTarget &target, RenderStates states) const {
		// Apply our transform.
		states.transform.combine(getTransform());

		// Ask subclass to draw.
		onDraw(target, states);
	}

#pragma endregion

} // namespace tk
