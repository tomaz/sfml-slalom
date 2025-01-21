#include "node.hpp"

namespace tk
{
#pragma region Overrides

	//-------------------------------------------------------------------------
	bool Node::onUpdate(double delta) {
		// We override this so subclasses to simplify subclasses that don't have to handle updates.
		return true;
	}

	//-------------------------------------------------------------------------
	void Node::draw(RenderTarget &target, RenderStates states) const {
		states.transform.combine(getTransform());
		onDraw(target, states);
	}

#pragma endregion

} // namespace tk
