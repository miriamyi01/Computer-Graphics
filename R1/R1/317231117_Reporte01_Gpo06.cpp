#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);

	//Verificación de errores de creacion  ventana
	if (window == NULL)
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

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	Shader OurShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {

		//FIGURA 1
		//Triángulo 1
		-0.9f,  0.9f,  0.0f,  1.0f,0.22f,0.61f,  // 0
		-0.75f, 0.75f, 0.0f,  1.0f,0.22f,0.61f,  // 1
		-0.6f,  0.9f,  0.0f,  1.0f,0.22f,0.61f,  // 2

		//Triángulo 2
		-0.6f,  0.9f,  0.0f,  0.01f,0.75f,1.0f,  // 3
		-0.6f,  0.6f,  0.0f,  0.01f,0.75f,1.0f,  // 4
		-0.75f, 0.75f, 0.0f,  0.01f,0.75f,1.0f,  // 5

		// Triángulo 3
		-0.45f, 0.45f, 0.0f,  1.0f,0.58f,0.0f,  // 6
		-0.25f, 0.65f, 0.0f,  1.0f,0.58f,0.0f,  // 7
		-0.05f, 0.45f, 0.0f,  1.0f,0.58f,0.0f,  // 8

		//Triángulo 4
		-0.6f, 0.05f, 0.0f,  1.0f,0.0f,0.02f,  // 9
		-0.6f, 0.6f,  0.0f,  1.0f,0.0f,0.02f,  // 10
		-0.3f, 0.3f,  0.0f,  1.0f,0.0f,0.02f,  // 11

		// Triángulo 5
		-0.05f, 0.45f, 0.0f,  0.97f,1.0f,0.0f,  // 12
		-0.05f, 0.05f, 0.0f,  0.97f,1.0f,0.0f,  // 13
		-0.45f, 0.45f, 0.0f,  0.97f,1.0f,0.0f,  // 14


		//FIGURA 2
		//Triángulo 1
		0.75f, -0.45f, 0.0f,  1.0f,0.22f,0.61f,  // 15
		0.85f, -0.55f, 0.0f,  1.0f,0.22f,0.61f,  // 16
		0.95f, -0.45f, 0.0f,  1.0f,0.22f,0.61f,  // 17

		//Triángulo 2
		0.05f, -0.35f, 0.0f,  0.01f,0.75f,1.0f,  // 18
		0.05f, -0.55f, 0.0f,  0.01f,0.75f,1.0f,  // 19
		0.15f, -0.45f, 0.0f,  0.01f,0.75f,1.0f,  // 20

		// Triángulo 3
		0.15f, -0.75f,  0.0f, 1.0f,0.58f,0.0f,  // 21
		0.35f, -0.55f,  0.0f, 1.0f,0.58f,0.0f,  // 22
		0.55f, -0.75f, 0.0f,  1.0f,0.58f,0.0f,  // 23

		//Triángulo 4
		0.6f,  -0.3f,  0.0f,  1.0f,0.0f,0.02f,  // 24
		0.6f,  -0.8f,  0.0f,  1.0f,0.0f,0.02f,  // 25
		0.35f, -0.55f, 0.0f,  1.0f,0.0f,0.02f,  // 26

		// Triángulo 5
		0.6f,  -0.3f,  0.0f,  0.97f,1.0f,0.0f,  // 27
		0.6f,  -0.8f,  0.0f,  0.97f,1.0f,0.0f,  // 28
		0.85f, -0.55f, 0.0f,  0.97f,1.0f,0.0f,  // 29


		//FIGURA 1
		//Rombo 1
		-0.45f, 0.75f, 0.0f,   0.0f,0.72f,0.18f,  // 30
		-0.6f,  0.6f,  0.0f,   0.0f,0.72f,0.18f,  // 31
		-0.3f,  0.6f,  0.0f,   0.0f,0.72f,0.18f,  // 32
		-0.45f, 0.45f, 0.0f,   0.0f,0.72f,0.18f,  // 33

		//Rombo 2
		-0.75f, 0.75f, 0.0f,  0.55f,0.03f,0.75f, // 34
		-0.75f, 0.35f, 0.0f,  0.55f,0.03f,0.75f, // 35
		-0.6f,  0.6f,  0.0f,  0.55f,0.03f,0.75f, // 36
		-0.6f,  0.2f,  0.0f,  0.55f,0.03f,0.75f, // 37

		//FIGURA 2
		//Rombo 1
		0.15f, -0.25f, 0.0f,   0.0f,0.72f,0.18f,  // 38
		0.05f, -0.35f, 0.0f,   0.0f,0.72f,0.18f,  // 39
		0.25f, -0.35f, 0.0f,   0.0f,0.72f,0.18f,  // 40
		0.15f, -0.45f, 0.0f,   0.0f,0.72f,0.18f,  // 41

		//Rombo 2
		0.25f, -0.35f, 0.0f, 0.55f,0.03f,0.75f, // 42
		0.15f, -0.45f, 0.0f, 0.55f,0.03f,0.75f, // 43
		0.25f, -0.65f, 0.0f, 0.55f,0.03f,0.75f, // 44
		0.15f, -0.75f, 0.0f, 0.55f,0.03f,0.75f, // 45

		
	};

	unsigned int indices[] = {  // note that we start from 0!
		//FIGURA 1 - Rombo 1 y 2
		30,31,32, //Mitad (1° TRIÁNGULO)
		31,32,33, //Mitad (2° TRIÁNGULO)

		34,35,36, //Mitad (1° TRIÁNGULO)
		35,36,37,  //Mitad (2° TRIÁNGULO)

		//FIGURA 2 - Rombo 1 y 2
		38,39,40, //Mitad (1° TRIÁNGULO)
		39,40,41, //Mitad (2° TRIÁNGULO)

		42,43,44, //Mitad (1° TRIÁNGULO)
		43,44,45  //Mitad (2° TRIÁNGULO)
	};


	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posición
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Desenlazamos de memoria el VAO


	
	while (!glfwWindowShouldClose(window))
	{
		// Checa si un eveneto ha sido activado y manda a llamar al callback correspondiente
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Dibujar aquí
		OurShader.Use();
		glBindVertexArray(VAO);

		//glPointSize(10);
		//glDrawArrays(GL_LINES_LOOP, 0, 4);
		//glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(GLfloat)));

		//Triángulos
		glDrawArrays(GL_TRIANGLES, 0, 30);
		//Rombos
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (GLvoid*)(0 * sizeof(GLfloat)));
	
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}