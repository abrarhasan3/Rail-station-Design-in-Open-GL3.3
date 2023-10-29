//
//  main.cpp
//  3D Object Drawing
//
//  Abrar Hasan
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "SpotLight.h"
#include "sphere.h"
#include "cylinder.h"
#include "wheel.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void chair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void cabin(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void wallTrain(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void platform(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void door(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void frame(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawtri(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float M_PI = 3.1416;
int n;
float pi = 3.1416;

bool directionLightOn = true;
float ambientR=.2, ambientG=.2, ambientB=.2;



// camera
Camera camera(glm::vec3(0.0f, 1.1f, 5.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

float pointLightYPos = 1.9, pointLightXPos = 2.1;;
// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(pointLightXPos,pointLightYPos,-1.2f),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2-(2.4*1)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 2)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 3)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 4)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 5)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 6)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 7)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 8)),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 9)),
    
};



float specularR=1.0, specularG=1.0, specularB=1.0;
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,            // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,           // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,          // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);

PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,            // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);
PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);
PointLight pointlight7(

    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number
);
PointLight pointlight8(

    pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    8       // light number
);
PointLight pointlight9(

    pointLightPositions[8].x, pointLightPositions[8].y, pointLightPositions[8].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,       // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    9       // light number
);
PointLight pointlight10(

    pointLightPositions[9].x, pointLightPositions[9].y, pointLightPositions[9].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,       // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    10       // light number
);

float spotLightXpos = -1.9-2.7  , spotLightYpos = -.4 +2.0 +1 ;
glm::vec3 spotPositions[] = {
    glm::vec3(spotLightXpos,spotLightXpos,-1.2f),
};
SpotLight spotlight1(
    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,      // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1,       // light number
    glm::cos(glm::radians(20.5f)),
    glm::cos(glm::radians(25.0f)),
    0, -1, 0
);




