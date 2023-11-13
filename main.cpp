//
//  main.cpp
//  3D Object Drawing
//
//  Abrar Hasan
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
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
#include "cube.h"
#include "stb_image.h"
#include "semiCylinder.h"
#include "sphere.h"
#include "semiWheel.h"
#include "semiCircle.h"


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
void drawdoor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void boundary(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawAludoor(Shader& lightingShader, glm::mat4 alTogether, Cube& cube, Cube& cube2);
void drawsquareroof(Shader& lightingShaderWithTexture, glm::mat4 alTogether, Cube& cube5);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);



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
float moveZ = 0.0;
int n;
float pi = 3.1416;

bool directionLightOn = true, moveVar = false;
float ambientR=.2, ambientG=.2, ambientB=.2;




// camera
Camera camera(glm::vec3(1.0f, 5.1f, 7.2f));
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
    glm::vec3(pointLightXPos,pointLightYPos,-1.2f+moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2-(2.4*1)+ moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 2)+moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 3) + moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 4) + moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 5) + moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 6) + moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 7) + moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 8) + moveZ),
    glm::vec3(pointLightXPos,pointLightYPos,-1.2 - (2.4 * 9) + moveZ),
    glm::vec3(-14.0,4.7,31.5)

    
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

PointLight pointlight11(

    pointLightPositions[10].x, pointLightPositions[10].y, pointLightPositions[10].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    specularR, specularG, specularB,       // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    11       // light number
);

