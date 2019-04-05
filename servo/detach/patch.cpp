
struct State { };

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    auto xservo = getValue<input_DEV>(ctx);

    if (isSettingUp()) {
        // Short-circuit DEV and DEV'
        emitValue<output_DEVU0027>(ctx, xservo);
    }

    if (!isInputDirty<input_DO>(ctx))
        return;

    xservo->forceUnlock();
    xservo->servo.detach();
    emitValue<output_DONE>(ctx, 1);
}
