#include <iostream>
#include <stdlib.h>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

// The MAIN function, from here we start the application and run the game loop
int main( ){

//  This function initializes the GLFW library.  Before most GLFW functions can 
//  be used, GLFW must be initialized, and before an application terminates GLFW 
//  should be terminated in order to free any resources allocated during or after initialization.
    glfwInit();
    


    // GLFW window creation
    /*
        The window handle is passed to all window related functions and is provided 
        to along with all input events, so event handlers can tell which window received the event.
    */
    glfwGetVideoMode *mode = glfwGetVideoMode(monitor);

    GLFW *window = glfwCreateWindow(WIDTH, HEIGHT, "Call of Duty Modern Warfare", glfwGetPrimaryMonitor(), nullptr);

    // glfwCreateWindow could returns NULL, so check
    if(nullptr == window){
        glfwDestroyWindow(window);
        return EXIT_FAILURE;
    }



}