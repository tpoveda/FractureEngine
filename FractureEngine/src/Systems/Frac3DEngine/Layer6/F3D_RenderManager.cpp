#include "../../../../include/Systems/Frac3DEngine/Layer6/F3D_RenderManager.h"

F3D_RenderManager::F3D_RenderManager() : 
F3D_Singleton<F3D_RenderManager>(),
m_window(nullptr)
{
	if(!createWindow(WIDTH, HEIGHT, TITLE, FULLSCREEN, DEBUG))
	{
		return;
	}
}

F3D_RenderManager::~F3D_RenderManager()
{
	if(m_window)
	{
		delete m_window;
		m_window = nullptr;
	}
}

void F3D_RenderManager::init()
{
	m_window->clearScreen();
}

void F3D_RenderManager::render()
{
	// operaciones de renderizado

	m_window->swapBuffers();
}

void F3D_RenderManager::stop()
{
}

bool F3D_RenderManager::createWindow(int width, int height, const std::string& title, bool fullscreen, bool debug)
{
	m_window = new F3D_Window(width, height, title, fullscreen, debug);
	if (m_window) return true;

	return false;
}

F3D_Window* F3D_RenderManager::getWindow()
{
	return m_window;
}