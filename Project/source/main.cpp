
#include <Windows.h>

#include "DrawableFactory.h"
#include "InputManager.h"
#include "Game.h"
#include "IRenderable.h"
#include "Graphics.h"



void AppMain() {
   
	Graphics *graphics = new Graphics();
	graphics->Initialize(800, 600);

	Game* game = new Game();
	game->Generate(graphics, 340, 460, 45.f, 8);

	InputManager::getInstancePtr()->initialise();

	double lastTime = glfwGetTime();
	while(glfwGetWindowParam(GLFW_OPENED) && !game->Exit()){

		double thisTime = glfwGetTime();
		
		game->Update(graphics, (float)(thisTime - lastTime));
		lastTime = thisTime;
		
		game->Draw(graphics);

		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			//std::cerr << "OpenGL Error " << error << ": " << (const char*)gluErrorString(error) << std::endl;
		}
	}


	delete game;
	delete graphics;

	glfwTerminate();
}


int main(int argc, char *argv[]) {
	try {
		AppMain();
	} catch (const std::exception& e){
		std::cerr << "ERROR: " << e.what() << std::endl;
		
		return EXIT_FAILURE;

	}

	return EXIT_SUCCESS;
}