float spotLightXpos = -1.9-2.7  , spotLightYpos = -.4 +2.0 +1 ;
glm::vec3 spotPositions[] = {
    glm::vec3(spotLightXpos,spotLightXpos,-1.2f+moveZ),
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
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
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

    float railTrackX=-8.5, railTrackY=-2.0, railTrackZ=0.0;
    string diffuseMapPath2 = "nmu.jpeg";
    string specularMapPath2 = "nmu.jpeg";

    //platform(lightingShader, modelMatrixForContainer);

    string diffuseMapPath = "wall.jpg";
    string specularMapPath = "wall.jpg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 5.0f, 5.0f);


    unsigned int diffMap2 = loadTexture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cylinder sphere = Cylinder();
    Wheel wheel = Wheel(1.0f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);;
  

    string diffuseMapPath3 = "metal2.jpg";
    string specularMapPath3 = "metalS.jpg";


    unsigned int diffMap3 = loadTexture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = loadTexture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube3 = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath4 = "stone.jpg";
    string specularMapPath4 = "stone.jpg";


    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube4 = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 3.0f, 3.0f);


    string diffuseMapPath5 = "whiteWall.jpg";
    string specularMapPath5 = "whiteBackground.png";

    unsigned int diffMap5 = loadTexture(diffuseMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap5 = loadTexture(specularMapPath5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube5 = Cube(diffMap5, specMap5, 32.0f, 0.0f, 0.0f, 2.0f, 2.0f);


    string diffuseMapPath6 = "mosaic.jpg";
    string specularMapPath6 = "mosaic.jpg";

    unsigned int diffMap6 = loadTexture(diffuseMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap6 = loadTexture(specularMapPath6.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube6 = Cube(diffMap6, specMap6, 32.0f, 0.0f, 0.0f, 30.0f, 15.0f);


    string diffuseMapPath7 = "nosmoking.png";
    string specularMapPath7 = "nosmoking.png";

    unsigned int diffMap7 = loadTexture(diffuseMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap7 = loadTexture(specularMapPath7.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube7 = Cube(diffMap7, specMap7, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath8 = "trainfare.jpg";
    string specularMapPath8 = "trainfare.jpg";
    unsigned int diffMap8 = loadTexture(diffuseMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap8 = loadTexture(specularMapPath8.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube8 = Cube(diffMap8, specMap8, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath9 = "mosaic.jpg";
    string specularMapPath9 = "mosaic.jpg";

    unsigned int diffMap9 = loadTexture(diffuseMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap9 = loadTexture(specularMapPath9.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube9 = Cube(diffMap9, specMap9, 32.0f, 0.0f, 0.0f, 9.0f, 3.0f);
    

    string diffuseMapPath10 = "marbel0.jpg";
    string specularMapPath10 = "marbel0.jpg";

    unsigned int diffMap10 = loadTexture(diffuseMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap10= loadTexture(specularMapPath10.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube10 = Cube(diffMap10, specMap10, 32.0f, 0.0f, 0.0f, 15.0f, 15.0f);

    string diffuseMapPath11 = "counter1.png";
    string specularMapPath11 = "counter1.png";

    unsigned int diffMap11 = loadTexture(diffuseMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap11 = loadTexture(specularMapPath11.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube11 = Cube(diffMap11, specMap11, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath12 = "counter2.jpg";
    string specularMapPath12 = "counter2.jpg";

    unsigned int diffMap12 = loadTexture(diffuseMapPath12.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap12 = loadTexture(specularMapPath12.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube12 = Cube(diffMap12, specMap12, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath13 = "counter3.jpg";
    string specularMapPath13 = "counter3.jpg";

    unsigned int diffMap13 = loadTexture(diffuseMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap13 = loadTexture(specularMapPath13.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube13 = Cube(diffMap13, specMap13, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath14 = "counter4.jpg";
    string specularMapPath14 = "counter4.jpg";

    unsigned int diffMap14 = loadTexture(diffuseMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap14 = loadTexture(specularMapPath14.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube14 = Cube(diffMap14, specMap14, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath15 = "fare.png";
    string specularMapPath15 = "fare.png";

    unsigned int diffMap15 = loadTexture(diffuseMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap15 = loadTexture(specularMapPath15.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube15 = Cube(diffMap15, specMap15, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);



    string diffuseMapPath16 = "no_smoking.png";
    string specularMapPath16 = "no_smoking.png";

    unsigned int diffMap16 = loadTexture(diffuseMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap16 = loadTexture(specularMapPath16.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube16 = Cube(diffMap16, specMap16, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath17 = "wooddoor.png";
    string specularMapPath17 = "wooddoor.png";

    unsigned int diffMap17 = loadTexture(diffuseMapPath17.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap17 = loadTexture(specularMapPath17.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube17 = Cube(diffMap17, specMap17, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath18 = "booking.png";
    string specularMapPath18 = "booking.png";

    unsigned int diffMap18 = loadTexture(diffuseMapPath18.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap18 = loadTexture(specularMapPath18.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube18 = Cube(diffMap18, specMap18, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath19 = "alu4.jpg";
    string specularMapPath19 = "whiteBackground.png";

    unsigned int diffMap19 = loadTexture(diffuseMapPath19.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap19 = loadTexture(specularMapPath19.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube19 = Cube(diffMap19, specMap19, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapPath20 = "blueglass.png";
    string specularMapPath20 = "whiteBackground.png";

    unsigned int diffMap20 = loadTexture(diffuseMapPath20.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap20 = loadTexture(specularMapPath20.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube20 = Cube(diffMap20, specMap20, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);




    
    semiCylinder semicylinder = semiCylinder(1.0f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);


    //ourShader.use();
    //lightingShader.use();

    //glm::mat4 move = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
    
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
        glClearColor((float)253/255, (float)184 / 255, (float)19 / 255, 1.0f);
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
       pointlight11.setUpPointLight(lightingShader);
       lightingShader.use();

       


       lightingShader.setVec3("directionalLight.directiaon", 0.5f, -3.0f, -3.0f);
       lightingShader.setVec3("directionalLight.ambient", .5f, .5f, .5f);
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

        glm::mat4 moveM = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, moveZ));


        
       
        wheel.drawWheel(lightingShader, model* moveM * glm::translate(identityMatrix, glm::vec3(0.4, -1.4, -1.5)) * glm::rotate(identityMatrix, glm::radians((float)90.0), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(identityMatrix, glm::vec3(.4,.02, .4)));
        //wheel.drawSphere(lightingShader, modelForSphere * glm::scale(model, glm::vec3(1, .07*2, 1)) * glm::translate(model, glm::vec3(-1.9, -5.0, -0.5)));
        

        
        
        glm::mat4 rotateSemi = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 translateSemi = glm::translate(identityMatrix, glm::vec3(-13.0, -1.0, 25.0));
        glm::mat4 scaleSemi = glm::scale(identityMatrix, glm::vec3(0.25, .3, -0.25));
        semicylinder.drawsemiCylinder(lightingShader, model * translateSemi* rotateSemi * scaleSemi);

        rotateSemi = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateSemi = glm::translate(identityMatrix, glm::vec3(-11.0, -1.0, 25.0));
        scaleSemi = glm::scale(identityMatrix, glm::vec3(0.25, .3, -0.25));
        semicylinder.drawsemiCylinder(lightingShader, model * translateSemi * rotateSemi * scaleSemi);


        rotateSemi = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateSemi = glm::translate(identityMatrix, glm::vec3(-4.0, 1.5, 25.0));
        scaleSemi = glm::scale(identityMatrix, glm::vec3(0.25, .18, -0.25));
        semicylinder.drawsemiCylinder(lightingShader, model* translateSemi* rotateSemi* scaleSemi);


        rotateSemi = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateSemi = glm::translate(identityMatrix, glm::vec3(-3.0, 1.5, 25.0));
        scaleSemi = glm::scale(identityMatrix, glm::vec3(0.25, .18, -0.25));
        semicylinder.drawsemiCylinder(lightingShader, model* translateSemi* rotateSemi* scaleSemi);


        //glass
        glm::mat4 modelCube = glm::mat4(1.0f);
        glm::mat4 translateCube = glm::mat4(1.0f);
        glm::mat4 scaleCube = glm::mat4(1.0f);
        translateCube = glm::translate(identityMatrix, glm::vec3(-13.5, 1.5, 25.0));
        scaleCube = glm::scale(identityMatrix, glm::vec3(3.0, -2.2, -0.1));;
        modelCube = translateCube * scaleCube;
        drawCube(cubeVAO, lightingShader, model* modelCube, (float)3 / 255, (float)127 / 255, (float)243 / 255);


        modelCube = glm::mat4(1.0f);
        translateCube = glm::mat4(1.0f);
        scaleCube = glm::mat4(1.0f);
        translateCube = glm::translate(identityMatrix, glm::vec3(-13.5, 1.7, 25.0));
        scaleCube = glm::scale(identityMatrix, glm::vec3(3.0, 2.8, -0.1));;
        modelCube = translateCube * scaleCube;
        drawCube(cubeVAO, lightingShader, model* modelCube, (float)3 / 255, (float)127 / 255, (float)243 / 255);


        modelCube = glm::mat4(1.0f);
        translateCube = glm::mat4(1.0f);
        scaleCube = glm::mat4(1.0f);
        translateCube = glm::translate(identityMatrix, glm::vec3(-4.5, 1.5, 25.0));
        scaleCube = glm::scale(identityMatrix, glm::vec3(1.0, -1.2, -0.1));;
        modelCube = translateCube * scaleCube;
        drawCube(cubeVAO, lightingShader, model* modelCube, (float)3 / 255, (float)127 / 255, (float)243 / 255);

        modelCube = glm::mat4(1.0f);
        translateCube = glm::mat4(1.0f);
        scaleCube = glm::mat4(1.0f);
        translateCube = glm::translate(identityMatrix, glm::vec3(-3.3, 1.5, 25.0));
        scaleCube = glm::scale(identityMatrix, glm::vec3(1.0, -1.2, -0.1));;
        modelCube = translateCube * scaleCube;
        drawCube(cubeVAO, lightingShader, model* modelCube, (float)3 / 255, (float)127 / 255, (float)243 / 255);


        modelCube = glm::mat4(1.0f);
        translateCube = glm::mat4(1.0f);
        scaleCube = glm::mat4(1.0f);
        translateCube = glm::translate(identityMatrix, glm::vec3(-4.5, 1.7, 25.0));
        scaleCube = glm::scale(identityMatrix, glm::vec3(2.2, 3.0, -0.1));;
        modelCube = translateCube * scaleCube;
        drawCube(cubeVAO, lightingShader, model* modelCube, (float)3 / 255, (float)127 / 255, (float)243 / 255);

        //drawdoor(cubeVAO, lightingShader, model);

        for (int i = 0; i < 9; i++)
        {
            translateCube = glm::mat4(1.0f);
            translateCube = glm::translate(identityMatrix, glm::vec3(.4*i, 0.0, 0.0));
            drawdoor(cubeVAO, lightingShader, model*translateCube);
        }


        for (int i = 0; i < 9; i++)
        {
            translateCube = glm::mat4(1.0f);
            translateCube = glm::translate(identityMatrix, glm::vec3(13+.4 * i, 0.0, 2.8));
            drawdoor(cubeVAO, lightingShader, model * translateCube);
        }


        glm:: mat4 rotateDoor = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        for (int i = 0; i < 9; i++)
        {
            translateCube = glm::mat4(1.0f);
            glm::mat4 translate22 = glm::translate(identityMatrix, glm::vec3(-8.4, -0.7, 25.0));
            glm::mat4 translate222 = glm::translate(identityMatrix, glm::vec3(8.4, 0.7, -25.0));
            translateCube = glm::translate(identityMatrix, glm::vec3(18.5 , 0.0, 8.6+.4 * i));
            drawdoor(cubeVAO, lightingShader, model * translateCube* translate22 * rotateDoor* translate222);
        }
       


        if (moveZ > -15.0 && moveVar)
        {
            moveZ = moveZ - .1;
        }
        
        

        cabin(cubeVAO, lightingShader, model* glm::translate(identityMatrix, glm::vec3(0.0, 0.0, moveZ)));

        //platform(cubeVAO, lightingShader, model);

        //left Platform

        glm::mat4 translate = glm::mat4(1.0f);
        translate = glm::translate(identityMatrix, glm::vec3(-4.7*4, 0.0, 0.0));
        platform(cubeVAO, lightingShader, model*translate);

        door(cubeVAO, lightingShader, model* glm::translate(identityMatrix, glm::vec3(0.0, 0.0, moveZ)));

        glm::mat4 reflectmatrix = glm::mat4(1.0f);
        reflectmatrix[2][2] = -1.0f;

        translate = glm::mat4(1.0f);
        translate = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, -23.5));
        //chair(cubeVAO, lightingShader, alTogether* translate* reflectmatrix);

        door(cubeVAO, lightingShader, model*glm::translate(identityMatrix, glm::vec3(0.0, 0.0, moveZ)) * translate*reflectmatrix);

        //ticket_counter(cubeVAO, lightingShader, model);


        for(int i=0;i<4;i++)
        {
            translate = glm::mat4(1.0f);
            translate = glm::translate(identityMatrix, glm::vec3(-4.0*i, 0.0, 0.0));
            boundary(cubeVAO, lightingShader, model* translate);

        }

        

        


        


        // Orange Pillers
        glm::mat4 translateP = glm::mat4(1.0f);
        glm::mat4 scaleP = glm::mat4(1.0f); 
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(-13.0, -1.0, 17.0));




        
        Cylinder c = Cylinder(0.65f, 36, 18, glm::vec3((float)255 / 255, (float)89 / 255, (float)0.0 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);
        c.drawSphere(lightingShader, model*translateP*scaleP);

        

        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(-7.0, -1.0, 17.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);

        



        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(-1.0, -1.0, 17.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);


        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(4.0, -1.0, 17.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);


        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(9.0, -1.0, 22.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);




        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(-13.0, -1.0, 22.0));


       
        c.drawSphere(lightingShader, model* translateP* scaleP);



        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(-7.0, -1.0, 22.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);




        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(-1.0, -1.0, 22.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);


        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(4.0, -1.0, 22.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);


        translateP = glm::mat4(1.0f);
        scaleP = glm::mat4(1.0f);
        scaleP = glm::scale(identityMatrix, glm::vec3(1.0, .3, -1.0));
        translateP = glm::translate(identityMatrix, glm::vec3(9.0, -1.0, 22.0));
        c.drawSphere(lightingShader, model* translateP* scaleP);




        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);


        



        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 11; i++)
        {
                       
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            
            model = glm::scale(model, glm::vec3(.6, .1, .2)); // Make it a smaller cube
            model = glm::translate(model, glm::vec3(-.5 , -0.1, -0.2));
            model = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, moveZ))*translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix * model;
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        
        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        pointlight8.setUpPointLight(lightingShaderWithTexture);
        pointlight9.setUpPointLight(lightingShaderWithTexture);
        pointlight10.setUpPointLight(lightingShaderWithTexture);
        pointlight11.setUpPointLight(lightingShaderWithTexture);


        lightingShaderWithTexture.setVec3("directionalLight.directiaon", 0.5f, -3.0f, -3.0f);
        lightingShaderWithTexture.setVec3("directionalLight.ambient", ambientR, ambientG, ambientB);
        lightingShaderWithTexture.setVec3("directionalLight.diffuse", .8f, .8f, .8f);
        lightingShaderWithTexture.setVec3("directionalLight.specular", 1.0f, 1.0f, 1.0f);

        
        lightingShaderWithTexture.setBool("directionLightOn", directionLightOn);


        spotlight1.setUpspotLight(lightingShaderWithTexture);


        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection1 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection1);

        // camera/view transformation
        glm::mat4 view1 = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view1);


        

        

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f), mtranslateMatrix, mrotateXMatrix, mrotateYMatrix, mrotateZMatrix, mscaleMatrix;
        //modelMatrixForContainer = glm::translate(model, glm::vec3(-0.5f, -0.5f, -0.5f));
        mtranslateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        mrotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        mrotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        mrotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        mscaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        modelMatrixForContainer = mtranslateMatrix * mrotateXMatrix * mrotateYMatrix * mrotateZMatrix * mscaleMatrix;
        
        


        identityMatrix = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);



        for (int i = 0; i < 8; i++)
        {
            model = glm::mat4(1.0f);
            translate = glm::mat4(1.0f);
            scale = glm::mat4(1.0f);

            scale = glm::scale(model, glm::vec3(1.0, 5.0, -1.0));
            translate = glm::translate(model, glm::vec3(6.55, -.4, 13.0 - (9.2 * i)));
            model = modelMatrixForContainer * translate * scale;
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);


            model = glm::mat4(1.0f);
            translate = glm::mat4(1.0f);
            scale = glm::mat4(1.0f);
            scale = glm::scale(model, glm::vec3(4.7, -1.0, -9.64 * i));
            translate = glm::translate(model, glm::vec3(4.7, -.4, 15.2));
            model = modelMatrixForContainer * translate * scale;
            cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }

        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);

        scale = glm::scale(model, glm::vec3(4.7, -1.0, -63.2));
        translate = glm::translate(model, glm::vec3(4.7, -.4 + 5.0 + 1, 15.2));
        model = modelMatrixForContainer * translate * scale;
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        

        


        glm::mat4 modelMatrixForContainer2 = glm::mat4(1.0f);
        glm::mat4 modeltranslate = glm::translate(identityMatrix, glm::vec3(4.65, .4, 0.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(0.0, .3, .3));

        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* moveM * modeltranslate* scale);

        for (int i = 0; i < 25; i++)
        {
            railTrackZ = 0.0;
            railTrackZ = railTrackZ - 2.2 * i;
            //Rail Track
            glm::mat4 modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + .075, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            //Right Track

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 3.0, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + .075 + 3.0, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 3.0, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            //Middle Track


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + .075 + 2.5, railTrackY, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX + 2.5, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);



            //Stones
            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .2, railTrackY - 0.15, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(1.5, -0.1, -2.0));

            //cube4.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            //middle piller


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .2, railTrackY - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(3.75, -0.1, -.2));

            cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX- .2, railTrackY - 0.3, railTrackZ - .8));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(3.75, -0.1, -.2));

            cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX - .2, railTrackY - 0.3, railTrackZ - 1.6));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(3.75, -0.1, -.2));

            cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);
        }

        float railTrackX1 = 1.0;
        float railTrackY1 = -2.0;
        
        for (int i = 0; i < 25; i++)
        {
            railTrackZ = 0.0;
            railTrackZ = railTrackZ - 2.2 * i;
            //Rail Track
            glm::mat4 modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1, railTrackY1, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 + .075, railTrackY1, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1, railTrackY1 - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            //Right Track

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 + 3.0, railTrackY1, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 + .075 + 3.0, railTrackY1, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 + 3.0, railTrackY1 - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            //Middle Track


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 + 2.5, railTrackY1, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 + .075 + 2.5, railTrackY1, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.15, -.2, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);

            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 + 2.5, railTrackY1 - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.3, .1, -2.2));

            cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);



            //Stones
            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 - .2, railTrackY1 - 0.15, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(1.5, -0.1, -2.0));

            //cube4.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            //middle piller


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 - .2, railTrackY1 - 0.3, railTrackZ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(3.75, -0.1, -.2));

            cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 - .2, railTrackY1 - 0.3, railTrackZ - .8));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(3.75, -0.1, -.2));

            cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);


            modelMatrixForContainer3 = glm::mat4(1.0f);
            modeltranslate = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(railTrackX1 - .2, railTrackY1 - 0.3, railTrackZ - 1.6));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(3.75, -0.1, -.2));

            cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer3 * modeltranslate * scale);
        }

        // Platform of ticket counter

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0, -1.0, 15.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(25.0, .3, 10.0));

        cube6.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);



        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0, 4.7, 15.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(25.0, .3, 10.0+3.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0, -1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 5.7, -0.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        
        modeltranslate = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-13.5, 1.5, 24.7));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(3.0, 0.1, -0.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture,  modeltranslate* scale);


        modeltranslate = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-13.5, 1.6, 24.7));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(3.0, 0.1, -0.6));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modeltranslate* scale);
        modeltranslate = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-13.5, 1.7, 24.7));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(3.0, 0.1, -0.7));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modeltranslate* scale);


        modeltranslate = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-13.5, 1.5, 24.7));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(3.0, 0.1, -0.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modeltranslate* scale);


       


        modeltranslate = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-13.5, 4.5, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(3.0, .2, -0.1));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modeltranslate* scale);


       

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-10.5, -1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 5.7, -0.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-9.0, -1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(0.5, 5.7, 3.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-8.5, -1.0+3.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(3.5, 2.7, 3.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);
        


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-5.0, -1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(0.5, 5.7, 3.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-4.5, .3, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.2, -1.0, -0.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-3.5, 0.3, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(0.2, 1.2, -0.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-4.5, 1.5, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.2, 0.2, -0.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-3.5, 1.5, 24.7));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.0, 0.2, 0.0));
        cube7.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-2.3, 1.5, 24.7));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 2.0, 0.0));
        cube8.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-2.3, -1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.2, 5.7, -0.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-0.1, -1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.0, 5.7, 2.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-0.1, -1.0, 25.0+2.5));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(5.0, 5.7, 0.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(.9, -1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(9.1, .3, 2.5));

        cube9.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(4.5+3.6, -1.0, 27.5));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 5.7, .5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(4.5 , 2.0, 27.5));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(3.6, 5.7-3, .5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0,-1.0, 25.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(25, .3, 20.0));
        cube10.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0, 4.7, 28.6));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(0.1, 1, 1.0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);
        

        //Roof of Ticket counter

        for (int j = 0; j < 20; j++)
        {
            for (int i = 0; i < 25; i++)
            {
                modelMatrixForContainer2 = glm::mat4(1.0f);
                modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0 + i, 4.7, 28.5+j));
                scale = glm::mat4(1.0f);
                scale = glm::scale(identityMatrix, glm::vec3(1.0, 1, .1));
                cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


                modelMatrixForContainer2 = glm::mat4(1.0f);
                modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0 + i, 5.7, 28.5 + j));
                scale = glm::mat4(1.0f);
                scale = glm::scale(identityMatrix, glm::vec3(1.0, 0.1, 1.0));
                cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);

                modelMatrixForContainer2 = glm::mat4(1.0f);
                modeltranslate = glm::translate(identityMatrix, glm::vec3(-14.0 + i, 4.7, 28.6 + j));
                scale = glm::mat4(1.0f);
                scale = glm::scale(identityMatrix, glm::vec3(0.1, 1, 1.0));
                cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);

                modelMatrixForContainer2 = glm::mat4(1.0f);
                modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0 + i, 4.7, 29.5 + j));
                scale = glm::mat4(1.0f);
                scale = glm::scale(identityMatrix, glm::vec3(1.0, 1, .1));
                cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);

            }

        }

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0, -1.0, 45.125));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(25, 1.5, -.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(8.0, 0.5, 45.125));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 2.1, -.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(8.0-4.0, 0.5, 45.125));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 2.1, -.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(8.0 - 4.0*2, 0.5, 45.125));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 2.1, -.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(8.0 - 4.0 * 3, 0.5, 45.125));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 2.1, -.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15, 0.5, 45.125));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(9.0, 2.1, -.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-15, 0.5+2.1, 45.125));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(25.0, 1.9, -.25));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(6.0, 2.7, 44.8));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 0.7, 0.0));
        cube11.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(6.0-4.0, 2.7, 44.8));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 0.7, 0.0));
        cube12.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(6.0-8.0, 2.7, 44.8));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 0.7, 0.0));
        cube13.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(6.0 - 12.0, 2.7, 44.8));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(1.5, 0.7, 0.0));
        cube14.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2 * modeltranslate * scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(-12, 0.0, 44.8));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.5, 3.0, 0.0));
        cube15.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(9.9, 3.0, 44.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(0.0, .7, 1.5));
        
        reflectmatrix = glm::mat4(1.0f);
        reflectmatrix[2][2] = -1.0f;

        cube16.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2*modeltranslate* reflectmatrix* scale);



        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(10, -1.0, 45.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(.25, 5.7, -4.0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(10, -1.0, 45.0 - 4.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(.25, 3.7, -1.5));
        cube17.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(10, -1.0, 45.0 - 5.5));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(.25, 5.7, -2.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(10, -1.0, 45.0 - 11.5));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(.25, 5.7, -5.4));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(10, -1.0 + 3.7, 45.0 - 4.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(.25, 2.0, -1.5));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);

        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(10, -1.0 + 3.0, 45.0 - 7.5));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(.25, 2.7, -4.0));
        cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);


        modelMatrixForContainer2 = glm::mat4(1.0f);
        modeltranslate = glm::translate(identityMatrix, glm::vec3(9.9, -1.0 + 3.7, 45.0 - 9.0));
        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(0.0, 0.5, -1.0));
        cube18.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer2* modeltranslate* scale);



        glm::mat4 modeltranslate3 = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 4.0));

        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 1.0, 1.0));
        drawAludoor(lightingShaderWithTexture, modeltranslate3, cube19, cube20);

        glm::mat4 modeltranslate1 = glm::translate(identityMatrix, glm::vec3(15, 0.0, -45.0 + 9.0));
        glm::mat4 modeltranslate2 = glm::translate(identityMatrix, glm::vec3(-10 - 5, 0.0, 45.0 - 9.0));
        modeltranslate3 = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
        glm::mat4 rotate11 = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawAludoor(lightingShaderWithTexture, modeltranslate3* modeltranslate2* rotate11* modeltranslate1, cube19, cube20);



        modeltranslate1 = glm::translate(identityMatrix, glm::vec3(15, 0.0, -45.0 + 9.0));
        modeltranslate2 = glm::translate(identityMatrix, glm::vec3(-10 - 5, 0.0, 45.0 - 9.0));
        modeltranslate3 = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.5));
        rotate11 = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawAludoor(lightingShaderWithTexture, modeltranslate3* modeltranslate2* rotate11* modeltranslate1, cube19, cube20);



        modeltranslate3 = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, -2.0));

        scale = glm::mat4(1.0f);
        scale = glm::scale(identityMatrix, glm::vec3(2.0, 1.0, 1.0));
        drawAludoor(lightingShaderWithTexture, modeltranslate3, cube19, cube20);


        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                modeltranslate3 = glm::translate(identityMatrix, glm::vec3(-2.0-j, -1.0, 2.0+i));
                drawsquareroof(lightingShaderWithTexture, modeltranslate3, cube5);
            }

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

