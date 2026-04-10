#include <mainWidget.hpp>
#include <dispatcher/DispatcherProvider.hpp>


int main(){

    dispatcher::DispatcherProvider::init(20,2);

    eos::view::mainWidget app;
    nana::exec();

    return 0;
}