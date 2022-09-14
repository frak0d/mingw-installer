#include "pages.hpp"
#include "Manager.hpp"


void update4(); ///exceptions realization

///architecture
namespace {
    const std::array<std::string_view, 2> archs{
            "i686\0",
            "x86_64\0"
    };
    Fl_Choice *choice;

    void choice_callback(Fl_Button *obj, void *) {
        size_t value = choice->value();
        Manager::manager.downloadCandidate.architecture = !value ? Arcs::i686 : Arcs::x86_64;
        update4();
    }
}


void page_2() {
    Fl_Group *g = new Fl_Group(0, 0, 400, 300);
    Fl_Button *next = new Fl_Button(290, 265, 100, 25, "Next @->");
    next->callback(next_cb);
    Fl_Button *back = new Fl_Button(180, 265, 100, 25, "@<- Back");
    back->callback(back_cb);

    Fl_Box *out = new Fl_Box(20, 100, 25, 25, "Select an architecture");
    out->labelsize(50);
    out->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);

    choice = new Fl_Choice(200, 150, 15 * (archs[0].size() * 2), 45); //,"Select a version");

    for (auto &arch: archs)
        choice->add(arch.data());

    choice->value(0);
    choice->textsize(20);
    choice->callback((Fl_Callback *) choice_callback);
    g->end();
}
