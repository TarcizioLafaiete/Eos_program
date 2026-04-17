#include <mainWidget.hpp>
#include <signalManager.hpp>
#include <controller.hpp>


int main(){

    auto sigManager = std::make_shared<eos::business::signalManager>(1,20);


    eos::view::mainWidget widgetApp(sigManager);
    eos::control::controller controlApp(sigManager);
    
    nana::exec();

    return 0;
}