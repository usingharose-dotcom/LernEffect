# Lern Effect — VST3/VSTGUI native project (no JUCE)

This is a larger native VST3 project shell for Windows 11 / FL Studio, using Steinberg's official VST3 SDK and VSTGUI. The editor target is 1280 x 760 pixels, a spacious landscape layout. The uploaded MetaTune.vst3 binary does not provide a trustworthy editor-size value by itself, so this is an editable design size rather than a claim of an exact MetaTune measurement.

## Included now
- Native VST3 processor/controller project.
- VSTGUI editor with a 1280 x 760 layout.
- Host parameters for Retune Speed, Detune, Amount, Sustain, Note Stabilizer, Low Latency, Real-time, Root Note, Scale Mode, Chromatic, Pitch Reference, Doubler controls, Keep My Scale, HeatMaps, Detected Notes, and 12 note-enable switches.
- Parameter state save/restore.
- Piano-note switches with note-name tooltips.
- No Tone generator, no added vibrato, and no reverb.
- Your original Lern Effect HTML retained in `reference/`.

## Critical current limitation
This is **not yet a finished auto-tune processor**. The plugin currently compiles as a native audio effect shell and passes stereo audio through unchanged. The UI controls are host parameters, but pitch detection, low-latency pitch shifting, note-stabilizer analysis, heatmap telemetry, presets/groups/snapshots, and a real-time doubler are not implemented in the DSP yet. The text-edit fields and note tooltips are UI scaffolding and need custom UI/controller work to deliver the exact typed-value and hover interactions. I am not claiming it is better than MetaTune or that it already corrects vocals.

## Windows 11 setup
Install Visual Studio 2022 Community with **Desktop development with C++**, CMake 3.25+, and Git for Windows. The SDK is fetched from Steinberg's official repository on first configure.

Run `scripts\build_windows.bat`. It generates a Visual Studio 2022 x64 build and compiles Release. If configuration fails, send the complete error output so the specific SDK/CMake issue can be fixed.

## FL Studio install
Copy the complete generated `LernEffect.vst3` bundle into `C:\Program Files\Common Files\VST3`, then use FL Studio > Options > Manage plugins > Find installed plugins.

## Next real engineering milestones
1. Verify compilation and VST3 validation.
2. Finish custom VSTGUI keyboard, hover pitch readout, editable ms/cents fields, live heatmap display, preset and A/B state management.
3. Implement and test a monophonic pitch detector and scale-aware note target selector.
4. Integrate a high-quality formant-aware pitch shifter with latency reporting and artifact tests.
5. Connect retune time, amount, sustain and note-stabilizer behavior to the DSP; implement a genuinely low-latency mode.
6. Test real vocals at 44.1/48/96 kHz and multiple buffer sizes before describing sound quality.

Official references: https://github.com/steinbergmedia/vst3sdk and https://steinbergmedia.github.io/vst3_dev_portal/pages/What+is+the+VST+SDK/VSTGUI.html


## Compact window sizing

The native editor template is now 292 x 363 pixels, matching the portrait proportions of the screenshot you supplied (292 x 363). This is a compact layout rather than a wide/landscape editor. Some advanced parameters remain registered with the host but are not all visible in this compact first screen.
