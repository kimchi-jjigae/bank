#include <fea/structure.hpp>
#include <fea/render2d.hpp>
#include <fea/util.hpp>
#include <fea/userinterface.hpp>
#include "inputhandler.hpp"
#include "messages.hpp"
#include "mainstate.hpp"
#include "audioplayer.hpp"

class Bank : public fea::Application,
    public fea::MessageReceiver<QuitMessage>
{
    public:
        Bank();
        ~Bank();
        void handleMessage(const QuitMessage& message) override;
    protected:
        virtual void setup(const std::vector<std::string>& args) override;
        virtual void destroy() override; 
        virtual void loop() override;
    private:
        fea::MessageBus mBus;
        fea::Window mWindow;
        fea::Renderer2D mRenderer;
        fea::InputHandler mFeaInputHandler;

        InputHandler mInputHandler;
        MainState mMainState;
        AudioPlayer mAudioPlayer;
};
