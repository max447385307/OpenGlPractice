//#include <iostream>
//#include <SOIL/SOIL.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
////assimp
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//// GLFW
//#include <GLFW/glfw3.h>
//#include <CyOpenGlUtil/ShaderHelper.h>
//#include <CyOpenGlUtil/Camera.h>
//#include <CyOpenGlUtil/Model.h>
////#include <CyOpenGlUtil/CyOpenGlUtil.h>
//#include <CyOpenGlUtil/stb_image.h>
//
//
//int main();
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void do_movement();
//unsigned int loadTexture(char const * path, bool gammaCorrection);
//
//const GLuint WIDTH = 1280, HEIGHT = 800;
//
//Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
//GLfloat lastX = WIDTH / 2.0;
//GLfloat lastY = HEIGHT / 2.0;
//bool    keys[1024];
//
//bool gammaEnabled = false;
//bool gammaKeyPressed = false;
//
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//// Deltatime
//GLfloat deltaTime = 0.0f;    // Time between current frame and last frame
//GLfloat lastFrame = 0.0f;      // Time of last frame
//
//int main()
//{
//	// Init GLFW
//	glfwInit();
//	// Set all the required options for GLFW
//	//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置选择哪个opengl profile
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//设置窗体属性是否可重置大小
//	glfwWindowHint(GLFW_SAMPLES, 8);
//
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//
//	// 注册键盘事件
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// GLFW Options， 设置输入模式，关闭光标
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
//	glewExperimental = GL_TRUE;
//
//	// Initialize GLEW to setup the OpenGL Function pointers
//	glewInit();
//
//	// Define the viewport dimensions, 设置视口尺寸
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	// OpenGL options
//	glEnable(GL_DEPTH_TEST);
//
//	//如果不开启Blend模式会怎样
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	ShaderHelper shader("GammaCorrection/GammaCorrection.vs", "GammaCorrection/GammaCorrection.fs");
//	float planeVertices[] = {
//		// positions            // normals         // texcoords
//		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
//		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
//
//		10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
//		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
//		10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
//	};
//
//	unsigned int planeVAO, planeVBO;
//	glGenBuffers(1, &planeVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
//
//	glGenVertexArrays(1, &planeVAO);
//	glBindVertexArray(planeVAO);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)0);
//
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//
//	glBindVertexArray(0);
//
//	string textureDir = "GammaCorrection/floor.jpg";
//	unsigned int floorTexture = loadTexture(textureDir.c_str(), false);
//	unsigned int floorTextureGammaCorrected = loadTexture(textureDir.c_str(), true);
//
//	glm::vec3 lightPositions[] = {
//		glm::vec3(-3.0f, 0.0f, 1.0f),
//		glm::vec3(-1.0f, 0.0f, 2.0f),
//		glm::vec3(1.0f, 0.0f, 3.0f),
//		glm::vec3(3.0f, 0.0f, 4.0f)
//	};
//	glm::vec3 lightColors[] = {
//		glm::vec3(2.25),
//		glm::vec3(2.50),
//		glm::vec3(2.75),
//		glm::vec3(2.00)
//	};
//
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		// input
//		glfwPollEvents();
//		do_movement();
//
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.Use();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//		// set light uniforms
//		glUniform3fv(glGetUniformLocation(shader.Program, "lightPositions"), 4, &lightPositions[0][0]);
//		glUniform3fv(glGetUniformLocation(shader.Program, "lightColors"), 4, &lightColors[0][0]);
//		shader.setVec3("viewPos", camera.Position);
//		shader.setInt("gamma", gammaEnabled);
//
//		// floor
//		glBindVertexArray(planeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, gammaEnabled ? floorTextureGammaCorrected : floorTexture);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		//std::cout << (gammaEnabled ? "Gamma enabled" : "Gamma disabled") << std::endl;
//
//		glfwSwapBuffers(window);
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//// Is called whenever a key is pressed/released via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//			keys[key] = true;
//		else if (action == GLFW_RELEASE)
//			keys[key] = false;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !gammaKeyPressed)
//	{
//		gammaEnabled = !gammaEnabled;
//		gammaKeyPressed = true;
//	}
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
//	{
//		gammaKeyPressed = false;
//	}
//
//}
//
//void do_movement()
//{
//	// Camera controls
//	if (keys[GLFW_KEY_W])
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (keys[GLFW_KEY_S])
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (keys[GLFW_KEY_A])
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (keys[GLFW_KEY_D])
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//bool firstMouse = true;
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//unsigned int loadTexture(char const * path, bool gammaCorrection)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum internalFormat;
//		GLenum dataFormat;
//		if (nrComponents == 1)
//		{
//			internalFormat = dataFormat = GL_RED;
//		}
//		else if (nrComponents == 3)
//		{
//			internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
//			dataFormat = GL_RGB;
//		}
//		else if (nrComponents == 4)
//		{
//			internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
//			dataFormat = GL_RGBA;
//		}
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
