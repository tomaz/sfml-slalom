#include "sprite_node.hpp"

namespace tk
{
#pragma region Getters & setters

	//-------------------------------------------------------------------------
	void SpriteNode::setSpriteSheet(std::shared_ptr<tk::SpriteSheet> &spritesheet) {
		m_spritesheet = spritesheet;
		m_sprite	  = std::make_unique<tk::Sprite>(m_spritesheet->texture());
		updateAnimations();
	}

	//-------------------------------------------------------------------------
	void SpriteNode::setAnimation(double time, animator::Type type) {
		m_animator.setTime(time);
		m_animator.setType(type);
		updateAnimations();
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	void SpriteNode::onActive(bool active) {
		m_animator.setActive(active);
	}

	//-------------------------------------------------------------------------
	bool SpriteNode::onUpdate(double delta) {
		m_animator.update(delta);
		return Node::onUpdate(delta);
	}

	//-------------------------------------------------------------------------
	void SpriteNode::onDraw(RenderTarget &target, RenderStates states) const {
		target.draw(*m_sprite, states);
	}

#pragma endregion

#pragma region Helpers

	//-------------------------------------------------------------------------
	void SpriteNode::updateAnimations() {
		updateFrame(0);

		m_animator.addCallbacksCount(m_spritesheet->frames().size(), [&](double progress) {
			auto index = m_animator.current();
			updateFrame(index);
		});
	}

	void SpriteNode::updateFrame(int index) {
		if (index < 0) index = 0;
		auto rect = m_spritesheet->frames()[index];
		m_sprite->setTextureRect(rect);
	}

#pragma endregion

} // namespace tk
