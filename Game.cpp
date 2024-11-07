#include "Game.h"

//private functions

void Game::initGLFW()
{
    if (glfwInit() == GLFW_FALSE) {
        std::cerr << "ERROR::GLFW::init failed" << "\n";
        glfwTerminate();
    }
}

void Game::initWindow(const char* title, bool resizable) {
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, resizable); //2nd true for resizable

    //for macos
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    //fourth one is fullscreen parameter (2nd to last NULL)
    this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

    if (this->window == nullptr) {
        std::cerr << "ERROR::glfw window init failed" << "\n";
        glfwTerminate();
    }

    //setting framebuffer height and width for when we change it
    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
    glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);

    //for constant frame size
    //glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    //glViewport(0, 0, framebufferWidth, framebufferHeight);

    glfwMakeContextCurrent(this->window); //important for glew

}

void Game::initGLEW()
{
    //glew just checks what functions are available and points them to your driver so you can use them
    glewExperimental = GL_TRUE;

    //error checking
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR::main::GLEW_INIT_FAILED" << "\n";
        glfwTerminate();
    }
}

void Game::initOpenGLOptions()
{
    glEnable(GL_DEPTH_TEST); //want to be able to change z axis
    glEnable(GL_CULL_FACE); //dont want to draw whats behind
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); //counter clockwise vector order, from top to left to right back to top, flipped will be back (we dont draw this)

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //fill the shape with a color us GL_LINE to draw outlines instead of fill

    glEnable(GL_BLEND); //we want to blend colors
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //blending setting

    //input for mouse cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatricies()
{
    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

    //perspective matrix
    this->ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);
}

void Game::initShaders()
{
    char* vertex = (char*)"vertex_core.glsl";
    char* fragment = (char*)"fragment_core.glsl";
    char* geometry = (char*)"";
    this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR, vertex, fragment, geometry));
}

void Game::initTextures()
{
    //texture 0 
    this->textures.push_back(new Texture("Images/cat.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/cat_specular.png", GL_TEXTURE_2D));
    //texture 1
    this->textures.push_back(new Texture("Images/shelf.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/shelf_specular.png", GL_TEXTURE_2D));
    //texture 2
    this->textures.push_back(new Texture("Images/colors.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Images/colors.png", GL_TEXTURE_2D));

}

void Game::initMaterials()
{                                                         //setting specular and stuff here
   this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(3.f),
       0,1)); //dont know about setting the textures here

}

void Game::initModels()
{
    std::vector<Mesh*>meshes;
    meshes.push_back(
        new Mesh(new Pyramid(),
            //here can add offsets for rotation
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)));

    this->models.push_back(
        //model position in vector here
        new Model(glm::vec3(0.f), 
            this->materials[MAT_1], 
            this->textures[TEX_COLOR], 
        this->textures[TEX_COLOR_SPECULAR],
            meshes));

    this->models.push_back(
        //model position in vector here
        new Model(glm::vec3(-2.f, 0.5f, 1.f),
            this->materials[MAT_1],
            this->textures[TEX_COLOR],
            this->textures[TEX_COLOR_SPECULAR],
            meshes));

    this->models.push_back(
        //model position in vector here
        new Model(glm::vec3(2.f, -0.5f, 1.f),
            this->materials[MAT_1],
            this->textures[TEX_COLOR],
            this->textures[TEX_COLOR_SPECULAR],
            meshes));

    //destroy after mesh giving to model
    for (auto*& i : meshes) {
        delete i;
    }
}

void Game::initLights()
{
    this->lights.push_back(new glm::vec3 (0.f, 0.f, 2.f));
}

void Game::initUniforms()
{
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
    
}

void Game::updateUniforms()
{
    //update view matrix (camera)
    this->ViewMatrix = this->camera.getViewMatrix();

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

    //update uniforms

    //update projection matrix
    //TODO ---- this is incase of a resize, this is inefficient and should be changed to, if we resize, then update matrix because this is a waste
    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

    this->ProjectionMatrix = glm::mat4(1.f);

    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane, this->farPlane);

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");
}


