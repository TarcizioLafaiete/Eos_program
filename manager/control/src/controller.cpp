#include <controller.hpp>
#include <configsManager.hpp>
#include <actions.hpp>

eos::control::controller::controller(std::shared_ptr<eos::business::signalManager> sigManager){
    this->manager = sigManager;
    this->workerComm.reset(new eos::business::workerComm());

    this->config = eos::business::ConfigsManager();
    this->currentConfig = this->config.loadConfigs();

    this->connect();

}

eos::control::controller::~controller(){}

void eos::control::controller::connect(){

    this->manager->connect(eos::business::signalRegister::START,[this](dispatcher::TaskContext& ctx){
        this->refreshConfigs(ctx);
        this->workerComm->start(ctx);
    });

    this->manager->connect(eos::business::signalRegister::STOP,[this](dispatcher::TaskContext& ctx){
        this->workerComm->stop(ctx);
    });

    this->manager->connect(eos::business::signalRegister::SAVE_CONFIG,[this](dispatcher::TaskContext& ctx){
        this->refreshConfigs(ctx);
        this->config.saveConfigs(this->currentConfig);
    });


    nlohmann::json cConfig = this->config.loadConfigs();
    eos::business::actions::eosConfig eConfig;
    eConfig.time = cConfig["time"];
    eConfig.timeUnit = cConfig["time_unit"];
    eConfig.uiSystem = cConfig["ui_system"];
    eConfig.randomDisplay = cConfig["random_display"];
    eConfig.currentCarousel = cConfig["current_carousel"];
    dispatcher::TaskContext loadConfigCtx;
    loadConfigCtx.set(eConfig);
    this->manager->emit(eos::business::signalRegister::LOAD_CONFIG,loadConfigCtx);

}

void eos::control::controller::refreshConfigs(dispatcher::TaskContext& ctx){

    auto config = ctx.get<eos::business::actions::eosConfig>();
    this->currentConfig["time"] = config.time;
    this->currentConfig["time_unit"] = config.timeUnit;
    this->currentConfig["ui_system"] = config.uiSystem;
    this->currentConfig["random_display"] = config.randomDisplay;
    this->currentConfig["current_carousel"] = config.currentCarousel;

}