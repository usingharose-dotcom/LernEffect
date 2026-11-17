#include "lerneffectcontroller.h"
#include "lerneffectparamids.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include <cstring>

namespace Steinberg {
tresult PLUGIN_API LernEffectController::initialize(FUnknown* context)
{
    const tresult result = EditControllerEx1::initialize(context);
    if (result != kResultOk) return result;
    const int32 a = Vst::ParameterInfo::kCanAutomate;
    auto continuous = [this, a](const char16* name, const char16* unit, Vst::ParamID id, double def) {
        parameters.addParameter(name, unit, 0, def, a, id);
    };
    auto toggle = [this, a](const char16* name, Vst::ParamID id, double def) {
        parameters.addParameter(name, nullptr, 1, def, a, id);
    };
    continuous(STR16("Retune Speed"), STR16("ms"), LernEffectParams::kRetuneSpeed, 0.25);
    continuous(STR16("Detune"), STR16("cents"), LernEffectParams::kDetuneCents, 0.50);
    continuous(STR16("Amount"), STR16("%"), LernEffectParams::kAmount, 1.0);
    continuous(STR16("Sustain"), nullptr, LernEffectParams::kSustain, 0.50);
    continuous(STR16("Note Stabilizer"), nullptr, LernEffectParams::kNoteStabilizer, 0.0);
    toggle(STR16("Low Latency"), LernEffectParams::kLowLatency, 1.0);
    toggle(STR16("Real-time Mode"), LernEffectParams::kRealtimeMode, 1.0);
    parameters.addParameter(STR16("Root Note"), nullptr, 11, 0.0, a, LernEffectParams::kRootNote);
    parameters.addParameter(STR16("Scale Mode"), nullptr, 4, 0.0, a, LernEffectParams::kScaleMode);
    toggle(STR16("Chromatic"), LernEffectParams::kChromatic, 0.0);
    continuous(STR16("Pitch Reference"), STR16("Hz"), LernEffectParams::kPitchReference, 0.5);
    continuous(STR16("Doubler Width"), STR16("%"), LernEffectParams::kDoublerWidth, 0.5);
    continuous(STR16("Doubler Mix"), STR16("%"), LernEffectParams::kDoublerMix, 0.0);
    toggle(STR16("Keep My Scale"), LernEffectParams::kKeepMyScale, 1.0);
    toggle(STR16("HeatMaps"), LernEffectParams::kHeatMaps, 1.0);
    toggle(STR16("Detected Notes"), LernEffectParams::kDetectedNotes, 1.0);
    const char16* noteNames[12] = { STR16("Key C"), STR16("Key C#"), STR16("Key D"), STR16("Key D#"),
        STR16("Key E"), STR16("Key F"), STR16("Key F#"), STR16("Key G"), STR16("Key G#"),
        STR16("Key A"), STR16("Key A#"), STR16("Key B") };
    const double noteDefaults[12] = {1,0,1,0,1,1,0,1,0,1,0,1};
    for (int i = 0; i < 12; ++i)
        parameters.addParameter(noteNames[i], nullptr, 1, noteDefaults[i], a,
            LernEffectParams::kKeyC + static_cast<Vst::ParamID>(i));
    return kResultOk;
}

tresult PLUGIN_API LernEffectController::setComponentState(IBStream* state)
{
    if (!state) return kResultFalse;
    IBStreamer streamer(state, kLittleEndian);
    for (int32 i = 0; i < LernEffectParams::kParameterCount; ++i) {
        float value = 0.0f;
        if (!streamer.readFloat(value)) return kResultFalse;
        setParamNormalized(LernEffectParams::kRetuneSpeed + static_cast<Vst::ParamID>(i), value);
    }
    return kResultOk;
}

IPlugView* PLUGIN_API LernEffectController::createView(FIDString name)
{
    if (name && std::strcmp(name, Vst::ViewType::kEditor) == 0)
        return new VSTGUI::VST3Editor(this, "view", "LernEffect.uidesc");
    return nullptr;
}
} // namespace Steinberg
