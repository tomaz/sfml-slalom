#pragma once

#include <list>

#include <SFML/Graphics.hpp>
#include <physical.hpp>

namespace tk
{
	using namespace sf;

	class Node;
	using NodesList = std::list<std::unique_ptr<Node>>;

	/**
	 * @brief Defines a "node".
	 *
	 * Node is an object that knows how to update and draw itself. This is abstract base class suitable for overriding. You probably want to use one of the available subclasses.
	 *
	 * As convenience, a node can have sub-nodes.
	 */
	class Node
		: public Physical
		, public Drawable
	{
	public:
		Node() noexcept					 = default;
		Node(const Node &other) noexcept = default;
		Node(Node &&other) noexcept		 = default;
		virtual ~Node()					 = default;

	protected:
		virtual void onDraw(RenderTarget &target, RenderStates states) const;
		bool onUpdate(double delta) override;
		void draw(RenderTarget &target, RenderStates states) const override;

	protected:
		NodesList &nodes() { return m_nodes; }

	private:
		NodesList m_nodes;
	};

} // namespace tk
