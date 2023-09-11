/*---------------------------------------------------------*/
/* ----------------   Pr�ctica 3 --------------------------*/
/*-----------------    2024-1   ---------------------------*/
/*-------Alumno: Martinez Gonzalez Kenya Yoselin-----------*/
/*-------Cuenta:     314223504           ------------------*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow* window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor* monitors;
GLuint VBO[2], VAO[2], EBO[2]; //aqui va a crear los contenedores Vertex buffer object, vertex array object, element buffer object 

void myData(void);
void getResolution(void);
void crearCubo(Shader, glm::vec3, glm::vec3);

//For Keyboard
float movX = 0.0f,
movY = 0.0f,
movZ = -40.0f;

float rotY = 0.0f;
glm::vec3 colorCafe = glm::vec3(0.4f, 0.2f, 0.0f);
glm::vec3 colorBlanco = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 colorNegro = glm::vec3(0.0f, 0.0f, 0.0f);

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{

	GLfloat verticesCubo[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	GLfloat verticesLuis[] = {
		// positions			//Color
		-0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 0.0f,	//V0
		0.5f, 0.7f, -0.5f,		1.0f, 0.0f, 1.0f,	//V1
		0.5f, 0.3f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		-0.2f, 0.3f, -0.5f,		1.0f, 1.0f, 0.0f,	//V3
		-0.2f, -0.3f, -0.5f,	0.0f, 1.0f, 0.0f,	//V4
		0.5f, -0.3f, -0.5f,		0.0f, 1.0f, 1.0f,	//V5
		0.5f, -0.7f, -0.5f,		0.0f, 0.0f, 1.0f,	//V6
		-0.5f, -0.7f, -0.5f,	1.0f, 1.0f, 1.0f,	//V7
	};

	unsigned int indicesLuis[] =
	{
		3, 2, 1, 0, 7, 4,
		7, 4, 5, 6
	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);	//Only if we are going to work with index


	glBindVertexArray(VAO[0]); // que las cree en memoria 
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLuis), verticesLuis, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesLuis), indicesLuis, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
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

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 3 20241", NULL, NULL);
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


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

	//Prepare to draw the scene with Projections
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	myShader.use();
	// create transformations and Projection
	glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f); // para visualizar en 3d
	//projectionOp = glm::ortho(-5.0f, 5.0f, -3.0f, 3.0f, 0.1f, 10.0f);//como se va a manejar, 2 primeros X, 2 segundos Y y asi

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		my_input(window);

		// render
		// Backgound color
		glClearColor(0.9f, 0.37f, 0.78f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi funci�n de dibujo
		/*******************************************/
		//Use "view" in order to affect all models
		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY, movZ)); //recopila la informacion de la matriz de vista 
		viewOp = glm::rotate(viewOp, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));// va a tomar lo que tiene la vista y de ahi se aplica
		// pass them to the shaders
		myShader.setMat4("model", modelOp);
		myShader.setMat4("view", viewOp);
		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		myShader.setMat4("projection", projectionOp);


		glBindVertexArray(VAO[1]);	//Enable data array [1], aqui comienza el dibujo y comienzo a decirle con que info trabaja (es de la letra C)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]); //Only if we are going to work with index

		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		myShader.setMat4("model", modelOp);
		//glDrawArrays(GL_LINE_LOOP, 0, 8); //My C
		//glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));	//to Draw using index
		//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(6 * sizeof(float)));	//to Draw using index


		/*-------------------Second figure-------------------*/
		glBindVertexArray(VAO[0]);	//Enable data array [0]
		//modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));//aqui son las coordenadas respecto al origen
		//myShader.setMat4("model", modelOp);// aqui lo dibuja utilizando la matriz de 4x4 
		//myShader.setVec3("aColor", glm::vec3(0.4f, 0.2f, 0.0f));//para darle color a mi cubo, puede funcionar para todos
		//glDrawArrays(GL_TRIANGLES, 0, 36); //My Cube 1

		crearCubo(myShader, glm::vec3(0.0f, 0.0f, 0.0f), colorCafe);//linea 1
		crearCubo(myShader, glm::vec3(1.0f, 0.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(2.0f, 0.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(1.0f, -1.0f, 0.0f), colorCafe);//linea 2
		crearCubo(myShader, glm::vec3(2.0f, -1.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -1.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(0.0f, -2.0f, 0.0f), colorCafe);//linea 3
		crearCubo(myShader, glm::vec3(1.0f, -2.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(2.0f, -2.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -2.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(4.0f, -2.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(0.0f, -3.0f, 0.0f), colorCafe);//linea 4
		crearCubo(myShader, glm::vec3(1.0f, -3.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(2.0f, -3.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -3.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(4.0f, -3.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-1.0f, -4.0f, 0.0f), colorCafe);//linea 5
		crearCubo(myShader, glm::vec3(0.0f, -4.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(1.0f, -4.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(2.0f, -4.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -4.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(4.0f, -4.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(5.0f, -4.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-2.0f, -5.0f, 0.0f), colorCafe);//linea 6
		crearCubo(myShader, glm::vec3(-1.0f, -5.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(0.0f, -5.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(1.0f, -5.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(2.0f, -5.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -5.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(4.0f, -5.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(5.0f, -5.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(6.0f, -5.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-2.0f, -6.0f, 0.0f), colorCafe);//linea 7
		crearCubo(myShader, glm::vec3(-1.0f, -6.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(0.0f, -6.0f, 0.0f), colorNegro);
		crearCubo(myShader, glm::vec3(1.0f, -6.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(2.0f, -6.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -6.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(4.0f, -6.0f, 0.0f), colorNegro);
		crearCubo(myShader, glm::vec3(5.0f, -6.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(6.0f, -6.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-2.0f, -7.0f, 0.0f), colorCafe);//linea 8
		crearCubo(myShader, glm::vec3(-1.0f, -7.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(0.0f, -7.0f, 0.0f), colorNegro);
		crearCubo(myShader, glm::vec3(1.0f, -7.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(2.0f, -7.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -7.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(4.0f, -7.0f, 0.0f), colorNegro);
		crearCubo(myShader, glm::vec3(5.0f, -7.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(6.0f, -7.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-3.0f, -8.0f, 0.0f), colorCafe);//linea 9
		crearCubo(myShader, glm::vec3(-2.0f, -8.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(-1.0f, -8.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(0.0f, -8.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(1.0f, -8.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(2.0f, -8.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -8.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(4.0f, -8.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(5.0f, -8.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(6.0f, -8.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(7.0f, -8.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-3.0f, -9.0f, 0.0f), colorCafe);//linea 10
		crearCubo(myShader, glm::vec3(-2.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(-1.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(0.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(1.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(2.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(4.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(5.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(6.0f, -9.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(7.0f, -9.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-4.0f, -10.0f, 0.0f), colorCafe);//linea 11
		crearCubo(myShader, glm::vec3(-3.0f, -10.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(-2.0f, -10.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(-1.0f, -10.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(0.0f, -10.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(1.0f, -10.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(2.0f, -10.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(3.0f, -10.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(4.0f, -10.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(5.0f, -10.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(6.0f, -10.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(7.0f, -10.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(8.0f, -10.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-4.0f, -11.0f, 0.0f), colorCafe);//linea 12
		crearCubo(myShader, glm::vec3(-3.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(-2.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(-1.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(0.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(1.0f, -11.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(2.0f, -11.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(3.0f, -11.0f, 0.0f), colorBlanco);
		crearCubo(myShader, glm::vec3(4.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(5.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(6.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(7.0f, -11.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(8.0f, -11.0f, 0.0f), colorCafe);

		crearCubo(myShader, glm::vec3(-3.0f, -12.0f, 0.0f), colorCafe);//linea 13
		crearCubo(myShader, glm::vec3(-2.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(-1.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(0.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(1.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(2.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(3.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(4.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(5.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(6.0f, -12.0f, 0.0f), colorCafe);
		crearCubo(myShader, glm::vec3(7.0f, -12.0f, 0.0f), colorCafe);
											 
		
		glBindVertexArray(0);
		/*****************************************************************/
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
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 2.1f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 2.1f;


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

//Definimos una funcion que recibe 3 cosas -> 1 objeto de la clase Shader, 1 vector de 3 dimensiones
//que guarda las cordenadas del cubo, un ultimo vector de 3 dimensiones para guardar el color

void crearCubo(Shader myShader, glm::vec3 cordenadas, glm::vec3 color) {
	glm::mat4 modelOp = glm::mat4(1.0f); //crea una nueva matriz default
	modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); //traslada la matriz al origen
	modelOp = glm::translate(modelOp, cordenadas); //trasladamos la matriz al valor guardado en 'cordenadas'
	myShader.setMat4("model", modelOp); //dibuja los vertices de los cubos
	myShader.setVec3("aColor", color); // asigna color a los vertices
	glDrawArrays(GL_TRIANGLES, 0, 36); // dibuja los triangulos utilizando los vertices y sus colores
}