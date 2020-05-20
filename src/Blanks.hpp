#pragma once

#include "plugin.hpp"

namespace captainssounds{
    struct BlankModule : Module {
        BlankModule() {
            config(0, 0, 0);
        }
    };

    struct Blank901 : BlankModule {};
    struct Blank902 : BlankModule {};
    struct Blank904 : BlankModule {};
}


extern Model* modelBlank901;
extern Model* modelBlank902;
extern Model* modelBlank904;