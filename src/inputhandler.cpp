#include "inputhandler.hpp"
#include "messages.hpp"

InputHandler::InputHandler(fea::MessageBus& bus, fea::InputHandler& handler)    :
    mHandler(handler),
    mBus(bus)
{
}

void InputHandler::process()
{
    fea::Event event;
    while(mHandler.pollEvent(event))
    {
        if(event.type == fea::Event::KEYPRESSED)
        {
            if(event.key.code == fea::Keyboard::ESCAPE)
                mBus.send(QuitMessage());
            else if(event.key.code == fea::Keyboard:: O)
                mBus.send(StartMinigameMessage{"outdoors"});
            else if(event.key.code == fea::Keyboard:: C)
                mBus.send(StartMinigameMessage{"crossword"});
            else if(event.key.code == fea::Keyboard:: S)
                mBus.send(StartMinigameMessage{"sudoku"});
            else if(event.key.code == fea::Keyboard:: H)
                mBus.send(StartMinigameMessage{"childquestion"});
            else if(event.key.code == fea::Keyboard:: E)
                mBus.send(StartMinigameMessage{"heartattack"});
            else if(event.key.code == fea::Keyboard:: W)
                mBus.send(StartMinigameMessage{"whiteboard"});
            else if(event.key.code == fea::Keyboard:: P)
                mBus.send(StartMinigameMessage{"painting"});
        }
        else if(event.type == fea::Event::CLOSED)
        {
            mBus.send(QuitMessage());
        }
        else if(event.type == fea::Event::RESIZED)
        {
            mBus.send(ResizeMessage{{event.size.width, event.size.height}});
        }
        else if(event.type == fea::Event::MOUSEBUTTONPRESSED)
        {
            mBus.send(MouseClickMessage{{event.mouseButton.x, event.mouseButton.y}});
        }
        else if(event.type == fea::Event::MOUSEBUTTONRELEASED)
        {
            mBus.send(MouseReleaseMessage{{event.mouseButton.x, event.mouseButton.y}});
        }
        else if(event.type == fea::Event::MOUSEMOVED)
        {
            mBus.send(MouseMoveMessage{{event.mouseMove.x, event.mouseMove.y}});
        }
    }
}
