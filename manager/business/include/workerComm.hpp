#ifndef EOS_BUSINESS_WORKERCOMM_HPP
#define EOS_BUSINESS_WORKERCOMM_HPP

#include <iostream>
#include <dispatcher/task.hpp>

namespace eos{
    namespace business{
        class workerComm{
            public:
                workerComm();
                ~workerComm();

                void start(dispatcher::TaskContext& ctx);
                void stop(dispatcher::TaskContext& ctx);
            private:

        }; 
    };
}

#endif