void drawsquareroof(Shader& lightingShaderWithTexture, glm::mat4 alTogether, Cube& cube5)

{

    
            glm::mat4 modelMatrixForContainer2 = glm::mat4(1.0f), identityMatrix= glm::mat4(1.0f);
            glm::mat4 modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0, 4.7, 28.5 ));
            glm::mat4  scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(1.0, 1, .1));
            cube5.drawCubeWithTexture(lightingShaderWithTexture, alTogether * modeltranslate * scale);


            modelMatrixForContainer2 = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0 ,5.7, 28.5 ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(1.0, 0.1, 1.0));
            cube5.drawCubeWithTexture(lightingShaderWithTexture, alTogether * modeltranslate * scale);

            modelMatrixForContainer2 = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(-14.0 , 4.7, 28.6 ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.1, 1, 1.0));
            cube5.drawCubeWithTexture(lightingShaderWithTexture, alTogether * modeltranslate * scale);

            modelMatrixForContainer2 = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0 , 4.7, 29.5 ));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(1.0, 1, .1));
            cube5.drawCubeWithTexture(lightingShaderWithTexture, alTogether * modeltranslate * scale);

            modelMatrixForContainer2 = glm::mat4(1.0f);
            modeltranslate = glm::translate(identityMatrix, glm::vec3(-15.0, 4.7, 28.6));
            scale = glm::mat4(1.0f);
            scale = glm::scale(identityMatrix, glm::vec3(0.1, 1, 1.0));
            cube5.drawCubeWithTexture(lightingShaderWithTexture, alTogether * modeltranslate * scale);



}



