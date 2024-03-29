#include "DBug.hpp"
#include <math.h>
#include <rack.hpp>
#include <regex>
#include <string>
#include "CSModule.hpp"
#include "dsp.hpp"
#include "plugin.hpp"

using namespace captainssounds;
using namespace rack;

struct DBugWidget : CSModuleWidget {
    const Vec offset = Vec(8, 30);
    const Vec displaySize = Vec(288, 220);
    DBugWidget(DBug* module) {
        hp = 20;
        setModule(module);
        box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);

        auto panel = new SvgPanel();
        panel->box.size = box.size;
        panel->setBackground(APP->window->loadSvg(asset::plugin(pluginInstance, "res/DBug.svg")));
        addChild(panel);

        auto display = new DBugDisplay(module);
        display->box.pos = offset;
        display->box.size = displaySize;
        addChild(display);

        addScrews();
    }
};

void DBugDisplay::drawScreen(const DrawArgs& args) {
    nvgSave(args.vg);
    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 0, box.size.x - 5, box.size.y);
    nvgFillColor(args.vg, nvgRGBA(0x00, 0x00, 0x00, 0xff));
    nvgFill(args.vg);
    nvgRestore(args.vg);
}

void DBugDisplay::draw(const DrawArgs& args) {
    drawScreen(args);

    // Check for module &  dbug on dbug bombs
    if (isConnected() && isSafe()) {
        auto consumerMessage = module->leftExpander.consumerMessage;
        // if (dynamic_cast<DBugMessagesPtr>(consumerMessage) == nullptr) {
        //     // if (typeid(consumerMessage) != typeid(DBugMessagesPtr)) {
        //     return;
        // }

        incomingMessage = (DBugMessagesPtr)consumerMessage;

        // DEBUG("incoming Messages %s", typeid(consumerMessage).name() == typeid(DBugMessages));
        nvgSave(args.vg);
        nvgFontSize(args.vg, 9);
        nvgFontFaceId(args.vg, font->handle);
        nvgFillColor(args.vg, nvgRGBA(0x00, 0xFF, 0x00, 0xff));
        // if (incomingMessage == nullptr) {
        //     return;
        // }
        for (int i = 0; i < (int)sizeof(incomingMessage); i++) {
            std::string inc(incomingMessage[i]);
            std::string msg = std::regex_replace(inc, std::regex(module->reg), "");
            nvgText(args.vg, 5, 15 + (i * yOffset), msg.c_str(), NULL);
        }
        nvgRestore(args.vg);
    }
    Widget::draw(args);
}

bool DBugDisplay::isConnected() {
    return module && module->leftExpander.module;
}

bool DBugDisplay::isSafe() {
    auto leftExpanderModule = module->leftExpander.module;
    bool notNested = leftExpanderModule->model != modelDBug;
    bool isDBugable = dynamic_cast<CSModule*>(leftExpanderModule) != nullptr;
    return notNested && isDBugable;
}

Model* modelDBug = createModel<DBug, DBugWidget>("DBug");