
#pragma XOD require "https://github.com/arduino-libraries/Keyboard"

{{#global}}
#include <Keyboard.h>
{{/global}}

using Type = Keyboard_*;

struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    auto kb = &Keyboard;
    if (isInputDirty<input_INIT>(ctx))
        kb->begin();

    emitValue<output_DEV>(ctx, kb);
}
