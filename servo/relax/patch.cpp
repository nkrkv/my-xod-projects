
struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    if (isSettingUp()) {
        // Short-circuit DEV and DEV'
        emitValue<output_DEVU0027>(ctx, xservo);
    }

    if (!isInputDirty<input_SET>(ctx))
        return;

    getValue<input_DEV>(ctx)->detach();
}
