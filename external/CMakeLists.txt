cmake_minimum_required(VERSION 3.25)

include(FetchContent)

# Steinberg's official VST3 SDK includes the VST3 API, helper classes,
# sample infrastructure, and VSTGUI as a submodule.
FetchContent_Declare(
    vst3sdk
    GIT_REPOSITORY https://github.com/steinbergmedia/vst3sdk.git
    GIT_TAG v3.8.1_build_84
    GIT_SUBMODULES_RECURSE TRUE
)

FetchContent_MakeAvailable(vst3sdk)