void drawAludoor(Shader& lightingShader, glm::mat4 alTogether, Cube &cube, Cube& cube2)
{
    
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 modeltranslate = glm::translate(identityMatrix, glm::vec3(-10-5, 0.0, 45.0 - 9.0));
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(.2, 0.1, -2.0));
    cube.drawCubeWithTexture(lightingShader, alTogether * modeltranslate * scale);


    
    modeltranslate = glm::mat4(1.0f);
    modeltranslate = glm::translate(identityMatrix, glm::vec3(-9.95-5, -.9, 45.0 - 9.0));
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(.1, .9, -2.0));
    cube.drawCubeWithTexture(lightingShader, alTogether * modeltranslate * scale);

    modeltranslate = glm::mat4(1.0f);
    modeltranslate = glm::translate(identityMatrix, glm::vec3(-9.95-5, 0.1, 45.0 - 9.0));
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(.1, 2.1, -0.1));
    cube.drawCubeWithTexture(lightingShader, alTogether * modeltranslate * scale);

    modeltranslate = glm::mat4(1.0f);
    modeltranslate = glm::translate(identityMatrix, glm::vec3(-9.95-5, 0.1, 45.0 - 10.9));
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(.1, 2.1, -0.1));
    cube.drawCubeWithTexture(lightingShader, alTogether * modeltranslate * scale);

    modeltranslate = glm::mat4(1.0f);
    modeltranslate = glm::translate(identityMatrix, glm::vec3(-9.95-5, 0.1, 45.0 - 9.1));
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(.1, 2.1, -1.8));
    cube2.drawCubeWithTexture(lightingShader, alTogether * modeltranslate * scale);

    
    modeltranslate = glm::translate(identityMatrix, glm::vec3(-10-5, 2.2, 45.0 - 9.0));
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(.2, 0.1, -2.0));
    cube.drawCubeWithTexture(lightingShader, alTogether * modeltranslate * scale);


}


