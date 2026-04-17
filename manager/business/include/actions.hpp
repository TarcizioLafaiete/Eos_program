#ifndef EOS_BUSINESS_ACTIONS_HPP
#define EOS_BUSINESS_ACTIONS_HPP

#include <iostream>

namespace eos{
    namespace business{
        namespace actions{

            struct emptyAction{
                bool useless;
            };

            struct eosConfig{
                int time;
                std::string timeUnit;
                std::string uiSystem;
                bool randomDisplay;
                std::string currentCarousel;
            };

        };
    };
}

#endif