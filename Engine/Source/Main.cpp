#include "Core/Engine.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

auto main(int argc, char** argv) -> int
{
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
        return 1;
    }

    // Initialize SDL_image.
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image initialization failed: " << IMG_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    // OpenGl initialize configuration.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Create an SDL window.
    SDL_Window* window = SDL_CreateWindow("Ygg Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    // Create an OpenGL context.
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context)
    {
        std::cerr << "OpenGL context creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize GLEW.
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(glewError) << '\n';
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop.
    bool quit{false};
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) { quit = true; }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Render here...
        SDL_GL_SwapWindow(window);
    }

    // Cleanup.
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

	return 0;
}