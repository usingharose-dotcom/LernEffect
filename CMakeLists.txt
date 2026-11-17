cmake_minimum_required(VERSION 3.25)

project(LernEffect VERSION 0.1.0.0
    DESCRIPTION "Lern Effect VST3 audio effect"
    LANGUAGES C CXX
)

# The SDK and VSTGUI are fetched from Steinberg's official VST3 SDK repository.
# First configure may take a while because it downloads the SDK.
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SMTG_ENABLE_VSTGUI_SUPPORT ON CACHE BOOL "" FORCE)

add_subdirectory(external)

smtg_enable_vst3_sdk()

smtg_add_vst3plugin(LernEffect
    source/version.h
    source/lerneffectcids.h
    source/lerneffectparamids.h
    source/lerneffectprocessor.h
    source/lerneffectprocessor.cpp
    source/lerneffectcontroller.h
    source/lerneffectcontroller.cpp
    source/lerneffectentry.cpp
    resource/LernEffect.uidesc
)

target_compile_features(LernEffect PRIVATE cxx_std_17)
target_link_libraries(LernEffect PRIVATE sdk vstgui_support)

smtg_target_add_plugin_resources(LernEffect
    RESOURCES
        resource/LernEffect.uidesc
)

smtg_target_configure_version_file(LernEffect)

if(SMTG_WIN)
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            PROPERTY VS_STARTUP_PROJECT LernEffect)
    endif()
endif()
