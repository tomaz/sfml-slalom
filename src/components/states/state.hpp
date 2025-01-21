#pragma once

#include <SFML/Graphics.hpp>
#include <activatable.hpp>
#include <node.hpp>
#include <updatable.hpp>

namespace tk
{
	using namespace sf;

	class Application;

	/**
	 * @brief Declares a state.
	 *
	 * State is a way to split larger algorithm into smaller chunks. States are @see Activatable but also @see Updatable and @see Drawable as convenience. To simplify states handling, you can override your class from @see StateMachine.
	 */
	class State
		: public Activatable
		, public Updatable
		, public Drawable
	{
	public:
		State() noexcept = default;
		virtual ~State() = default;

	public:
		void onActivated() override;
		void onDeactivated() override;
		bool onUpdate(double delta) override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	public:
		void setApplication(std::shared_ptr<tk::Application> application);
		tk::Application *application();
		tk::NodesList &nodes() { return m_nodes; }

	private:
		std::weak_ptr<tk::Application> m_application;
		tk::NodesList m_nodes;
	};

} // namespace tk
