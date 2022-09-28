#include "pages.hpp"

#include "Manager.hpp"

#include "home.hpp"

#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include "Fl/Fl_File_Chooser.H"
#include "Fl/Fl_Multiline_Output.H"

#include <algorithm>


///directory
namespace {
    Fl_File_Chooser*  fc;
    Fl_Multiline_Output *box;

    void choose_callback(Fl_File_Chooser *obj, void *)
    {
        if(fc->visible()) return;
        Manager::manager.installDir = obj->value();
        box->value(Manager::manager.installDir.c_str());
        if(obj != fc)
            throw std::runtime_error("choose_callback page0(5.5) ");
        delete fc;
        fc = nullptr;
    }

    void call_back_page_1(Fl_Widget*, void*)
    {
        if (!fc) {
            fc = new Fl_File_Chooser(nullptr, nullptr, 4, nullptr);
            fc->callback(choose_callback);
            fc->show();
        }else if(!fc->visible())
            fc->show();
    }
}

void auto_download_cb(Fl_Widget*, void*);

void page_6()
{
    auto *g = new Fl_Group(0, 0, width, height);

    auto *next = new Fl_Button(button_x+png_size, button_y, button_width, button_height, "Process");
    next->callback(auto_download_cb);

    auto *back = new Fl_Button(button_x - button_width - 20 + png_size, button_y,
                               button_width, button_height, "@<- Back");
    back->callback(back_cb);

    auto *set_dir = new Fl_Button(500 + png_size, 180, 100, 25, "Choose");
    set_dir->callback(call_back_page_1);

    box = new Fl_Multiline_Output(100 + png_size, 150, 500, 25,"Install in: ");
    Manager::manager.installDir = home();
    box->value(Manager::manager.installDir.c_str());

    auto *out = new Fl_Box(20 + png_size, 100, 500, 25, "Select directory for installation");
    out->labelsize(45);
    out->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);

    Manager::logo();

    g->end();
}
