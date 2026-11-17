#pragma once

#include "pluginterfaces/base/funknown.h"

namespace Steinberg {

// Unique IDs for this plug-in. Do not reuse another plug-in's IDs.
static const FUID kLernEffectProcessorUID(
    0x4B8F21D7, 0xA61C4E32, 0x9F70B5C8, 0xD3126A41);

static const FUID kLernEffectControllerUID(
    0x7C1D9A53, 0xE8424B16, 0xA5F3C9D0, 0x6218BE74);

#define LernEffectVST3Category "Fx|Tools"

} // namespace Steinberg
