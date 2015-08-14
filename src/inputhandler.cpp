#include "inputhandler.hpp"
#include "messages.hpp"

InputHandler::InputHandler(fea::MessageBus& bus, fea::InputHandler& handler)    :
    mBus(bus),
    mHandler(handler)
{
}

void InputHandler::process()
{
    fea::Event event;
    while(mHandler.pollEvent(event))
    {
        if(event.type == fea::Event::KEYPRESSED)
        {
            if(event.key.code == fea::Keyboard::Q)
                mBus.send(QuitMessage());
        }
        else if(event.type == fea::Event::CLOSED)
        {
            mBus.send(QuitMessage());
        }
        else if(event.type == fea::Event::RESIZED)
        {
            mBus.send(ResizeMessage{{event.size.width, event.size.height}});
        }
    }
}
