#include "lerneffectprocessor.h"
#include "lerneffectcontroller.h"
#include "lerneffectcids.h"
#include "version.h"

#include "public.sdk/source/main/pluginfactory.h"

#define stringPluginName "Lern Effect"

using namespace Steinberg;
using namespace Steinberg::Vst;

BEGIN_FACTORY_DEF("Lern Audio", "https://example.invalid", "mailto:change-this-before-release@example.invalid")

DEF_CLASS2(
    INLINE_UID_FROM_FUID(kLernEffectProcessorUID),
    PClassInfo::kManyInstances,
    kVstAudioEffectClass,
    stringPluginName,
    Vst::kDistributable,
    LernEffectVST3Category,
    FULL_VERSION_STR,
    kVstVersionString,
    LernEffectProcessor::createInstance
)

DEF_CLASS2(
    INLINE_UID_FROM_FUID(kLernEffectControllerUID),
    PClassInfo::kManyInstances,
    kVstComponentControllerClass,
    stringPluginName " Controller",
    0,
    "",
    FULL_VERSION_STR,
    kVstVersionString,
    LernEffectController::createInstance
)

END_FACTORY
