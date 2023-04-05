#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 3", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers



	// use with Perspective Projection
	float vertices[] = {

		//Cubo azul
		-0.5f, -0.5f, 0.5f, 0.0f, 0.44f,1.0f,//1 - Frontal
		0.5f, -0.5f, 0.5f,  0.0f, 0.44f,1.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.44f,1.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.44f,1.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.44f,1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.44f,1.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.44f,1.0f,//Posterior
		 0.5f, -0.5f,-0.5f, 0.0f, 0.44f,1.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.44f,1.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.44f,1.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.44f,1.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.44f,1.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.24f,0.54f, //Lateral izquierda
		 0.5f, -0.5f, -0.5f,  0.0f, 0.24f,0.54f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.24f,0.54f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.24f,0.54f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.24f,0.54f,
		 0.5f,  -0.5f, 0.5f,  0.0f, 0.24f,0.54f,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.24f,0.54f, //Lateral derecha
		-0.5f,  0.5f, -0.5f,  0.0f, 0.24f,0.54f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.24f,0.54f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.24f,0.54f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.24f,0.54f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.24f,0.54f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.44f,1.0f, //Inferior
		0.5f, -0.5f, -0.5f,  0.0f, 0.44f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.44f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.44f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.44f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.44f,1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.44f,1.0f, //Superior
		0.5f,  0.5f, -0.5f,  0.0f, 0.44f,1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.44f,1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.44f,1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.44f,1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.44f,1.0f, //36


		//Cubo blanco
		-0.5f, -0.5f, 0.5f, 0.95f, 0.95f,0.95f,//37 - Frontal
		0.5f, -0.5f, 0.5f,  0.95f, 0.95f,0.95f,
		0.5f,  0.5f, 0.5f,  0.95f, 0.95f,0.95f,
		0.5f,  0.5f, 0.5f,  0.95f, 0.95f,0.95f,
		-0.5f,  0.5f, 0.5f, 0.95f, 0.95f,0.95f,
		-0.5f, -0.5f, 0.5f, 0.95f, 0.95f,0.95f,

		-0.5f, -0.5f,-0.5f, 0.95f, 0.95f,0.95f,//Posterior
		 0.5f, -0.5f,-0.5f, 0.95f, 0.95f,0.95f,
		 0.5f,  0.5f,-0.5f, 0.95f, 0.95f,0.95f,
		 0.5f,  0.5f,-0.5f, 0.95f, 0.95f,0.95f,
		-0.5f,  0.5f,-0.5f, 0.95f, 0.95f,0.95f,
		-0.5f, -0.5f,-0.5f, 0.95f, 0.95f,0.95f,

		 0.5f, -0.5f,  0.5f,  0.85f, 0.85f,0.85f, //Lateral izquierda
		 0.5f, -0.5f, -0.5f,  0.85f, 0.85f,0.85f,
		 0.5f,  0.5f, -0.5f,  0.85f, 0.85f,0.85f,
		 0.5f,  0.5f, -0.5f,  0.85f, 0.85f,0.85f,
		 0.5f,  0.5f,  0.5f,  0.85f, 0.85f,0.85f,
		 0.5f,  -0.5f, 0.5f,  0.85f, 0.85f,0.85f,

		-0.5f,  0.5f,  0.5f,  0.85f, 0.85f,0.85f, //Lateral derecha
		-0.5f,  0.5f, -0.5f,  0.85f, 0.85f,0.85f,
		-0.5f, -0.5f, -0.5f,  0.85f, 0.85f,0.85f,
		-0.5f, -0.5f, -0.5f,  0.85f, 0.85f,0.85f,
		-0.5f, -0.5f,  0.5f,  0.85f, 0.85f,0.85f,
		-0.5f,  0.5f,  0.5f,  0.85f, 0.85f,0.85f,

		-0.5f, -0.5f, -0.5f, 0.95f, 0.95f,0.95f, //Inferior
		0.5f, -0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		0.5f, -0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		0.5f, -0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		-0.5f, -0.5f,  0.5f, 0.95f, 0.95f,0.95f,
		-0.5f, -0.5f, -0.5f, 0.95f, 0.95f,0.95f,

		-0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f, //Superior
		0.5f,  0.5f, -0.5f,  0.95f, 0.95f,0.95f,
		0.5f,  0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		0.5f,  0.5f,  0.5f,  0.95f, 0.95f,0.95f,
		-0.5f,  0.5f,  0.5f, 0.95f, 0.95f,0.95f,
		-0.5f,  0.5f, -0.5f, 0.95f, 0.95f,0.95f, //72


		//Cubo naranja
		-0.5f, -0.5f, 0.5f, 1.0f, 0.85f,0.0f,//73 - Frontal
		0.5f, -0.5f, 0.5f,  1.0f, 0.85f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.85f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.85f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.85f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.85f,0.0f,

		-0.5f, -0.5f,-0.5f, 1.0f, 0.85f,0.0f,//Posterior
		 0.5f, -0.5f,-0.5f, 1.0f, 0.85f,0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.85f,0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.85f, 0.0f,
		-0.5f,  0.5f,-0.5f, 1.0f, 0.85f, 0.0f,
		-0.5f, -0.5f,-0.5f, 1.0f, 0.85f, 0.0f,

		 0.5f, -0.5f,  0.5f,  0.9f, 0.75f,0.0f, //Lateral izquierda
		 0.5f, -0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.9f, 0.75f, 0.0f,
		 0.5f,  -0.5f, 0.5f,  0.9f, 0.75f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.9f, 0.75f, 0.0f, //Lateral derecha
		-0.5f,  0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.9f, 0.75f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.9f, 0.75f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.9f, 0.75f, 0.0f, //Inferior
		0.5f, -0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.75f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.9f, 0.75f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.9f, 0.75f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.9f, 0.75f, 0.0f,

		-0.5f,  0.5f, -0.5f, 0.9f, 0.75f, 0.0f, //Superior
		0.5f,  0.5f, -0.5f,  0.9f, 0.75f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.9f, 0.75f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.9f, 0.75f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.9f, 0.75f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.9f, 0.75f, 0.0f, //108


		//Cubo negro
		-0.5f, -0.5f, 0.5f, 0.15f, 0.15f,0.15f,//109 - Frontal
		0.5f, -0.5f, 0.5f,  0.15f, 0.15f, 0.15f,
		0.5f,  0.5f, 0.5f,  0.15f, 0.15f, 0.15f,
		0.5f,  0.5f, 0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f, 0.5f, 0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f, 0.5f, 0.15f, 0.15f, 0.15f,

		-0.5f, -0.5f,-0.5f, 0.15f, 0.15f, 0.15f,//Posterior
		 0.5f, -0.5f,-0.5f, 0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f,-0.5f, 0.15f, 0.15f, 0.15f,
		 0.5f,  0.5f,-0.5f, 0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f,-0.5f, 0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f,-0.5f, 0.15f, 0.15f, 0.15f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, //Lateral izquierda
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, //Lateral derecha
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.15f, 0.15f, 0.15f, //Inferior
		0.5f, -0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		0.5f, -0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f,  0.5f, 0.15f, 0.15f, 0.15f,
		-0.5f, -0.5f, -0.5f, 0.15f, 0.15f, 0.15f,

		-0.5f,  0.5f, -0.5f, 0.15f, 0.15f, 0.15f, //Superior
		0.5f,  0.5f, -0.5f,  0.15f, 0.15f, 0.15f,
		0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		0.5f,  0.5f,  0.5f,  0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f,  0.5f, 0.15f, 0.15f, 0.15f,
		-0.5f,  0.5f, -0.5f, 0.15f, 0.15f, 0.15f, //144


		//Cubo rojo
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//145 - Frontal
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,-0.5f, 1.0f, 0.0f, 0.0f,//Posterior
		 0.5f, -0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,-0.5f, 1.0f, 0.0f, 0.0f,

		 0.5f, -0.5f,  0.5f,  0.85f, 0.0f, 0.0f, //Lateral izquierda
		 0.5f, -0.5f, -0.5f,  0.85f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.85f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.85f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.85f, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0.5f,  0.85f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.85f, 0.0f, 0.0f, //Lateral derecha
		-0.5f,  0.5f, -0.5f,  0.85f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.85f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.85f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.85f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.85f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //Inferior
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //Superior
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, //180


		//Cubo azul claro
		-0.5f, -0.5f, 0.5f, 0.0f, 0.75f,1.0f,//181 - Frontal
		0.5f, -0.5f, 0.5f,  0.0f, 0.75f, 1.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.75f, 1.0f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.75f, 1.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.75f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.75f, 1.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.75f, 1.0f,//Posterior
		 0.5f, -0.5f,-0.5f, 0.0f, 0.75f, 1.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.75f, 1.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.75f, 1.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.75f, 1.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.75f, 1.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.75f, 1.0f, //Lateral izquierda
		 0.5f, -0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.75f, 1.0f,
		 0.5f,  -0.5f, 0.5f,  0.0f, 0.75f, 1.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 0.75f, 1.0f, //Lateral derecha
		-0.5f,  0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.75f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.75f, 1.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.75f, 1.0f, //Inferior
		0.5f, -0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.75f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.75f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.75f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.75f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.75f, 1.0f, //Superior
		0.5f,  0.5f, -0.5f,  0.0f, 0.75f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.75f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.75f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.75f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.75f, 1.0f, //216
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);

		//Abrigo
		model = glm::scale(model, glm::vec3(1.0f, 0.7f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);

		//Hombro Izquierdo
		model = glm::translate(model, glm::vec3(0.325f, 0.45f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.2f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);

		//Hombro Derecho
		model = glm::translate(model, glm::vec3(-0.325f, 0.45f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.2f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);

		//Decoración - Tirantes
		model = glm::translate(model, glm::vec3(-0.25f, 0.455f, 0.355f));
		model = glm::scale(model, glm::vec3(0.1f, 0.21f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(0.25f, 0.455f, 0.355f));
		model = glm::scale(model, glm::vec3(0.1f, 0.21f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(-0.25f, 0.555f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.01f, 0.71f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(0.25f, 0.555f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.01f, 0.71f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(-0.25f, 0.105f, -0.355f));
		model = glm::scale(model, glm::vec3(0.1f, 0.91f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(0.25f, 0.105f, -0.355f));
		model = glm::scale(model, glm::vec3(0.1f, 0.91f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Moño
		model = glm::translate(model, glm::vec3(0.0f, 0.225f, 0.425f));
		model = glm::scale(model, glm::vec3(0.6f, 0.25f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 180);
		model = glm::mat4(1);

		//Brazo izquierdo
		model = glm::translate(model, glm::vec3(0.625f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);

		//Brazo derecho
		model = glm::translate(model, glm::vec3(-0.625f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);

		//Mangas
		model = glm::translate(model, glm::vec3(-0.625f, -0.25f, 0.13f));
		model = glm::scale(model, glm::vec3(0.25f, 0.1f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(0.625f, -0.25f, 0.13f));
		model = glm::scale(model, glm::vec3(0.25f, 0.1f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Mano izquierda
		model = glm::translate(model, glm::vec3(0.625f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		model = glm::mat4(1);

		//Mano derecha
		model = glm::translate(model, glm::vec3(-0.625f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		model = glm::mat4(1);

		//Cuerpo
		model = glm::translate(model, glm::vec3(0.0f, -0.6f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		model = glm::mat4(1);

		//Pierna izquierda
		model = glm::translate(model, glm::vec3(-0.375f, -1.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Pierna derecha
		model = glm::translate(model, glm::vec3(0.375f, -1.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Pata izquierda
		model = glm::translate(model, glm::vec3(-0.375f, -1.4f, 0.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.1f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Pata derecha
		model = glm::translate(model, glm::vec3(0.375f, -1.4f, 0.2f));
		model = glm::scale(model, glm::vec3(0.4f, 0.1f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Pecho
		model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		model = glm::mat4(1);

		//Cuello
		model = glm::translate(model, glm::vec3(0.0f, 0.65f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.3f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		model = glm::mat4(1);

		//Cabeza 1
		model = glm::translate(model, glm::vec3(0.0f, 0.85f, -0.025f));
		model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		model = glm::mat4(1);

		//Cabeza 2
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, -0.1f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 72);
		model = glm::mat4(1);

		//Liston
		model = glm::translate(model, glm::vec3(0.0f, 1.525f, -0.1f));
		model = glm::scale(model, glm::vec3(0.5f, 0.15f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
		model = glm::mat4(1);

		model = glm::translate(model, glm::vec3(0.0f, 1.4f, -0.4f));
		model = glm::scale(model, glm::vec3(0.5f, 0.4f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
		model = glm::mat4(1);

		//Gorro 1
		model = glm::translate(model, glm::vec3(0.0f, 1.625f, -0.1f));
		model = glm::scale(model, glm::vec3(0.5f, 0.05f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);

		//Gorro 2
		model = glm::translate(model, glm::vec3(0.0f, 1.75f, -0.1f));
		model = glm::scale(model, glm::vec3(0.7f, 0.2f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4(1);

		//Pico Abajo
		model = glm::translate(model, glm::vec3(0.0f, 0.825f, 0.25f));
		model = glm::scale(model, glm::vec3(0.5f, 0.15f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Pico Arriba
		model = glm::translate(model, glm::vec3(0.0f, 0.975f, 0.35f));
		model = glm::scale(model, glm::vec3(0.5f, 0.15f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 108);
		model = glm::mat4(1);

		//Ojo Izquierdo
		model = glm::translate(model, glm::vec3(-0.175f, 1.2f, 0.155f));
		model = glm::scale(model, glm::vec3(0.15f, 0.3f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 216);
		model = glm::mat4(1);

		//Pupila Izquierda
		model = glm::translate(model, glm::vec3(-0.15f, 1.15f, 0.165f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
		model = glm::mat4(1);

		//Ojo Derecho
		model = glm::translate(model, glm::vec3(0.175f, 1.2f, 0.155f));
		model = glm::scale(model, glm::vec3(0.15f, 0.3f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 216);
		model = glm::mat4(1);

		//Pupila Derecha
		model = glm::translate(model, glm::vec3(0.15f, 1.15f, 0.165f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 144);
		model = glm::mat4(1);


		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}


void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.05f;
}