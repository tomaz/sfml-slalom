#pragma once

#include <memory>

#include <animator.hpp>
#include <node.hpp>
#include <spritesheet.hpp>

namespace tk
{
	/**
	 * @brief Embeds sf::Sprite and allows animating.
	 */
	class SpriteNode
		: public Node
	{
	public:
		SpriteNode() noexcept					= default;
		SpriteNode(SpriteNode &&other) noexcept = default;
		~SpriteNode()							= default;

	public:
		void setSpriteSheet(std::shared_ptr<tk::SpriteSheet> &spritesheet);
		void setAnimation(double time, animator::Type type);
		void setFrame(int index);

		sf::Sprite *sprite() { return m_sprite.get(); }

	protected:
		/**
		 * @brief
		 * @param status
		 */
		void onStatus(updatable::Status status) override;
		void onUpdate(double delta) override;
		void onDraw(RenderTarget &target, RenderStates states) const override;

	private:
		void updateAnimations();
		void updateFrame(int index);

	private:
		std::shared_ptr<tk::SpriteSheet> m_spritesheet;
		std::unique_ptr<sf::Sprite> m_sprite;
		tk::Animator m_animator;
		bool m_animated;
	};

} // namespace tk
