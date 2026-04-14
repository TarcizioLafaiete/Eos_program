#include "../include/mainWidget.hpp"
#include <nana/paint/image.hpp>
#include <filesystem>
#include <iostream>
#include <dispatcher/DispatcherProvider.hpp>
#include <actions.hpp>



using namespace nana;
namespace fs = std::filesystem;

eos::view::mainWidget::mainWidget(std::shared_ptr<eos::business::signalManager> sigManager)
:fm{API::make_center(800,600)}{

    this->manager = sigManager;

    fm.caption("Main Window");

    this->makeLayout();
    API::show_window(this->add_view_image_btn,false);
    

    this->connect();
    // exec();
    

}

eos::view::mainWidget::~mainWidget(){}


void eos::view::mainWidget::makeLayout(){


    std::string resources = PROJECT_ROOT + std::string("/build/manager/control/resources");
    

    auto fm_size = fm.size();

    paint::image icon;

    if(!icon.open(resources + "/wallman_icon.ico"))
    {
        std::cerr << "Erro ao carregar ícone\n";
    }
    API::window_icon(fm,icon);

    //========= HEADER =========
    this->header_title.create(fm);
    this->header_title.caption("EOS Program");
    header_title.format(true);
    header_title.move(10,10);
    header_title.size(nana::size(200,30));

    //====== GROUP 1: CONFIG ====
    this->config.create(fm);
    this->config.caption("Configurations");
    config.move(rectangle(10,40,fm_size.width - 20,120));

    label space_group1{config,""};
    this->time_lbl.create(config);
    this->time_lbl.caption("Time: ");
    time_input.create(config);
    this->time_unit.create(config);
    this->time_unit.push_back("sec");
    this->time_unit.push_back("min");
    this->time_unit.push_back("hour");
    this->time_unit.push_back("day");

    this->ui_lbl.create(config);
    this->ui_lbl.caption("UI System: ");
    this->ui_combo.create(config);
    this->ui_combo.push_back("Gnome");
    this->ui_combo.push_back("KDE");

    this->random_chk.create(config);
    this->random_chk.caption("Randomize display images");
    this->carousel.create(config);
    this->carousel.push_back("standard carousel");

    //======== GROUP 2: IMAGE HANDLER ====
    this->wall.create(fm);
    this->wall.caption("Wallpaper Handler");
    label space_group2{wall,""};
    wall.move(rectangle(10,180,fm_size.width/2,300));

    this->add_lbl.create(wall);
    this->add_lbl.caption("Add new Images to carousel");
    this->add_image_btn.create(wall);
    this->add_image_btn.caption("");
    this->drawImageInButton(this->add_image_btn, resources + "/adicionar_imagem.ico");
    this->add_folder_btn.create(wall);
    this->add_folder_btn.caption("");
    this->drawImageInButton(this->add_folder_btn, resources + "/adicionar_pasta.ico");

    this->remove_lbl.create(wall);
    this->remove_lbl.caption("Remove images to carousel");
    this->remove_image_btn.create(wall);
    this->remove_image_btn.caption("");
    this->drawImageInButton(this->remove_image_btn,resources + "/remover_imagem.ico");

    this->show_lbl.create(wall);
    this->show_lbl.caption("Show Image on Display");
    this->view_image_btn.create(wall);
    this->view_image_btn.caption("");
    this->drawImageInButton(this->view_image_btn,resources + "/adicionar_imagem.ico");

    this->create_lbl.create(wall);
    this->create_lbl.caption("Create a new carousel");
    this->create_carousel_btn.create(wall);
    this->create_carousel_btn.caption("");
    this->drawImageInButton(this->create_carousel_btn,resources + "/add.ico");
    this->remove_carousel_btn.create(wall);
    this->remove_carousel_btn.caption("");
    this->drawImageInButton(this->remove_carousel_btn,resources + "/minus.ico");

    // ===== LAYOUT CONFIG =====
    place plc_config{config};


    // Depois no place usar arrange com valores iguais
    plc_config.div(R"(
        margin=[20,10,10,10] gap=15
        <vert
            <line1 height=20 arrange=[10%,26%,16%,16%,16%,16%]>
            <line2 height = 35>
            <line3 height=20 arrange=[30%,40%,30%]>
        >
    )");

    plc_config["line1"] << time_lbl << this->time_input << this->time_unit << space_group1
                        << ui_lbl << this->ui_combo;

    plc_config["line3"] << this->random_chk << space_group1 << this->carousel;

    // ===== LAYOUT WALL =====
    place plc_wall{wall};

    plc_wall.div(R"(
    margin=10 gap=35
    <vert
        <ls1 height=30>
        <l1 height=40 arrange=[60%,5%,15%,5%,15%]>
        <ls2 height=30>
        <l2 height=40 arrange=[60%,5%,15%,20%]>
        <ls3 heigth=30>
        <l3 height=40 arrange=[60%,5%,15%,20%]>
        <ls4 height=30> 
        <l4 height=40 arrange=[60%,5%,15%,5%,15%]>
    >
    )");

    plc_wall["l1"] << add_lbl << space_group2 << add_image_btn << space_group2 << add_folder_btn;
    plc_wall["l2"] << remove_lbl << space_group2 << this->remove_image_btn << space_group2;
    plc_wall["l3"] << show_lbl << space_group2 << this->view_image_btn << space_group2;
    plc_wall["l4"] << create_lbl << space_group2 <<this->create_carousel_btn << space_group2 << this->remove_carousel_btn ;

    // plc.collocate();
    plc_config.collocate();
    plc_wall.collocate();

    this->start_btn.create(fm);
    this->start_btn.caption("Start");
    this->start_btn.bgcolor(colors::green);
    this->start_btn.move(rectangle(fm_size.width*0.72,fm_size.height*0.88,90,30));

    this->stop_btn.create(fm);
    this->stop_btn.caption("Stop");
    this->stop_btn.bgcolor(colors::red);
    this->stop_btn.move(rectangle(fm_size.width*0.85,fm_size.height*0.88,90,30));

    this->save_config_btn.create(fm);
    this->save_config_btn.caption("Save Config");
    this->save_config_btn.bgcolor(colors::light_gray);
    this->save_config_btn.move(rectangle(fm_size.width*0.59,fm_size.height*0.88,90,30));

    this->add_view_image_btn.create(fm);
    this->add_view_image_btn.caption("Add Image");
    this->add_view_image_btn.bgcolor(colors::blue);
    this->add_view_image_btn.move(rectangle(fm_size.width*0.46,fm_size.height*0.88,90,30));


    fm.show();
    // exec();

}

void eos::view::mainWidget::drawImageInButton(button& button,std::string icon){

    paint::image img = paint::image(icon);
        if (!img.open(icon)) {
        std::cerr << "Erro ao carregar imagem\n";
        return;
    }
    drawing dw(button);
    dw.draw([img](paint::graphics& g) {
        // limpa fundo
        g.rectangle(true, colors::light_gray);

        auto size = g.size();
        auto img_size = img.size();

        int x = (size.width - img_size.width) / 2;
        int y = (size.height - img_size.height) / 2;

        img.paste(g, point(x, y));
    });

    dw.update();
}

void test(){
    int a = 20;
    int b = 30;
    std::cout<<a+b<<std::endl;
}

void eos::view::mainWidget::connect(){

    dispatcher::TaskContext starCtx;
    eos::business::actions::emptyAction start;
    starCtx.set(start);
    this->start_btn.events().click([this,starCtx]{
        this->manager->emit(eos::business::signalRegister::START,starCtx);
    });

    dispatcher::TaskContext stopCtx;
    eos::business::actions::emptyAction stop;
    stopCtx.set(stop);
    this->stop_btn.events().click([this,stopCtx]{
        this->manager->emit(eos::business::signalRegister::STOP,stopCtx);
    });

}