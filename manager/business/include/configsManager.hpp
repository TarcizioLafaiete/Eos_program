#ifndef EOS_BUSINESS_CONFIGS_MANAGER_HPP
#define EOS_BUSINESS_CONFIGS_MANAGER_HPP

#include <nlohmann/json.hpp>
#include <iostream>

namespace eos {
    namespace business {
        class ConfigsManager {
        public:
            ConfigsManager();
            ~ConfigsManager() = default;

            nlohmann::json loadConfigs();
            void saveConfigs(const nlohmann::json& configs);

        private:
            std::string configFile;

            void createDefaultConfig();
        };
    }
}

#endif