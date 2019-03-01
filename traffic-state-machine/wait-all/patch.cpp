
using State = uint8_t;

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    auto mask = getState(ctx);

    if (isInputDirty<input_RST>(ctx))
        *mask = 0x00;

    if (isInputDirty<input_IN1>(ctx))
        *mask |= 0x01;

    if (isInputDirty<input_IN2>(ctx))
        *mask |= 0x02;

    if (*mask == 0x03) {
        emitValue<output_OUT>(ctx, 1);
        *mask = 0xFF;
    }
}
