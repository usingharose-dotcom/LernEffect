#pragma once
#include <array>
#include "public.sdk/source/vst/vstaudioeffect.h"

namespace Steinberg {
class LernEffectProcessor final : public Vst::AudioEffect {
public:
    LernEffectProcessor();
    ~LernEffectProcessor() SMTG_OVERRIDE = default;
    static FUnknown* createInstance(void*) { return static_cast<Vst::IAudioProcessor*>(new LernEffectProcessor()); }
    tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API setupProcessing(Vst::ProcessSetup& setup) SMTG_OVERRIDE;
    tresult PLUGIN_API canProcessSampleSize(int32 symbolicSampleSize) SMTG_OVERRIDE;
    tresult PLUGIN_API process(Vst::ProcessData& data) SMTG_OVERRIDE;
    tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE;
    tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE;
private:
    // Normalized host parameters. DSP remains intentionally transparent until
    // the dedicated pitch-shifter milestone is implemented and tested.
    std::array<Vst::ParamValue, 28> mParameters {
        0.25, 0.50, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0,
        440.0 / 880.0, 0.5, 0.0, 1.0, 1.0, 1.0,
        1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0
    };
};
}
