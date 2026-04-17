#include <iostream>
#include <memory>

#include <signalManager.hpp>
#include <signalRegister.hpp>
#include <workerComm.hpp>
#include <configsManager.hpp>

namespace eos{
    namespace control{
        class controller{
            public:
                controller(std::shared_ptr<eos::business::signalManager> sigManager);
                ~controller();
                
            private:
                void connect();
                void refreshConfigs(dispatcher::TaskContext& ctx);

                std::unique_ptr<eos::business::workerComm> workerComm;
                std::shared_ptr<eos::business::signalManager> manager;

                eos::business::ConfigsManager config;
                nlohmann::json currentConfig;


        };
    };
}