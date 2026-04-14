#include <controller.hpp>

eos::control::controller::controller(std::shared_ptr<eos::business::signalManager> sigManager){
    this->manager = sigManager;
    this->workerComm.reset(new eos::business::workerComm());

    this->connect();

}

eos::control::controller::~controller(){}

void eos::control::controller::connect(){

    this->manager->connect(eos::business::signalRegister::START,[this](dispatcher::TaskContext& ctx){
        this->workerComm->start(ctx);
    });

    this->manager->connect(eos::business::signalRegister::STOP,[this](dispatcher::TaskContext& ctx){
        this->workerComm->stop(ctx);
    });

}