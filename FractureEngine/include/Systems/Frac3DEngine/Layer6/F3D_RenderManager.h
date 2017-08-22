#ifndef F3D_RenderManager_H
#define F3D_RenderManager_H

#include "../_includesF3D.h"

#include "../Layer0/F3D_Singleton.h"

#include "../Layer1/F3D_Window.h"

class F3D_RenderManager : public F3D_Singleton<F3D_RenderManager>
{
	friend class F3D_Singleton<F3D_RenderManager>;

public:
	//! @brief Inicializa el subsistema de render
	void init();

	//! @brief Renderiza la escena
	void render();

	//! @brief Finaliza y libera el subsistema de renderizado de la escena
	void stop();

	//! @brief Devuelve una instancia a la ventana de OpenGL
	F3D_Window* getWindow();


private:
	F3D_RenderManager();
	virtual ~F3D_RenderManager();

	//! @brief Crea una ventana de OpenGL
	bool createWindow(int width, int height, const std::string& title, bool fullscreen, bool debug);

	F3D_Window* m_window;
};

#endif