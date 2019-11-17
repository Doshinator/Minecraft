#include <iostream>
#include <stdlib.h>
#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void drawTriangle();
void createVertexData();
unsigned int createVertexShader();
unsigned int createFragmentShader();
unsigned int createShaderProgram();

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


const unsigned int SCRN_WIDTH = 800, SCRN_HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main(){

    // GL Init
    // ------------------------
    glfwInit();

    // GL Config
    // ------------------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    #endif
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );



    // GLFW window creation
    // ------------------------
    GLFWwindow *window = glfwCreateWindow(SCRN_WIDTH, SCRN_HEIGHT, "Call", NULL, NULL);

    if(NULL == window){
        std::cout << "Window creation failed.\n" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }   

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // Glew Init 
    // ------------------------
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
   
    // 5) use the program
    glUseProgram(createShaderProgram());
    // 6)
    // someFunctionThatDrawsTheObjet();

    // main game loop
    // ------------------------
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
       

        // When the entire frame has been rendered, it is time to swap the back 
        // and the front buffers in order to display what has been rendered and 
        // begin rendering a new frame. This is done with glfwSwapBuffers.
        glfwSwapBuffers(window);   

        glfwPollEvents();
    }



    glfwTerminate();

    return EXIT_SUCCESS;
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    // size of the window that you want to render in
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}



// Graphics pipeline
// ------------------------

// 1) vertex data
void createVertexData(){
    float triangleVertecies[] = {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.0f,  0.5f, 0.0f  // top left
    };
    // 1.1) Create Vertex data -> Generate Vertex array -> Generate Buffer -> Bind Vetex Array -> Bind Buffer -> buffer data

    unsigned int VBO;
    glGenVertexArrays(1, &VBO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertecies), triangleVertecies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
}

// 2) creating vertex shader
unsigned int createVertexShader(){
    // 2.1 line 17 - writing GLSL language for a vertex shader in a form of a const char in C.
    // 2.2 create vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // 2.3 attatch vertex shader source code(GLSL code) to vertex shader object 
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);  

    // 2.4 checking if glCompileShader succeeded
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return vertexShader;
}

// 3) creating fragment shader 
unsigned int createFragmentShader(){
    // 2.1 line 24 - writing GLSL language for a fragment shader in a form of a const char in C.

    // 2.2 create fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // 2.3 attach fragment shader source code(GLSL code) to fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // 2.4 checking if glCompileShader succeeded
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return fragmentShader;
}

// 4) create shader program
unsigned int createShaderProgram(){
    int vertexShader = createVertexShader();
    int fragmentShader = createFragmentShader();
    // 4.1 create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    // 4.2 link vertex & fragment shader
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 4.3 check if shader was linked
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //4.4 delete vertex + fragment Shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}