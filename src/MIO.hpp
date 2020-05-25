#pragma once
#include "plugin.hpp"

namespace captainssounds {
    struct MIO: Module {
        enum inputIds {
            INPUT_1,
            INPUT_2,
            INPUT_3,
            INPUT_4,
            INPUT_5,
            INPUT_6,
            NUM_INPUTS
        };
        enum outputIds {
            OUTPUT_A,
            OUTPUT_B,
            NUM_OUTPUTS
        };

        int numChannels = 16;
        float outputAV [16];
        float outputBV [16];
        int channelsA = 0;
        int channelsB = 0;

        MIO() {
            config(0, NUM_INPUTS, NUM_OUTPUTS);
        }

        void process(const ProcessArgs& args) override;
    };
}