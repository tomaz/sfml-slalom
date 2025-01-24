#include "node.hpp"

namespace tk
{
#pragma region Overrides

	//-------------------------------------------------------------------------
	void Node::onStatus(updatable::Status status) {
		Updatable::onStatus(status);

		// Notify nodes.
		for (auto &node : m_nodes) {
			node->setStatus(status);
		}
	}

	//-------------------------------------------------------------------------
	void Node::onUpdate(double delta) {
		// Pass update to our base classes so physics will work correctly.
		Physical::onUpdate(delta);

		// Update all sub-nodes.
		for (auto &subnode : m_nodes) {
			subnode->update(delta);
		}
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
