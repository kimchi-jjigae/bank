#include "bank.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>

Bank::Bank() :
    mRenderer(fea::Viewport({800, 600}, {0, 0}, fea::Camera({400.0f, 300.0f}))),
    mWindow(new fea::SDL2WindowBackend()),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mMainState(mBus, mRenderer)
{
    mBus.addSubscriber<QuitMessage>(*this);
}

Bank::~Bank()
{
    mBus.removeSubscriber<QuitMessage>(*this);
}

void Bank::handleMessage(const QuitMessage& message)
{
    quit();
}

void Bank::render()
{
    mRenderer.clear(fea::Color::Red);
}

void Bank::setup(const std::vector<std::string>& args)
{
    mWindow.create(fea::VideoMode(800, 600), "Bank");
    mRenderer.setup();
    mWindow.setFramerateLimit(60);
}

void Bank::destroy()
{
    mWindow.close();
}

void Bank::loop()
{
    mInputHandler.process();
    mWindow.swapBuffers();
    //mAudioPlayer.update();

    render();
}