// light settings
bool onOffToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };


    //vector<float> circVer;
    //vector<unsigned int> circInd;
    //float r1 = 4, r2 = 3.5, x1, y1, z1, x2, y2, z2, x3, y3, z3;
    //float theta = 25, c = 0, t = 6, k = 2 * pi;
    //int steps = 100, i;
    ////float total = (((155 - 25) * 3.1416) / 180) / steps;
    //float angle = 3.1416 * 2.0 / steps, starting = 26;
    //for (i = 0; i < steps; i++) {
    //    x1 = r2 * cosf(starting + angle * i);
    //    y1 = r2 * sinf(starting + angle * i);
    //    z1 = 0.0;
    //    circVer.push_back(x1);
    //    circVer.push_back(y1);
    //    circVer.push_back(z1);
    //    circVer.push_back(0.0);
    //    circVer.push_back(0.0);
    //    circVer.push_back(1.0);

    //    circInd.push_back(c);

    //    c++;
    //    x2 = r1 * cosf(starting + angle * i);
    //    y2 = r1 * sinf(starting + angle * i);
    //    z2 = 0.0;
    //    circVer.push_back(x2);
    //    circVer.push_back(y2);
    //    circVer.push_back(z2);
    //    circVer.push_back(0.0);
    //    circVer.push_back(0.0);
    //    circVer.push_back(1.0);

    //    circInd.push_back(c);

    //    c++;
    //    x3 = r1 * cosf(starting + angle * (i + 1));
    //    y3 = r1 * sinf(starting + angle * (i + 1));
    //    z3 = 0.0;
    //    circVer.push_back(x3);
    //    circVer.push_back(y3);
    //    circVer.push_back(z3);
    //    circVer.push_back(0.0);
    //    circVer.push_back(0.0);
    //    circVer.push_back(1.0);

    //    circInd.push_back(c);

    //    //2nd tri
    //    x1 = r2 * cosf(starting + angle * i);
    //    y1 = r2 * sinf(starting + angle * i);
    //    z1 = 0.0;
    //    circVer.push_back(x1);
    //    circVer.push_back(y1);
    //    circVer.push_back(z1);
    //    circVer.push_back(0.0);
    //    circVer.push_back(0.0);
    //    circVer.push_back(1.0);

    //    circInd.push_back(c);

    //    c++;
    //    x2 = r2 * cosf(starting + angle * (i + 1));
    //    y2 = r2 * sinf(starting + angle * (i + 1));
    //    z2 = 0.0;
    //    circVer.push_back(x2);
    //    circVer.push_back(y2);
    //    circVer.push_back(z2);
    //    circVer.push_back(0.0);
    //    circVer.push_back(0.0);
    //    circVer.push_back(1.0);

    //    circInd.push_back(c);

    //    c++;
    //    x3 = r1 * cosf(starting + angle * (i + 1));
    //    y3 = r1 * sinf(starting + angle * (i + 1));
    //    z3 = 0.0;
    //    circVer.push_back(x3);
    //    circVer.push_back(y3);
    //    circVer.push_back(z3);
    //    circVer.push_back(0.0);
    //    circVer.push_back(0.0);
    //    circVer.push_back(1.0);

    //    circInd.push_back(c);
    //}
    //n = circVer.size();
    //unsigned int signVAO, signVBO, signEBO;
    //glGenVertexArrays(1, &signVAO);
    //glGenBuffers(1, &signVBO);
    //glGenBuffers(1, &signEBO);

    //glBindVertexArray(signVAO);

    //glBindBuffer(GL_ARRAY_BUFFER, signVBO);
    //glBufferData(GL_ARRAY_BUFFER, circVer.size(), circVer.data(), GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, signEBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, circInd.size(), circInd.data(), GL_STATIC_DRAW);


    //// position attribute
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    //// vertex normal attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    //glEnableVertexAttribArray(1);




    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);




    Cylinder sphere = Cylinder();
    Wheel wheel = Wheel();
  
    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);






       



        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
       pointlight4.setUpPointLight(lightingShader);
       pointlight5.setUpPointLight(lightingShader);
       pointlight6.setUpPointLight(lightingShader);
       pointlight7.setUpPointLight(lightingShader);
       pointlight8.setUpPointLight(lightingShader);
       pointlight9.setUpPointLight(lightingShader);
       pointlight10.setUpPointLight(lightingShader);
       lightingShader.use();

       


       lightingShader.setVec3("directionalLight.directiaon", 0.5f, -3.0f, -3.0f);
       lightingShader.setVec3("directionalLight.ambient", ambientR, ambientG, ambientB);
       lightingShader.setVec3("directionalLight.diffuse", .8f, .8f, .8f);
       lightingShader.setVec3("directionalLight.specular", 1.0f, 1.0f, 1.0f);


       lightingShader.setBool("directionLightOn", directionLightOn);


       spotlight1.setUpspotLight(lightingShader);

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);


        
      
        
        wheel.drawWheel(lightingShader, model* glm::scale(identityMatrix, glm::vec3(.1,.01, .1))* glm::translate(identityMatrix, glm::vec3(-3.9, -5.0, -0.5)));
        //wheel.drawSphere(lightingShader, modelForSphere * glm::scale(model, glm::vec3(1, .07*2, 1)) * glm::translate(model, glm::vec3(-1.9, -5.0, -0.5)));

   

        cabin(cubeVAO, lightingShader, model);

        platform(cubeVAO, lightingShader, model);

        //left Platform

        glm::mat4 translate = glm::mat4(1.0f);
        translate = glm::translate(identityMatrix, glm::vec3(-4.7*4, 0.0, 0.0));
        platform(cubeVAO, lightingShader, model*translate);

        door(cubeVAO, lightingShader, model);



        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);


        



        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
                       
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            
            model = glm::scale(model, glm::vec3(.6, .1, .2)); // Make it a smaller cube
            model = glm::translate(model, glm::vec3(-.5 , -0.1, -0.2));
            model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix * model;
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void door(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    //AAfter chair divider
    scale = glm::scale(model, glm::vec3(1.75, 2.5, 0.0));
    translate = glm::translate(model, glm::vec3(-0.1, -.4, .4));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);



    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.75, 2.5, 0.0));
    translate = glm::translate(model, glm::vec3(2.85, -.4, .4));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);


    //Red
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, -.4, .2));
    scale = glm::scale(model, glm::vec3(0.0, .1, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //Ash
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, -.3, .2));
    scale = glm::scale(model, glm::vec3(0.0, .2, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, -.1, .2));
    scale = glm::scale(model, glm::vec3(0.0, .1, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //green Line
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 0.0, .2));
    scale = glm::scale(model, glm::vec3(0.0, .4, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);


    //upper red
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 1.8, .2));
    scale = glm::scale(model, glm::vec3(0.0, .3, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //roof
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 2.1, .2));
    scale = glm::scale(model, glm::vec3(4.7, .3, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);


    //green cube
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 0.4, 0.0));
    scale = glm::scale(model, glm::vec3(0.0, 1.4, 2.4));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

    //floor
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(4.7, 0.0, 2.2));
    translate = glm::translate(model, glm::vec3(-.1, -.4, .2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.549, 0.549, 0.533);


    //Red
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.6, -.4, .2));
    scale = glm::scale(model, glm::vec3(0.0, .1, .8));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //Ash
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.6, -.3, .2));
    scale = glm::scale(model, glm::vec3(0.0, .2, .8));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.6, -.1, .2));
    scale = glm::scale(model, glm::vec3(0.0, .1, .8));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //green Line
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.6, 0.0, .2));
    scale = glm::scale(model, glm::vec3(0.0, .4, .8));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);


    //upper red
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.6, 1.8, .2));
    scale = glm::scale(model, glm::vec3(0.0, .3, .8));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //green cube
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.6, 0.4, 0.0));
    scale = glm::scale(model, glm::vec3(0.0, 1.4, 1.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

    //green cube 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.6, -0.4, 2.0));
    scale = glm::scale(model, glm::vec3(0.0, 2.5, 0.4));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

    frame(cubeVAO, lightingShader, alTogether);

    //back side Green
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, -.4, 2.4));
    scale = glm::scale(model, glm::vec3(4.7, 2.5, 0.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

}

void frame(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
        
    scale = glm::scale(model, glm::vec3(0.1, 2.5, .1));
    translate = glm::translate(model, glm::vec3(4.5, -.4, 1.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.5, -.4, 1.0));
    scale = glm::scale(model, glm::vec3(.1, .1, 1.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.5, +2.1, 1.0));
    scale = glm::scale(model, glm::vec3(.1, -.1, 1.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1, 2.5, .1));
    translate = glm::translate(model, glm::vec3(4.5, -.4, 2.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);



    //Second Frame
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1, 2.3, .1));
    translate = glm::translate(model, glm::vec3(4.4, -.3, 1.1));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.4, -.3, 1.2));
    scale = glm::scale(model, glm::vec3(.1, .1, .8));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.4, +1.9, 1.2));
    scale = glm::scale(model, glm::vec3(.1, .1, .8));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    

    scale = glm::scale(model, glm::vec3(0.1, 2.3, .1));
    translate = glm::translate(model, glm::vec3(4.4, -.3, 1.9));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

}



