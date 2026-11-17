#pragma once
#include "pluginterfaces/vst/vsttypes.h"

namespace Steinberg { namespace LernEffectParams {
enum : Vst::ParamID {
    kRetuneSpeed = 100,
    kDetuneCents = 101,
    kAmount = 102,
    kSustain = 103,
    kNoteStabilizer = 104,
    kLowLatency = 105,
    kRealtimeMode = 106,
    kRootNote = 107,
    kScaleMode = 108,
    kChromatic = 109,
    kPitchReference = 110,
    kDoublerWidth = 111,
    kDoublerMix = 112,
    kKeepMyScale = 113,
    kHeatMaps = 114,
    kDetectedNotes = 115,
    kKeyC = 116, kKeyCs = 117, kKeyD = 118, kKeyDs = 119,
    kKeyE = 120, kKeyF = 121, kKeyFs = 122, kKeyG = 123,
    kKeyGs = 124, kKeyA = 125, kKeyAs = 126, kKeyB = 127,
    kParameterCount = 28
};
} }
