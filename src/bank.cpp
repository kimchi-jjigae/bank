#include "bank.hpp"
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>

Bank::Bank() :
    mRenderer(fea::Viewport({1024, 768}, {0, 0}, fea::Camera({512.0f, 384.0f}))),
    mWindow(new fea::SDL2WindowBackend()),
    mFeaInputHandler(new fea::SDL2InputBackend()),
    mInputHandler(mBus, mFeaInputHandler),
    mMainState(mBus, mRenderer),
    mAudioPlayer(mBus)
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

void Bank::setup(const std::vector<std::string>& args)
{
    mWindow.create(fea::VideoMode(1024, 768), "Bank");
    mMainState.setupGraphics();
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
    mAudioPlayer.update();

    mMainState.update();
    mWindow.swapBuffers();
}
