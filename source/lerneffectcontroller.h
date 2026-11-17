#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {

class LernEffectController final : public Vst::EditControllerEx1
{
public:
    static FUnknown* createInstance(void*)
    {
        return static_cast<Vst::IEditController*>(new LernEffectController());
    }

    tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API setComponentState(IBStream* state) SMTG_OVERRIDE;
    IPlugView* PLUGIN_API createView(FIDString name) SMTG_OVERRIDE;

    DEFINE_INTERFACES
        // No additional VST interfaces in this first starter version.
    END_DEFINE_INTERFACES(EditController)
    DELEGATE_REFCOUNT(EditController)
};

} // namespace Steinberg
