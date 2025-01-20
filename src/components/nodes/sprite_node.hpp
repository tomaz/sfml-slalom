#pragma once

#include <node.hpp>
#include <spritesheet.hpp>

namespace tk
{
	/**
	 * @brief Embeds sf::Sprite.
	 */
	class SpriteNode
		: public Node
	{
	public:
		SpriteNode(tk::SpriteSheet *spritesheet);
		SpriteNode(const SpriteNode &other) noexcept = default;
		SpriteNode(SpriteNode &&other) noexcept		 = default;
		~SpriteNode()								 = default;

	protected:
		void onDraw(RenderTarget &target, RenderStates states) const override;

	public:
		void setSpriteSheet(tk::SpriteSheet *spritesheet);
		tk::SpriteSheet *spritesheet() { return m_spritesheet; }

	private:
		tk::SpriteSheet *m_spritesheet;
		sf::Sprite m_sprite;
	};

} // namespace tk