void ticket_counter(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{

}
void boundary(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    for (int i = 0; i < 7; i++)
    {
        glm::mat4  translateP = glm::mat4(1.0f);
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4  scaleP = glm::mat4(1.0f);

        scaleP = glm::scale(identityMatrix, glm::vec3(.1, .07, -0.1));
        translateP = glm::translate(identityMatrix, glm::vec3(8.0, -0.7, 44.7-i*0.3));


        Cylinder c = Cylinder(0.65f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);
        c.drawSphere(lightingShader, alTogether * translateP * scaleP);

        
        Sphere c1 = Sphere(0.1f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);

        glm::mat4 translate = glm::mat4(1.0f);
        
        translate = glm::translate(identityMatrix, glm::vec3(8.0, 0.72, 44.7 - i * 0.3));
        c1.drawSphere(lightingShader, alTogether * translate);

    }

    for (int i = 0; i < 7; i++)
    {
        glm::mat4  translateP = glm::mat4(1.0f);
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4  scaleP = glm::mat4(1.0f);

        scaleP = glm::scale(identityMatrix, glm::vec3(.1, .07, -0.1));
        translateP = glm::translate(identityMatrix, glm::vec3(6.0, -0.7, 44.7 - i * 0.3));


        Cylinder c = Cylinder(0.65f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);
        c.drawSphere(lightingShader, alTogether * translateP * scaleP);


        Sphere c1 = Sphere(0.1f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);

        glm::mat4 translate = glm::mat4(1.0f);

        translate = glm::translate(identityMatrix, glm::vec3(6.0, 0.72, 44.7 - i * 0.3));
        c1.drawSphere(lightingShader, alTogether * translate);

    }


    for (int i = 0; i < 7; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);

        scale = glm::scale(identityMatrix, glm::vec3(2.0, .05, -0.1));
        translate = glm::translate(identityMatrix, glm::vec3(6.0, 0.5+i*.3, 45.1));
        model = alTogether * translate * scale;
        drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);
    }

    for (int i = 0; i < 2; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);

        scale = glm::scale(identityMatrix, glm::vec3(.1, 2.0, -0.1));
        translate = glm::translate(identityMatrix, glm::vec3(6.5+i, 0.5, 45.1));
        model = alTogether * translate * scale;
        drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);
    }

    



    
   


   /* glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 modelCube = glm::mat4(1.0f);
    glm::mat4 translateCube = glm::mat4(1.0f);
    glm::mat4 scaleCube = glm::mat4(1.0f);
    translateCube = glm::translate(identityMatrix, glm::vec3(-13.5, 1.5, 25.0));
    scaleCube = glm::scale(identityMatrix, glm::vec3(3.0, -2.2, -0.1));;
    modelCube = translateCube * scaleCube;
    drawCube(cubeVAO, lightingShader, alTogether * modelCube, (float)3 / 255, (float)127 / 255, (float)243 / 255);*/

    

}



