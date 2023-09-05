/*---------------------------------------------------------*/
/* ----------------   Pr?ctica 2 --------------------------*/
/*-----------------    2024-1   ---------------------------*/
/*------------Martinez Gonz?lez kenya Yoselin--------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow* window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor* monitors;
GLuint VBO[2], VAO[2], EBO[2];
GLuint shaderProgramYellow, shaderProgramColor;

static const char* myVertexShader = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader
static const char* myFragmentShaderYellow = "								\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(1.0f, 1.0f, 0.0f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";
//trabajara en conjunto con el shader de fragmentos

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] =
	{
		// positions         //color
		-0.2560638928749f, -0.1780421044117f, 0.0f,  0.82,0.65,0.11f, //0 
		-0.3264930665113f, -0.0693799508014f, 0.0f,	 0.82,0.65,0.11f, //1 
		-0.1675243603035f, -0.0814535234248f, 0.0f,	 0.82,0.65,0.11f, //2 
		-0.1333159045373f, -0.1840788907234f, 0.0f,	 0.82,0.65,0.11f, //3 

		0.2560638928749f, -0.1780421044117f, 0.0f,  0.82,0.65,0.11f, //5 
		0.3264930665113f, -0.0693799508014f, 0.0f,	 0.82,0.65,0.11f, //6 
		0.1675243603035f, -0.0814535234248f, 0.0f,	 0.82,0.65,0.11f, //7 
		0.1333159045373f, -0.1840788907234f, 0.0f,	 0.82,0.65,0.11f, //8  

		0.0011201536473f, -0.6702393757825f, 0.0f,  0.0f, 0.0f, 1.0f, //8K 
		-0.077657349658f, -0.6175817849271f, 0.0f,	 0.0f, 0.0f, 1.0f, //9C 
		-0.0772539350677f, -0.5685979794802f, 0.0f,	 1.0f, 0.6f, 0.8f, //10D 
		0.0772539350677f, -0.5685979794802f, 0.0f,	 0.0f, 0.0f, 1.0f, //11E
		0.077657349658f, -0.6175817849271f, 0.0f,	 0.0f, 0.0f, 1.0f, //9C 

		0.0011201536473f, -0.6702393757825f, 0.0f,  0.0f, 0.0f, 1.0f, //10K 
		0.1995045657071f, -0.7179985860932f, 0.0f,  0.0f, 0.0f, 1.0f, //11N
		0.0011201536473f, -0.7884128064231f, 0.0f,  0.0f, 0.0f, 1.0f, //12M
		-0.1995045657071f, -0.7179985860932f, 0.0f,  0.0f, 0.0f, 1.0f, //13L

		-0.4617233537604f, 0.5986307396748f, 0.0f,  0.0f, 0.0f, 1.0f, //17 
		-0.3f, 0.4f, 0.0f,	 1.0f, 0.6f, 0.8f, //18 
		-0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //19
		-0.4864393410616f, 0.3631784395956f, 0.0f,	 0.0f, 0.0f, 1.0f, //20

		0.4617233537604f, 0.5986307396748f, 0.0f,  0.0f, 0.0f, 1.0f, //21 
		0.3f, 0.4f, 0.0f,	 1.0f, 0.6f, 0.8f, //22 
		0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //23
		0.4864393410616f, 0.3631784395956f, 0.0f,	 0.0f, 0.0f, 1.0f, //24

		-0.5362003005682f, 0.7714440699558f, 0.0f, 0.0f, 0.0f, 1.0f, //25 
		-0.1369732966932f, 0.4240647289218f, 0.0f,	 1.0f, 0.6f, 0.8f, //26 
		-0.3f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, //27
		-0.4617233537604f, 0.5986307396748f, 0.0f,	 0.0f, 0.0f, 1.0f, //28

		0.5362003005682f, 0.7714440699558f, 0.0f, 0.0f, 0.0f, 1.0f, //29 
		0.1369732966932f, 0.4240647289218f, 0.0f,	 1.0f, 0.6f, 0.8f, //30 
		0.3f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, //31
		0.4617233537604f, 0.5986307396748f, 0.0f,	 0.0f, 0.0f, 1.0f, //32

		-0.5362003005682f, 0.7714440699558f, 0.0f, 0.0f, 0.0f, 1.0f, //33w 
		-0.4617233537604f, 0.5986307396748f, 0.0f,	 1.0f, 0.6f, 0.8f, //34p 
		-0.4864393410616f, 0.3631784395956f, 0.0f, 0.0f, 0.0f, 1.0f, //35q
		-0.5569393657045f, 0.3540703840865f, 0.0f,	 0.0f, 0.0f, 1.0f, //36a1

		0.5362003005682f, 0.7714440699558f, 0.0f, 0.0f, 0.0f, 1.0f, //37w 
		0.4617233537604f, 0.5986307396748f, 0.0f,	 1.0f, 0.6f, 0.8f, //38p 
		0.4864393410616f, 0.3631784395956f, 0.0f, 0.0f, 0.0f, 1.0f, //39q
		0.5569393657045f, 0.3540703840865f, 0.0f,	 0.0f, 0.0f, 1.0f, //40a1

		-0.5569393657045f, 0.3540703840865f, 0.0f,	 0.0f, 0.0f, 1.0f, //41a1
		-0.4864393410616f, 0.3631784395956f, 0.0f, 0.0f, 0.0f, 1.0f, //42q
		-0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //43P
		-0.5718976492987f, 0.0764414623271f, 0.0f, 0.0f, 0.0f, 1.0f, //44R

		0.5569393657045f, 0.3540703840865f, 0.0f,	 0.0f, 0.0f, 1.0f, //45a1
		0.4864393410616f, 0.3631784395956f, 0.0f, 0.0f, 0.0f, 1.0f, //46q
		0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //47P
		0.5718976492987f, 0.0764414623271f, 0.0f, 0.0f, 0.0f, 1.0f, //48R

		-0.3f, 0.4f, 0.0f,	 0.0f, 0.0f, 1.0f, //49O
		-0.1369732966932f, 0.4240647289218f, 0.0f,	 0.0f, 0.0f, 1.0f, //50Z
		0.0f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, //51B1
		-0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //52P

		0.3f, 0.4f, 0.0f,	 0.0f, 0.0f, 1.0f, //53O
		0.1369732966932f, 0.4240647289218f, 0.0f,	 0.0f, 0.0f, 1.0f, //54Z
		0.0f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, //55B1
		0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //56P

		0.0f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, //55B1
		-0.0003683762397f, 0.1587344769179f, 0.0f, 0.0f, 0.0f, 1.0f, //58C1
		-0.2005523768663f, 0.0671583513526f, 0.0f, 0.0f, 0.0f, 1.0f, //59D1
		-0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //60P

		0.0f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, //61B1
		0.0003683762397f, 0.1587344769179f, 0.0f, 0.0f, 0.0f, 1.0f, //62C1
		0.2005523768663f, 0.0671583513526f, 0.0f, 0.0f, 0.0f, 1.0f, //63D1
		0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //64P

		-0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //65P
		-0.2005523768663f, 0.0671583513526f, 0.0f, 0.0f, 0.0f, 1.0f, //66D1
		-0.1675243603035f, -0.0814535234248f, 0.0f, 0.0f, 0.0f, 1.0f, //67P2
		-0.3264930665113f, -0.0693799508014f, 0.0f, 0.0f, 0.0f, 1.0f, //68P1
		-0.5718976492987f, 0.0764414623271f, 0.0f, 0.0f, 0.0f, 1.0f, //69R

		0.4435115736438f, 0.2239884058471f, 0.0f, 0.0f, 0.0f, 1.0f, //70P
		0.2005523768663f, 0.0671583513526f, 0.0f, 0.0f, 0.0f, 1.0f, //71D1
		0.1675243603035f, -0.0814535234248f, 0.0f, 0.0f, 0.0f, 1.0f, //72P2
		0.3264930665113f, -0.0693799508014f, 0.0f, 0.0f, 0.0f, 1.0f, //73P1
		0.5718976492987f, 0.0764414623271f, 0.0f, 0.0f, 0.0f, 1.0f, //74R

		-0.5718976492987f, 0.0764414623271f, 0.0f, 0.0f, 0.0f, 1.0f, //75R
		-0.3264930665113f, -0.0693799508014f, 0.0f, 0.0f, 0.0f, 1.0f, //76P1
		-0.6801652494167f, -0.2681196128441f, 0.0f, 0.0f, 0.0f, 1.0f, //77E1

		0.5718976492987f, 0.0764414623271f, 0.0f, 0.0f, 0.0f, 1.0f, //78R
		0.3264930665113f, -0.0693799508014f, 0.0f, 0.0f, 0.0f, 1.0f, //79P1
		0.6801652494167f, -0.2681196128441f, 0.0f, 0.0f, 0.0f, 1.0f, //80E1

		-0.3264930665113f, -0.0693799508014f, 0.0f, 0.0f, 0.0f, 1.0f, //81P1
		-0.2560638928749f, -0.1780421044117f, 0.0f, 0.0f, 0.0f, 1.0f, //82P0
		-0.4636628868861f, -0.4289928961133f, 0.0f, 0.0f, 0.0f, 1.0f, //83F1
		-0.6801652494167f, -0.2681196128441f, 0.0f, 0.0f, 0.0f, 1.0f, //84E1

		0.3264930665113f, -0.0693799508014f, 0.0f, 0.0f, 0.0f, 1.0f, //85P1
		0.2560638928749f, -0.1780421044117f, 0.0f, 0.0f, 0.0f, 1.0f, //86P0
		0.4636628868861f, -0.4289928961133f, 0.0f, 0.0f, 0.0f, 1.0f, //87F1
		0.6801652494167f, -0.2681196128441f, 0.0f, 0.0f, 0.0f, 1.0f, //88E1

		-0.2560638928749f, -0.1780421044117f, 0.0f, 0.0f, 0.0f, 1.0f, //89P0
		-0.1333159045373f, -0.1840788907234f, 0.0f, 0.0f, 0.0f, 1.0f, //90P3
		-0.2516709902416f, -0.5838522248678f, 0.0f, 0.0f, 0.0f, 1.0f, //91G1
		-0.4636628868861f, -0.4289928961133f, 0.0f, 0.0f, 0.0f, 1.0f, //92F1

		0.2560638928749f, -0.1780421044117f, 0.0f, 0.0f, 0.0f, 1.0f, //93P0
		0.1333159045373f, -0.1840788907234f, 0.0f, 0.0f, 0.0f, 1.0f, //94P3
		0.2516709902416f, -0.5838522248678f, 0.0f, 0.0f, 0.0f, 1.0f, //95G1
		0.4636628868861f, -0.4289928961133f, 0.0f, 0.0f, 0.0f, 1.0f, //96F1

		//0.0011201536473f, -0.7884128064231f, 0.0f, 0.0f, 0.0f, 1.0f, //97M
		//-0.1995045657071f, -0.7179985860932f, 0.0f, 0.0f, 0.0f, 1.0f, //98L
		//-0.2516709902416f, -0.5838522248678f, 0.0f, 0.0f, 0.0f, 1.0f, //99G1
		//-0.1333159045373f, -0.1840788907234f, 0.0f, 0.0f, 0.0f, 1.0f, //100P3
		//-0.1675243603035f, -0.0814535234248f, 0.0f, 1.0f, 0.6f, 0.8f, //1012 
		//-0.2005523768663f, 0.0671583513526f, 0.0f, 0.0f, 0.0f, 1.0f, //102D1
		//0.0003683762397f, 0.1587344769179f, 0.0f, 0.0f, 0.0f, 1.0f, //103C1
		//0.2005523768663f, 0.0671583513526f, 0.0f, 0.0f, 0.0f, 1.0f, //104D1
		//0.1675243603035f, -0.0814535234248f, 0.0f, 1.0f, 0.6f, 0.8f, //105P2
		//0.1333159045373f, -0.1840788907234f, 0.0f, 0.0f, 0.0f, 1.0f, //106P3
		//0.2516709902416f, -0.5838522248678f, 0.0f, 0.0f, 0.0f, 1.0f, //107G1
		//0.1995045657071f, -0.7179985860932f, 0.0f, 0.0f, 0.0f, 1.0f, //108L

		-0.2516709902416f, -0.5838522248678f, 0.0f, 0.0f, 0.0f, 1.0f, //97G1
		-0.1995045657071f, -0.7179985860932f, 0.0f, 0.0f, 0.0f, 1.0f, //98L

		0.2516709902416f, -0.5838522248678f, 0.0f, 0.0f, 0.0f, 1.0f, //99G1
		0.1995045657071f, -0.7179985860932f, 0.0f, 0.0f, 0.0f, 1.0f, //100L



	};

	unsigned int indices[] =
	{

		0, 1, 2, 3, //triangulo con 3 como pivote
		4, 5, 6, 7,
		8, 9, 10, 11, 12,
		13, 14, 15, 16,
		17, 18, 19, 20,
		21, 22, 23, 24,
		25, 26, 27, 28,
		29, 30, 31, 32,
		33, 34, 35, 36,
		37, 38, 39, 40,
		41, 42, 43, 44,
		45, 46, 47, 48,
		49, 50, 51, 52,
		53, 54, 55, 56,
		57, 58, 59, 60, 
		61, 62, 63, 64, 
		65, 66, 67, 68, 69, 
		70, 71, 72, 73, 74, 
		75, 76, 77,
		78, 79, 80, 
		81, 82, 83, 84,
		85, 86, 87, 88,
		89, 90, 91, 92,
		93, 94, 95, 96,
		97, 98,
		99, 100
				

	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);



	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //como se va a comportar, que entrada, cuantos datos recibe(de vertices)
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //la posicion 1 es color( de vertices)
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &myFragmentShaderYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometr?a con Color
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderColor);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//My Functions
	//Setup Data to use
	myData();
	//To Setup Shaders
	setupShaders();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  //// LINEA DE PRUEBA


	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Background color
		glClearColor(0.94F, 0.63F, 0.91f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Display Section
		glUseProgram(shaderProgramColor); //dibuja todo de un solo color

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

		glPointSize(10.0);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(4 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(8 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(13 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(17 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(21 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(25 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(29 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(33 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(37 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(41 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(45 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(49 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(53 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(57 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(61 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(65 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(70 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 3, GL_UNSIGNED_INT, (void*)(75 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 3, GL_UNSIGNED_INT, (void*)(78 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(81 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(85 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(89 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(93 * sizeof(float)));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(97 * sizeof(float)));
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(99 * sizeof(float)));






		//glDrawArrays(GL_TRIANGLE_FAN, 0, 6);


		glBindVertexArray(0);
		glUseProgram(0);

		//End of Display Section

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);  //Close
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}