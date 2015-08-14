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

void Bank::setup(const std::vector<std::string>& args)
{
    mWindow.create(fea::VideoMode(800, 600), "Bank");
    mRenderer.setup();
    mWindow.setFramerateLimit(60);
//
//    mStateMachine.addGameState("ingame", std::unique_ptr<InGameState>(new InGameState(mBus, mRenderer)));
//    mStateMachine.addGameState("menu", std::unique_ptr<MenuState>(new MenuState(mBus, mRenderer)));
//    mStateMachine.setCurrentState("menu");
}

void Bank::destroy()
{
    mWindow.close();
}

void Bank::loop()
{
    mInputHandler.process();
    //mStateMachine.run();
    mWindow.swapBuffers();
    //mAudioPlayer.update();

    //if(mStateMachine.isFinished())
        //quit();
}