void platform(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(4.7, -1.0, -48.2));
    translate = glm::translate(model, glm::vec3(4.7, -.4, .2));
    model = alTogether * translate *scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

    for (int i = 0; i < 5; i++)
    {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);

        scale = glm::scale(model, glm::vec3(1.0, 5.0, -1.0));
        translate = glm::translate(model, glm::vec3(6.55, -.4, -2.0-(9.2*i)));
        model = alTogether * translate * scale;
        drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);
    }

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(4.7, -1.0, -48.2));
    translate = glm::translate(model, glm::vec3(4.7, -.4+5.0+1, .2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

    
    

}

void cabin(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float distance = 2.4;
    for (int i = 0; i < 10; i++)

    {
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f), translate2 = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);


        translate = glm::translate(model, glm::vec3(0.0, 0, -i*distance));

        chair(cubeVAO, lightingShader, alTogether*translate);


        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);


        glm::mat4 reflectmatrix = glm::mat4(1.0f);
        reflectmatrix[2][2] = -1.0f;

        translate = glm::translate(model, glm::vec3(0.0, 0, -2.0 - i * distance));
        chair(cubeVAO, lightingShader, alTogether * translate * reflectmatrix);





        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(3.0, 0, -i * distance));

        model = alTogether  * translate;
        chair(cubeVAO, lightingShader, model);


        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        translate2 = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(3.0, 0, -2.0 - i * distance));
        model = alTogether * translate * reflectmatrix;
        chair(cubeVAO, lightingShader, model);

    }


    //Floor
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(4.7, 0.0, -24.2));
    translate = glm::translate(model, glm::vec3(-.1, -.4, .2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, 0.549, 0.549, 0.533);



    //leftwall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    model = alTogether;
    wallTrain(cubeVAO, lightingShader, model);



    // Curvy Upper 

    //curvy ash upper
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 2.1, .2));
    scale = glm::scale(model, glm::vec3(4.7, .3, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

    //right wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.7, 0.0, 0.0));
    model = alTogether* translate;
    wallTrain(cubeVAO, lightingShader, model);


    //Bunker Left
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.1, 1.6, .2));
    scale = glm::scale(model, glm::vec3(0.09, 0.09, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.4, 1.6, .2));
    scale = glm::scale(model, glm::vec3(0.09, 0.09, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(0.7, 1.6, .2));
    scale = glm::scale(model, glm::vec3(0.09, 0.09, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);


    //Bunker Right
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.7-0.4, 1.6, .2));
    scale = glm::scale(model, glm::vec3(0.09, 0.09, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.7 - 0.4 -0.4, 1.6, .2));
    scale = glm::scale(model, glm::vec3(0.09, 0.09, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(4.7 - 0.4-0.7, 1.6, .2));
    scale = glm::scale(model, glm::vec3(0.09, 0.09, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

}


void chair(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{


    //Back
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(1.5, 1.0, .2));
    model = alTogether * scale ;
    drawCube(cubeVAO, lightingShader, model, (float)19/255, (float)42/255, (float)48/255);


    //Base
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(1.5, 0.2, -0.6));

    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, (float)19 / 255, (float)42 / 255, (float)48 / 255);


    //Left leg 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(.1, -0.4, -.5));

    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, (float)136 / 255, (float)139 / 255, (float)141 / 255);

    //Right leg 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(.1, -0.4, -.5));

    translate = glm::translate(model, glm::vec3(1.4, 0.0, 0.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)136 / 255, (float)139 / 255, (float)141 / 255);

}


