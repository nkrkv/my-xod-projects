
struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    auto xservo = getValue<input_DEV>(ctx);

    if (isSettingUp()) {
        // Short-circuit DEV and DEV'
        emitValue<output_DEVU0027>(ctx, xservo);
    }

    bool justEntered = false;
    auto nodeId = getNodeId(ctx);

    if (isInputDirty<input_ENTR>(ctx) && xservo->lockedFor == 0) {
        xservo->lockedFor = nodeId;
        justEntered = true;
    }

    if (isInputDirty<input_EXIT>(ctx)
        && (xservo->lockedFor == 0 || xservo->lockedFor == nodeId)) {

        justEntered = false;
        xservo->lockedFor = 0;
        emitValue<output_EXITU0027>(ctx, 1);
    }

    if (justEntered)
        emitValue<output_ENTRU0027>(ctx, 1);

    if (isInputDirty<input_IN>(ctx) && xservo->lockedFor == nodeId)
        emitValue<output_OUT>(ctx, 1);
}