//change the way camera is initialized in constructor, i dont like this
Game::Game(const char* title, const int  WINDOW_WIDTH, const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable)
    : WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT), GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR),
    camera(glm::vec3(0.f,0.f,1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f,1.f,0.f))
{
    this->window = nullptr;
    this->framebufferHeight = this->WINDOW_HEIGHT;
    this->framebufferWidth = this->WINDOW_WIDTH;

    //view matrix DONT NEED ANYMORE?
    this->camPosition = glm::vec3(0.f, 0.f, 1.f);
    this->worldUp = glm::vec3(0.f, 1.f, 0.f);
    this->camFront = glm::vec3(0.f, 0.f, -1.f);

    //perspective matrix
    this-> fov = 105.f;
    this->nearPlane = 0.1f;
    this->farPlane = 1000.f;

    //delta time
    this->dt = 0.0f;
    this->curTime = 0.0f;
    this->lastTime = 0.0f;

    //time
    this->lastMouseX = 0.0;
    this->lastMouseY = 0.0;
    this->mouseX = 0.0;
    this->mouseY = 0.0;
    this->mouseOffsetX = 0.0;
    this->mouseOffsetY = 0.0;
    this->firstMouse = true;

    this->initGLFW();
	this->initWindow(title, resizable);
    this->initGLEW();
    this->initOpenGLOptions();
    this->initMatricies();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    this->initModels();
    this->initLights();
    this->initUniforms();
}

Game::~Game()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->shaders.size(); i++) {
        delete this->shaders[i];
    }
    for (size_t i = 0; i < this->textures.size(); i++) {
        delete this->textures[i];
    }
    for (size_t i = 0; i < this->materials.size(); i++) {
        delete this->materials[i];
    }
    for (auto*& i : this->models) {
        delete i;
    }
    for (size_t i = 0; i < this->lights.size(); i++) {
        delete this->lights[i];
    }
}


//accessors
int Game::getWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

//modifiers

void Game::setWindowShouldClose()
{
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//functions 

void Game::updateDT()
{
    this->curTime = static_cast<float>(glfwGetTime());
    this->dt = this->curTime - this->lastTime;
    this->lastTime = this->curTime;
}

void Game::updateKeyboardInput()
{
    //game close
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        this->setWindowShouldClose();
    }

    //camera
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
        this->camera.move(this->dt, FORWARD);
      }
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
        this->camera.move(this->dt, BACKWARD);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
        this->camera.move(this->dt, LEFT);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
        this->camera.move(this->dt, RIGHT);
    }
    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->camera.move(this->dt, UP);
    }
    if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        this->camera.move(this->dt, DOWN);
    }
}

void Game::updateMouseInput()
{
    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

    if (this->firstMouse) {
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->firstMouse = false;
    }

    //x is normal, y is inverted 
    this->mouseOffsetX = this->mouseX - this->lastMouseX;
    this->mouseOffsetY = this->lastMouseY - this->mouseY;

    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;

}

void Game::updateInput()
{
    glfwPollEvents();
 
    this->updateKeyboardInput();
    this->updateMouseInput();
    this->camera.updateInput(this->dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::update()
{
    //update input
    this->updateDT();
    this->updateInput();


    this->models[0]->rotate(glm::vec3(0.f, 0.5f, 0.f));
    this->models[1]->rotate(glm::vec3(0.f, 0.5f, 0.f));
    this->models[2]->rotate(glm::vec3(0.f, 0.5f, 0.f));

}

void Game::render()
{

    //clear
    glClearColor(0.f, 0.f, 0.f, 1.f); //R-G-B-opacity float (range is 0-1 for rgb)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //update uniforms
    this->updateUniforms();

    //render models
    for (auto& i : this->models){
        i->render(this->shaders[SHADER_CORE_PROGRAM]);
    }

    //end draw - back buffer is being drawn to while front buffer is showing on screen, we swap them, then flush the new back buffer
    glfwSwapBuffers(this->window);
    glFlush();


    //clean
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


//static functions 

void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
    //this is how to resize window
    glViewport(0, 0, fbW, fbH);
}

