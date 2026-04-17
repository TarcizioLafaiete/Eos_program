#include <configsManager.hpp>
#include <filesystem>
#include <fstream>


eos::business::ConfigsManager::ConfigsManager(){

    std::string configDir = PROJECT_ROOT + std::string("/configs");

    if(!std::filesystem::exists(configDir)) {
        std::filesystem::create_directory(configDir);
    }

    this->configFile = PROJECT_ROOT + std::string("/configs/config.json");

    if(!std::filesystem::exists(this->configFile)){
        createDefaultConfig();
    }

}

void eos::business::ConfigsManager::createDefaultConfig(){
    nlohmann::json defaultConfig;
    defaultConfig["version"] = "1.0";
    defaultConfig["time"] = 10;
    defaultConfig["time_unit"] = "min";
    defaultConfig["ui_system"] = "Gnome";
    defaultConfig["random_display"] = false;
    defaultConfig["carousel_list"] = nlohmann::json::array();
    defaultConfig["carousel_list"].push_back("default");
    defaultConfig["default"] = nlohmann::json::array();
    defaultConfig["current_carousel"] = "default";

    this->saveConfigs(defaultConfig);
}

nlohmann::json eos::business::ConfigsManager::loadConfigs(){
    std::ifstream file(this->configFile);
    nlohmann::json configs;
    file >> configs;
    return configs;
}


void eos::business::ConfigsManager::saveConfigs(const nlohmann::json& configs){

    std::ofstream file(this->configFile);
    file << configs.dump(4);
    file.close();

}