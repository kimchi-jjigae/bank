#include <fea/structure.hpp>
#include <fea/render2d.hpp>
#include <fea/util.hpp>
#include <fea/userinterface.hpp>
#include "inputhandler.hpp"
#include "messages.hpp"
#include "mainstate.hpp"

class Bank : public fea::Application,
    public fea::MessageReceiver<QuitMessage>
{
    public:
        Bank();
        ~Bank();
        void handleMessage(const QuitMessage& message) override;
        void render();
    protected:
        virtual void setup(const std::vector<std::string>& args) override;
        virtual void destroy() override; 
        virtual void loop() override;
    private:
        fea::MessageBus mBus;
        fea::Renderer2D mRenderer;
        fea::Window mWindow;
        fea::InputHandler mFeaInputHandler;

        InputHandler mInputHandler;
        MainState mMainState;
};
