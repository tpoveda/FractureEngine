#include "LastBastion.h"
#include "SDL2/SDL.h"

LastBastion::LastBastion(FractureEngine* engine) :
m_fractureEngine(engine),
m_isRunning(false)
{
}

void LastBastion::init()
{
	if (m_isRunning) return;
	m_isRunning = true;

	// almacenamos punteros a los distintos sistemas y subsistemas
	frac3D = m_fractureEngine->getRenderSystem();
	scene = frac3D->getEntityManager();
	render = frac3D->getRenderManager();
	resource = frac3D->getResourceManager();

	// creacion de entidades y recursos

	// Creamos entidades
	F3D_Entity* entity = scene->createEntity("Interior");
	F3D_Entity* child1 = scene->createEntity("Hijo1", "Interior");
	F3D_Entity* child1_1 = scene->createEntity("Hijo2", child1);

	// Añadimos componentes
	scene->getEntityById("Hijo1")->addComponent(Transform);
	scene->getEntityById("Hijo2")->addComponent(Transform);

	// Testeo de carga de shaders y cubemaps
	unsigned int texture = resource->getInstance()->getTextureManager()->createTexture("crate.tga", "./res/textures/");
	unsigned int logo = F3D_ResourceManager::getInstance()->getTextureManager()->createTexture("logo.jpg", "./res/textures/");
	resource->getInstance()->getTextureManager()->removeTexture(texture);
	F3D_Texture2D* tex = resource->getInstance()->getTextureManager()->getTexture(texture);
	F3D_Texture2D* logoTex = resource->getInstance()->getTextureManager()->getTexture(logo);
	resource->getInstance()->getTextureManager()->removeTexture(logo);
	F3D_Texture2D* logTex2 = resource->getInstance()->getTextureManager()->getTexture(logo);

	// Testeo de carga de modelos
	unsigned int mesh = resource->getInstance()->getMeshManager()->createMesh("sphere.obj", "./res/meshes/");
	F3D_Mesh* myMesh = resource->getInstance()->getMeshManager()->getMesh(mesh);
	resource->getInstance()->getMeshManager()->removeMesh(mesh);
	F3D_Mesh* myMesh2 = resource->getInstance()->getMeshManager()->getMesh(mesh);

	/*unsigned int textura = F3D_Texture2DManager::getInstance()->createTexture("./res/textures/crate.tga");
	printf("Ancho textura: %i\n", textura.get()->getWidth());
	printf("Alto textura: %i\n", textura.get()->getHeight());
	printf("ID Textura: %s\n", textura.get()->getID().c_str());
	printf("Formato textura: %i\n", textura.get()->getFormat());
	printf("Target textura: %i\n", textura.get()->getTarget());
	unsigned int cubemap = F3D_TextureCubeMapManager::getInstance()->createTexture("./res/textures/cubemap.dds");
	printf("Ancho cubemap: %i\n", cubemap.get()->getWidth());
	printf("Alto cubemap: %i\n", cubemap.get()->getHeight());
	printf("ID Cubemap: %s\n", cubemap.get()->getID().c_str());
	printf("Formato textura: %i\n", cubemap.get()->getFormat());
	printf("Target cubemap: %i\n", cubemap.get()->getTarget());
	printf("Nombre textura cubemap: %i\n", cubemap.get()->getTextureName());

	F3D_Texture2DManager::getInstance()->terminate();

	printf("Ancho textura: %i\n", textura.get()->getWidth());
	printf("Alto textura: %i\n", textura.get()->getHeight());
	printf("ID Textura: %s\n", textura.get()->getID().c_str());
	printf("Formato textura: %i\n", textura.get()->getFormat());
	printf("Target textura: %i\n", textura.get()->getTarget());

	// Testeo de carga de shaders
	Frac3DShader shader = F3D_ShaderManager::getInstance()->createShader("TestShader", "./res/shaders/test.vs", "./res/shaders/test.fs");
	shader.get()->addUniform("color");
	shader->setUniform("color", glm::vec3(1.0, 0.0, 0.0));
	shader->printActiveUniforms();
	shader->printAddedUniforms();
	printf("Shaders totales: %i\n", shader->getTotalShaders());

	F3D_ShaderManager::getInstance()->removeShader(shader);
	printf("Shaders totales: %i\n", shader->getTotalShaders());*/

	run();
}

void LastBastion::run()
{
	if (!m_isRunning) return;

	long double log = 0;

	while (m_isRunning)
	{
		processInput();
	}
}

void LastBastion::finish()
{
	m_isRunning = false;
}

void LastBastion::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			finish();
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				finish();
			}
		}

	}
}

LastBastion::~LastBastion()
{

}