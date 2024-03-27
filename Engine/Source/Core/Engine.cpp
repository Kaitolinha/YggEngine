#include "Engine.hpp"

#include "../Tree/Roots/Root.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

namespace ygg
{
namespace detail
{

struct Engine::Implementation
{
    Implementation() YGG_EXCEPT
        : window{nullptr}
        , context{nullptr}
        , event{}
    {
        // Initialize SDL.
        Assert(SDL_Init(SDL_INIT_EVERYTHING) == 0, "SDL initialization failed: " + std::string(SDL_GetError()));

        // Initialize SDL_image.
        Assert(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG, "SDL_image initialization failed: " + std::string(IMG_GetError()));

        // OpenGl initialize configuration.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Create an SDL window.
        this->window = SDL_CreateWindow(ENGINE_WINDOW_NAME,
                                        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                        ENGINE_INITIAL_WINDOW_WIDTH, ENGINE_INITIAL_WINDOW_HEIGHT,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        Assert(this->window, "Window creation failed: " + std::string(SDL_GetError()));

        // Create an OpenGL implementation.
        this->context = SDL_GL_CreateContext(this->window);
        Assert(this->context, "OpenGL implementation creation failed: " + std::string(SDL_GetError()));

        // Initialize GLEW.
        GLenum glewError{glewInit()};
        Assert(glewError == GLEW_OK, "GLEW initialization failed: " + std::string((const char*)glewGetErrorString(glewError)));
    }

    ~Implementation() YGG_NOEXCEPT
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

Engine::Engine() YGG_EXCEPT
    : implementation{nullptr}
    , isRunning{false}
{
    this->implementation = new Implementation;
    Print("Engine initialized!");
}

Engine::~Engine() YGG_NOEXCEPT
{
    delete this->implementation;
    Print("Engine was stopped.");
}

auto Engine::Run() YGG_EXCEPT -> void
{
    Print("Engine is running...");

    Root root;

    this->isRunning = true;
    while (this->isRunning)
    {
        while (SDL_PollEvent(&this->implementation->event))
        {
            root.Flow(Root::FLOW_INPUT);
            if (this->implementation->event.type == SDL_QUIT) { this->isRunning = false; }
        }

        root.Flow(Root::FLOW_FEED);
        root.Flow(Root::FLOW_FIXED_FEED);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render here...
        root.Flow(Root::FLOW_VIEW);

        SDL_GL_SwapWindow(this->implementation->window);

        root.Flow(Root::FLOW_REFRESH);
    }
}

} // namespace detail
} // namespace ygg