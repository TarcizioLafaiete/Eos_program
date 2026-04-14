#include <nana/gui.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/spinbox.hpp>

#include <memory>

#include <signalManager.hpp>
#include <signalRegister.hpp>

namespace eos{
    namespace view{
        class mainWidget{
            public:
                mainWidget(std::shared_ptr<eos::business::signalManager> sigManager);
                ~mainWidget();
            
            private:
               void makeLayout();
               void drawImageInButton(nana::button& button,std::string icon); 
               void connect();

               nana::form fm;

               //Others
               nana::label header_title;
               nana::group config;
               nana::group wall;

               //Group 1 - Config Inputs
               nana::label time_lbl;
               nana::label ui_lbl;
               nana::combox time_unit;
               nana::spinbox time_input;
               nana::combox ui_combo;
               nana::checkbox random_chk;
               nana::combox carousel;

               //Group2 - Images Handler
               nana::label add_lbl;
               nana::label remove_lbl;
               nana::label show_lbl;
               nana::label create_lbl;
               nana::button add_image_btn;
               nana::button add_folder_btn;
               nana::button remove_image_btn;
               nana::button view_image_btn;
               nana::button remove_carousel_btn;
               nana::button create_carousel_btn;

               //Group3 - Main Controller
               nana::button start_btn;
               nana::button stop_btn;
               nana::button save_config_btn;
               nana::button add_view_image_btn;

               std::shared_ptr<eos::business::signalManager> manager;

        };
    };
}