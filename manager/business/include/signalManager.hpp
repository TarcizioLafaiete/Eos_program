#ifndef EOS_BUSINESS_SIGNALMANAGER_HPP
#define EOS_BUSINESS_SIGNALMANAGER_HPP

#include <dispatcher/DispatcherProvider.hpp>
#include <unordered_map>
#include <memory>
#include "signalRegister.hpp"

namespace eos{
    namespace business{
        class signalManager{
            public:
                signalManager(int numWorkers,int hashMapSize);
                ~signalManager();
                void connect(signalRegister reg, std::function<void(dispatcher::TaskContext&)> func);
                void emit(signalRegister reg,dispatcher::TaskContext ctx);
            private:

                std::unordered_map<signalRegister,std::unique_ptr<dispatcher::signal>> registerMap;
                std::unique_ptr<dispatcher::AsyncDispatcher> dispatcher;
                

        };
    };
}

#endif