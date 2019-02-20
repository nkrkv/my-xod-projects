struct State {
    uint8_t state = 0xFF;
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    State* state = getState(ctx);
    auto newValue = getValue<input_IN>(ctx);

    if (newValue == true && state->state == 0x00)
        emitValue<output_OUT>(ctx, 1);

    state->state = newValue ? 0x01 : 0x00;
}
