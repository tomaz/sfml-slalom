#pragma once

#include <memory>

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
		SpriteNode(std::shared_ptr<tk::SpriteSheet> spritesheet);
		SpriteNode(const SpriteNode &other) noexcept = default;
		SpriteNode(SpriteNode &&other) noexcept		 = default;
		~SpriteNode()								 = default;

	protected:
		void onDraw(RenderTarget &target, RenderStates states) const override;

	public:
		void setSpriteSheet(std::shared_ptr<tk::SpriteSheet> &spritesheet);

	private:
		std::shared_ptr<tk::SpriteSheet> m_spritesheet;
		sf::Sprite m_sprite;
	};

} // namespace tk
