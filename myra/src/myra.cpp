#include "myra.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>

Myra::Myra() :
    mWindow(new fea::SDL2WindowBackend()),
    mInputHandler(new fea::SDL2InputBackend()),
    mRenderer(fea::Viewport({1024, 768}, {0, 0}, fea::Camera({1024 / 2.0f, 768 / 2.0f})))
{
}

void Myra::setup(const std::vector<std::string>& args)
{
    (void)args;
    mWindow.create(fea::VideoMode(1024, 768), "Myra");
    mWindow.setVSyncEnabled(true);
    mRenderer.setup();
    mWindow.setFramerateLimit(60);
}

void Myra::destroy()
{
    mWindow.close();
}

void Myra::loop()
{
    handleInput();

    //update code

    mWindow.swapBuffers();
}

void Myra::handleInput()
{
    fea::Event event;
    while(mInputHandler.pollEvent(event))
    {
        if(event.type == fea::Event::KEYPRESSED)
        {
            if(event.key.code == fea::Keyboard::ESCAPE)
                quit();
        }
        else if(event.type == fea::Event::CLOSED)
        {
            quit();
        }
        else if(event.type == fea::Event::RESIZED)
        {
            mRenderer.setViewport(fea::Viewport({event.size.width, event.size.height}, {0, 0}, fea::Camera({event.size.width / 2.0f, event.size.height / 2.0f})));
        }
        else if(event.type == fea::Event::MOUSEBUTTONPRESSED)
        {
            //
        }
        else if(event.type == fea::Event::MOUSEBUTTONRELEASED)
        {
            //
        }
        else if(event.type == fea::Event::MOUSEMOVED)
        {
            //
        }
    }
}
