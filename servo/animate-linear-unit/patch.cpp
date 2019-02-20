
struct State {
    TimeMs prevTime;
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    auto now = transactionTime();
    auto state = getState(ctx);
    auto rate = max(0, getValue<input_RATE>(ctx));
    auto out = getValue<output_OUT>(ctx);

    if (isSettingUp()) {
        emitValue<output_IDLE>(ctx, true);
    }

    if (isInputDirty<input_FWD>(ctx)) {
        // Fast forward to 1.0
        emitValue<output_OUT>(ctx, 1);
        emitValue<output_IDLE>(ctx, true);
        clearTimeout(ctx);
        return;
    }

    if (isInputDirty<input_PLAY>(ctx)) {
        // Start animation from scratch
        emitValue<output_OUT>(ctx, 0);
        emitValue<output_IDLE>(ctx, false);
        state->prevTime = now;
        setTimeout(ctx, 0);
        return;
    }

    if (isInputDirty<input_REV>(ctx)) {
        // Rewind to 0.0 and cancel animation
        emitValue<output_OUT>(ctx, 0);
        emitValue<output_IDLE>(ctx, true);
        clearTimeout(ctx);
        return;
    }

    if (isTimedOut(ctx)) {
        // Continue animation
        auto dt = now - state->prevTime;
        out += dt / 1000.0 * rate;

        if (out >= 1) {
            emitValue<output_OUT>(ctx, 1);
            emitValue<output_IDLE>(ctx, true);
        } else {
            emitValue<output_OUT>(ctx, out);
            emitValue<output_IDLE>(ctx, false);
            state->prevTime = now;
            setTimeout(ctx, 0);
        }
    }
}
