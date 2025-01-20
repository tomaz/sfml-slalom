#pragma once

#include <list>

#include <SFML/Graphics.hpp>
#include <updatable.hpp>

namespace tk
{
	using namespace sf;

	/**
	 * @brief Defines a "node".
	 *
	 * Node is an object that knows how to update and draw itself. This is abstract base class suitable for overriding. You probably want to use one of the available subclasses.
	 */
	class Node
		: public Updatable
		, public Transformable
		, public Drawable
	{
	public:
		Node() noexcept					 = default;
		Node(const Node &other) noexcept = default;
		Node(Node &&other) noexcept		 = default;
		virtual ~Node()					 = default;

	public:
		Node &operator=(const Node &other) noexcept = default;
		Node &operator=(Node &&other) noexcept		= default;

	public:
		bool onUpdate(double delta) override;

	protected:
		virtual void onDraw(RenderTarget &target, RenderStates states) const = 0;
		void draw(RenderTarget &target, RenderStates states) const override;
	};

	/**
	 * The list of nodes.
	 */
	typedef std::list<std::unique_ptr<tk::Node>> NodesList;

} // namespace tk
