#include "lerneffectprocessor.h"
#include "lerneffectcids.h"
#include "lerneffectparamids.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include <algorithm>

namespace Steinberg {
LernEffectProcessor::LernEffectProcessor() { setControllerClass(kLernEffectControllerUID); }

tresult PLUGIN_API LernEffectProcessor::initialize(FUnknown* context)
{
    const tresult result = AudioEffect::initialize(context);
    if (result != kResultOk) return result;
    addAudioInput(STR16("Stereo Input"), Vst::SpeakerArr::kStereo);
    addAudioOutput(STR16("Stereo Output"), Vst::SpeakerArr::kStereo);
    return kResultOk;
}
tresult PLUGIN_API LernEffectProcessor::setupProcessing(Vst::ProcessSetup& setup)
{ return AudioEffect::setupProcessing(setup); }
tresult PLUGIN_API LernEffectProcessor::canProcessSampleSize(int32 size)
{ return size == Vst::kSample32 ? kResultTrue : kResultFalse; }

tresult PLUGIN_API LernEffectProcessor::process(Vst::ProcessData& data)
{
    if (data.inputParameterChanges) {
        const int32 count = data.inputParameterChanges->getParameterCount();
        for (int32 q = 0; q < count; ++q) {
            auto* queue = data.inputParameterChanges->getParameterData(q);
            if (!queue || queue->getPointCount() == 0) continue;
            Vst::ParamValue value = 0.0; int32 offset = 0;
            if (queue->getPoint(queue->getPointCount() - 1, offset, value) != kResultTrue) continue;
            const auto id = queue->getParameterId();
            if (id >= LernEffectParams::kRetuneSpeed &&
                id < LernEffectParams::kRetuneSpeed + LernEffectParams::kParameterCount)
                mParameters[static_cast<size_t>(id - LernEffectParams::kRetuneSpeed)] = std::clamp(value, 0.0, 1.0);
        }
    }
    if (data.numSamples <= 0 || data.numInputs == 0 || data.numOutputs == 0) return kResultOk;
    auto& in = data.inputs[0]; auto& out = data.outputs[0];
    if (!in.channelBuffers32 || !out.channelBuffers32) return kResultOk;
    const int32 channels = std::min(in.numChannels, out.numChannels);
    for (int32 ch = 0; ch < channels; ++ch) {
        const float* src = in.channelBuffers32[ch]; float* dst = out.channelBuffers32[ch];
        if (src && dst && src != dst) std::copy_n(src, data.numSamples, dst);
    }
    out.silenceFlags = in.silenceFlags;
    return kResultOk;
}

tresult PLUGIN_API LernEffectProcessor::setState(IBStream* state)
{
    if (!state) return kResultFalse;
    IBStreamer streamer(state, kLittleEndian);
    for (auto& p : mParameters) { float v = 0.0f; if (!streamer.readFloat(v)) return kResultFalse; p = std::clamp(static_cast<double>(v), 0.0, 1.0); }
    return kResultOk;
}
tresult PLUGIN_API LernEffectProcessor::getState(IBStream* state)
{
    if (!state) return kResultFalse;
    IBStreamer streamer(state, kLittleEndian);
    for (const auto p : mParameters) streamer.writeFloat(static_cast<float>(p));
    return kResultOk;
}
} // namespace Steinberg
