#pragma once
#include "libs.h"

//ENUMERATIONS
enum shader_enum {
	SHADER_CORE_PROGRAM = 0, SHADER_2D_CORE =1 
};
enum texture_enum {
	TEX_CAT = 0, TEX_CAT_SPECULAR, TEX_CONTAINER, TEX_CONTAINER_SPECULAR, TEX_COLOR, TEX_COLOR_SPECULAR
};
enum material_enum {
	MAT_1 = 0
};
enum mesh_enum {
	MESH_QUAD = 0
};

class Game {
private: 
	//variables
	//window 
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;
	//openGL context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//delta time
	float dt;
	float curTime;
	float lastTime;

	//fps

	float lastFrameTimeFPS;
	int FPS;
	int nextFPS;


	//camera
	Camera camera;

	//mouse input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//matricies
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//orthomatrix for hud
	glm::mat4 OrthoMatrix;

	//shaders
	std::vector<Shader*> shaders;

	//textures
	std::vector<Texture*> textures;

	//materials
	std::vector<Material*> materials;

	//lights
	 std::vector<glm::vec3*> lights;

	 //models
	 std::vector<Model*> models;

	//private functions
	void initGLFW();
	void initWindow(const char* title, bool resizable);
	void initGLEW(); //after context creation
	void initOpenGLOptions();
	void initMatricies();

	void initShaders();
	void initTextures();
	void initMaterials();
	void initOBJModels();
	void initModels();
	void initLights();
	void initUniforms();

	void updateUniforms();

public:
	//constuctor/destructor
	Game(const char* title, const int WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable);
	virtual ~Game();

	//accessor
	int getWindowShouldClose();

	int getFPS();

	//modifiers
	void setWindowShouldClose();
	//function

	void updateDT();
	void updateKeyboardInput();
	void updateMouseInput();
	void updateInput();
	void update();
	void render();
	
	//static functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
};