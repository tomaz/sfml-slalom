#include "sprite_node.hpp"

namespace tk
{
	//-------------------------------------------------------------------------
	SpriteNode::SpriteNode(tk::SpriteSheet *spritesheet)
		: m_spritesheet{ spritesheet }
		, m_sprite{ spritesheet->texture() } {
		m_sprite.setTexture(m_spritesheet->texture());
	}

	//-------------------------------------------------------------------------
	void SpriteNode::onDraw(RenderTarget &target, RenderStates states) const {
		target.draw(m_sprite, states);
	}

	//-------------------------------------------------------------------------
	void SpriteNode::setSpriteSheet(tk::SpriteSheet *spritesheet) {
		m_spritesheet = spritesheet;
		m_sprite.setTexture(m_spritesheet->texture());
	}

} // namespace tk
