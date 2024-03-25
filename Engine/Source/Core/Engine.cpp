#include "Engine.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

struct Engine::Context
{
    Context()
        : window{nullptr}
        , context{nullptr}
        , event{}
    {
        // Initialize SDL.
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            throw std::runtime_error("SDL initialization failed: " + std::string(SDL_GetError()));
        }

        // Initialize SDL_image.
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        {
            throw std::runtime_error("SDL_image initialization failed: " + std::string(IMG_GetError()));
        }

        // OpenGl initialize configuration.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create an SDL window.
        this->window = SDL_CreateWindow(ENGINE_WINDOW_NAME,
                                        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                        ENGINE_INITIAL_WINDOW_WIDTH, ENGINE_INITIAL_WINDOW_HEIGHT,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if (!this->window)
        {
            throw std::runtime_error("Window creation failed: " + std::string(SDL_GetError()));
        }

        // Create an OpenGL context.
        this->context = SDL_GL_CreateContext(this->window);
        if (!this->context)
        {
            throw std::runtime_error("OpenGL context creation failed: " + std::string(SDL_GetError()));
        }

        // Initialize GLEW.
        GLenum glewError{glewInit()};
        if (glewError != GLEW_OK)
        {
            throw std::runtime_error("GLEW initialization failed: " + std::string((const char*)glewGetErrorString(glewError)));
        }
    }

    ~Context()
    {
        // Cleanup.
        SDL_GL_DeleteContext(this->context);
        SDL_DestroyWindow(this->window);
        IMG_Quit();
        SDL_Quit();
    }

    SDL_Window* window;
    SDL_GLContext context;
    SDL_Event event;
};

Engine::Engine()
    : context{nullptr}
    , isRunning{false}
{
    this->context = new Context;
    this->Log("Engine initialized!");
}

Engine::~Engine()
{
    delete this->context;
    this->Log("Engine was stopped.");
}

auto Engine::Run() -> void
{
    this->Log("Engine is running...");

    this->isRunning = true;
    while (this->isRunning)
    {
        while (SDL_PollEvent(&this->context->event))
        {
            if (this->context->event.type == SDL_QUIT) { this->isRunning = false; }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Render here...
        SDL_GL_SwapWindow(this->context->window);
    }
}