void drawdoor(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    
    scale = glm::scale(model, glm::vec3(-0.1, 2.7, 0.1));
    translate = glm::translate(identityMatrix, glm::vec3(-8.4, -0.7, 25.0));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);

    

    glm::mat4 mrotateYMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(0.44, .1, -0.01));
    translate = glm::translate(identityMatrix, glm::vec3(-8.45, 0.0, 25.05));
    model = alTogether * translate* mrotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);


    mrotateYMatrix = glm::mat4(1.0f);    
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(0.44, .1, -0.01));
    translate = glm::translate(identityMatrix, glm::vec3(-8.15, 0.05, 25.05));
    mrotateYMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translate * mrotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);



    mrotateYMatrix = glm::mat4(1.0f);
    mrotateYMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(0.44, .1, -0.01));
    translate = glm::translate(identityMatrix, glm::vec3(-8.45, 1.0, 25.05));
    model = alTogether * translate * mrotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);


    mrotateYMatrix = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(0.44, .1, -0.01));
    translate = glm::translate(identityMatrix, glm::vec3(-8.15, 1.1, 25.05));
    mrotateYMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f - 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translate * mrotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);


    mrotateYMatrix = glm::mat4(1.0f);
    mrotateYMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(0.44, .1, -0.01));
    translate = glm::translate(identityMatrix, glm::vec3(-8.45, 2.0, 25.05));
    model = alTogether * translate * mrotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);


    mrotateYMatrix = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(identityMatrix, glm::vec3(0.44, .1, -0.01));
    translate = glm::translate(identityMatrix, glm::vec3(-8.15, 2.1, 25.05));
    mrotateYMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f - 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translate * mrotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)213 / 255, (float)46 / 255);



    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.75, 2.5, 0.0));
    translate = glm::translate(model, glm::vec3(2.85, -.4, .4));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);*/

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
    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 2.1, .2));
    scale = glm::scale(model, glm::vec3(4.7, .3, 2.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);*/


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

    scale = glm::scale(model, glm::vec3(4.7, -1.0, -63.2));
    translate = glm::translate(model, glm::vec3(4.7, -.4, 15.0));
    model = alTogether * translate *scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);

    for (int i = 0; i < 5; i++)
    {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);

        scale = glm::scale(model, glm::vec3(1.0, .3, -1.0));
        translate = glm::translate(model, glm::vec3(7.25, -.4, -2.0-(9.2*i)));
        model = alTogether * translate * scale;
        //drawCube(cubeVAO, lightingShader, model, (float)178 / 255, (float)190 / 255, (float)181 / 255);
        Cylinder c = Cylinder(1.0f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255),glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178*0.5 / 255 , (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f) ;
        c.drawSphere(lightingShader, model);
    }

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(4.7, -1.0, -63.2));
    translate = glm::translate(model, glm::vec3(4.7, -.4+5.0+1, 15.0));
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
    semiWheel wheel1 = semiWheel(1.0f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);;
    glm::mat4 temp = glm::mat4(1.0f), identityMatrix = glm::mat4(1.0f);
    glm::mat4 r1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 r2 = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    temp = alTogether * glm::translate(identityMatrix, glm::vec3(2.2, 2.1, 5.0)) * glm::scale(identityMatrix, glm::vec3(1.2, .3, 0.814)) * r2 * r1;
    wheel1.drawsemiWheel(lightingShader, temp);


    semiCircle wheel3 = semiCircle(0.0f, 36, 18, glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 / 255, (float)190 / 255, (float)181 / 255), glm::vec3((float)178 * 0.5 / 255, (float)190 * 0.5 / 255, (float)181 * 0.5 / 255), 32.0f);;
    temp = glm::mat4(1.0f);
    r1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    r2 = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    temp = alTogether * glm::translate(identityMatrix, glm::vec3(2.2, 2.1, 5.0)) * glm::scale(identityMatrix, glm::vec3(1.2, .3, 0.81)) * r2 * r1;
    wheel3.drawsemiCircle(lightingShader, temp);

    temp = glm::mat4(1.0f);
    r1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    r2 = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    temp = alTogether * glm::translate(identityMatrix, glm::vec3(2.2, 2.1, -24.3)) * glm::scale(identityMatrix, glm::vec3(1.2*2, .3*2, 0.81)) * r2 * r1;
    wheel3.drawsemiCircle(lightingShader, temp);

    //curvy ash upper
  /*  model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate = glm::translate(model, glm::vec3(-.1, 2.1, .2));
    scale = glm::scale(model, glm::vec3(4.7, .3, -24.2));
    model = alTogether * translate * scale;
    drawCube(cubeVAO, lightingShader, model, (float)255 / 255, (float)255 / 255, (float)255 / 255);*/

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
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
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
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RGB;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}