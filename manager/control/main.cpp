#include <mainWidget.hpp>
#include <signalManager.hpp>
#include <controller.hpp>


int main(){

    auto sigManager = std::make_shared<eos::business::signalManager>(1,20);


    eos::control::controller controlApp(sigManager);
    eos::view::mainWidget widgetApp(sigManager);
    nana::exec();

    return 0;
}