#include <workerComm.hpp>
#include <actions.hpp>

eos::business::workerComm::workerComm(){};

eos::business::workerComm::~workerComm(){};

void eos::business::workerComm::start(dispatcher::TaskContext& ctx){
    
    auto st = ctx.get<actions::eosConfig>();

    std::cout<<"Sexo grupal"<<std::endl;

}

void eos::business::workerComm::stop(dispatcher::TaskContext& ctx){
    auto st = ctx.get<actions::emptyAction>();

    std::cout<<"Parando workerComm"<<std::endl;
}