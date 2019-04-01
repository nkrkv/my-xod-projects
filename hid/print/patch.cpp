
struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    // Chain DEV to DEV'
    emitValue<output_DEVU0027>(ctx, getValue<input_DEV>(ctx));

    if (!isInputDirty<input_DO>(ctx))
        return;

    auto kb = getValue<input_DEV>(ctx);
    auto s = getValue<input_S>(ctx);

    for (auto it = s.iterate(); it; ++it)
        kb->write(*it);

    emitValue<output_DONE>(ctx, 1);
}
