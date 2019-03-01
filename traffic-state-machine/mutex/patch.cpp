
struct State {
    uint16_t lockedFor;
};

using Type = State*;

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    emitValue<output_OUT>(ctx, getState(ctx));
}
