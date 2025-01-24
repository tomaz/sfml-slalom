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
		m_animated = true;
		m_animator.setTime(time);
		m_animator.setType(type);
		updateAnimations();
	}

	//-------------------------------------------------------------------------
	void SpriteNode::setFrame(int index) {
		m_animated = false;
		updateFrame(index);
	}

#pragma endregion

#pragma region Overrides

	//-------------------------------------------------------------------------
	void SpriteNode::onStatus(updatable::Status status) {
		Node::onStatus(status);
		m_animator.setStatus(status);
	}

	//-------------------------------------------------------------------------
	void SpriteNode::onUpdate(double delta) {
		if (m_animated) {
			m_animator.update(delta);
		}
		Node::onUpdate(delta);
	}

	//-------------------------------------------------------------------------
	void SpriteNode::onDraw(RenderTarget &target, RenderStates states) const {
		target.draw(*m_sprite, states);
	}

#pragma endregion

#pragma region Helpers

	//-------------------------------------------------------------------------
	void SpriteNode::updateAnimations() {
		if (!m_animated) return;

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
