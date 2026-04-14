#include <iostream>
#include <memory>

#include <signalManager.hpp>
#include <signalRegister.hpp>
#include <workerComm.hpp>

namespace eos{
    namespace control{
        class controller{
            public:
                controller(std::shared_ptr<eos::business::signalManager> sigManager);
                ~controller();
                
            private:
                void connect();

                std::unique_ptr<eos::business::workerComm> workerComm;
                std::shared_ptr<eos::business::signalManager> manager;

        };
    };
}