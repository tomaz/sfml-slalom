#include <SFML/Graphics.hpp>
#include <application.hpp>
#include <game_scene.hpp>

int main() {
	auto application = tk::Application::create("Slalom");
	auto scene		 = tk::game::GameScene();
	application->run(scene);
	return 0;
}
