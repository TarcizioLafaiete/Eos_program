#include <signalManager.hpp>

eos::business::signalManager::signalManager(int numWorkers,int hashMapSize){

    this->dispatcher.reset(new dispatcher::AsyncDispatcher(hashMapSize,numWorkers));

}

eos::business::signalManager::~signalManager(){}

void eos::business::signalManager::connect(signalRegister reg, std::function<void(dispatcher::TaskContext&)> func){

    dispatcher::TaskContext ctx;
    ctx.set(NULL);
    
    auto sig = std::make_unique<dispatcher::signal>(ctx);
    dispatcher::signal* rawSig = sig.get();


    this->registerMap.emplace(reg,std::move(sig));
    this->dispatcher->connect(*rawSig,func);

}

void eos::business::signalManager::emit(signalRegister reg,dispatcher::TaskContext ctx){
    auto it = this->registerMap.find(reg);
    if(it != this->registerMap.end()){
        it->second->context = ctx;
        this->dispatcher->emit(*(it->second));
    }
}