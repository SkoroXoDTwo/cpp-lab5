#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "GLDemoWindow.h"

int main(int, char **) {
    SDL_Init(SDL_INIT_EVERYTHING);

    try {
        GLDemoWindow w;

        w.main_loop();

    } catch (const std::exception &e) {
        std::cerr << "Runtime error: "
                  << std::endl
                  << e.what()
                  << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unexpected runtime error: "
                  << std::endl;
        return 1;
    }

    return 0;
}








