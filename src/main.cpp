#include <iostream>
#include <stdlib.h>
#include <vector>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>



void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processClose(GLFWwindow *window);
void drawTriangle();
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
    /*
        The window handle is passed to all window related functions and is provided 
        to along with all input events, so event handlers can tell which window received the event.
    */
    // ------------------------
    GLFWwindow *window = glfwCreateWindow(SCRN_WIDTH, SCRN_HEIGHT, "Call", NULL, NULL);

    if(NULL == window){
        std::cout << "Window creation failed.\n" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }   

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers

    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // moment a user resizes the window the viewport should be adjusted as well
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    

    // render loop
    while(!glfwWindowShouldClose(window)){
        // input
        processClose(window);

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

void processClose(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void drawTriangle(){
    float triangleVertecies[] = {
         0.5f,  0.5f, 0.0f, // top right
         0.5f, -0.5f, 0.0f, // bottom right
        -0.0f,  0.5f, 0.0f  // top left


    }

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertecies), GL_STATIC_DRAW);

    // unsigned int vertexShader;
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);

    
}
