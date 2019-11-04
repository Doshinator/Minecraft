#include "display.h"
#include <memory>
#include <SFML/Graphics.hpp>

namespace Display{

    std::unique_ptr<sf::RenderWindow> window;

    void init(){
        sf::ContextSettings settings;
        settings.depthBits = 24;
        settings.majorVersion = 3;
        settings.minorVersion = 3;

    }

    void close(){


    }

}