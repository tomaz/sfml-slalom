#include "node.hpp"

namespace tk
{
#pragma region Subclass

	//-------------------------------------------------------------------------
	bool Node::onUpdate(double delta) {
		return true;
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	void Node::draw(RenderTarget &target, RenderStates states) const {
		states.transform.combine(getTransform());
		onDraw(target, states);
	}

#pragma endregion

} // namespace tk