void wallTrain(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    //red
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, -.4, .2));
    scale = glm::scale(model, glm::vec3(0.0, .1, -24.2));
    model = alTogether* translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //ash
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, -.3, .2));
    scale = glm::scale(model, glm::vec3(0.0, .2, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

    //red
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, -.1, .2));
    scale = glm::scale(model, glm::vec3(0.0, .1, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

    //green Line
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 0.0, .2));
    scale = glm::scale(model, glm::vec3(0.0, .4, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

    //green cube
    float translateFactor = 2.4;
    for (int i = 0; i < 10; i++)
    {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(-.1, 0.4, .2-i*translateFactor));
        scale = glm::scale(model, glm::vec3(0.0, 1.4, -.8));
        model = alTogether * translate * scale;
        drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(-.1, 0.4, .2 - 1.6 - i * translateFactor));
        scale = glm::scale(model, glm::vec3(0.0, 1.4, -.8));
        model = alTogether * translate * scale;
        drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);

        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        translate = glm::translate(model, glm::vec3(-.1, 1.0, .2 - .8 - i * translateFactor));
        scale = glm::scale(model, glm::vec3(0.0, .8, -.8));
        model = alTogether * translate * scale;
        drawCube(cubeVAO, lightingShader, model, (float)18 / 255, (float)129 / 255, (float)11 / 255);
    }   

    //upper red
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 1.8, .2));
    scale = glm::scale(model, glm::vec3(0.0, .3, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)233 / 255, (float)28 / 255, (float)25 / 255);

}


void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(r, g, b));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void drawtri(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_INT, 0);
}

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //blanket
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.01;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.01;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.01;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.01;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.01;
    //if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        pointlight2.turnOff();
        pointlight3.turnOff();
        pointlight4.turnOff();
        pointlight5.turnOff();
        pointlight6.turnOff();
        pointlight7.turnOff();
        pointlight8.turnOff();
        pointlight9.turnOff();
        pointlight10.turnOff();


    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        
        pointlight1.turnOn();
        pointlight2.turnOn();
        pointlight3.turnOn();
        pointlight4.turnOn();
        pointlight5.turnOn();
        pointlight6.turnOn();
        pointlight7.turnOn();
        pointlight8.turnOn();
        pointlight9.turnOn();
        pointlight10.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        spotlight1.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        spotlight1.turnOff();

    }
    
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        directionLightOn = !directionLightOn;
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight2.turnAmbientOn();
        pointlight3.turnAmbientOn();
        pointlight4.turnAmbientOn();
        pointlight5.turnAmbientOn();
        pointlight6.turnAmbientOn();
        pointlight7.turnAmbientOn();
        pointlight8.turnAmbientOn();
        pointlight9.turnAmbientOn();
        pointlight10.turnAmbientOn();
        spotlight1.turnAmbientOn();

    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight2.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        pointlight4.turnDiffuseOn();
        pointlight5.turnDiffuseOn();
        pointlight6.turnDiffuseOn();
        pointlight7.turnDiffuseOn();
        pointlight8.turnDiffuseOn();
        pointlight9.turnDiffuseOn();
        pointlight10.turnDiffuseOn();
        spotlight1.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
        pointlight5.turnSpecularOn();
        pointlight6.turnSpecularOn();
        pointlight7.turnSpecularOn();
        pointlight8.turnSpecularOn();
        pointlight9.turnSpecularOn();
        pointlight10.turnSpecularOn();
        spotlight1.turnSpecularOn();
    }

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        /*pointlight1.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight2.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight3.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight4.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight4.specular = glm::vec3(0.0, 1.0, 0.0);*/

    }


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
