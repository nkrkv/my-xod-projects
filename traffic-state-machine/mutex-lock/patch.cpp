
struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    auto mutex = getValue<input_MX>(ctx);

    if (isSettingUp()) {
        // Short-circuit MX and MX'
        emitValue<output_MXU0027>(ctx, mutex);
    }

    bool justEntered = false;
    auto nodeId = getNodeId(ctx);

    if (isInputDirty<input_ENTR>(ctx) && mutex->lockedFor == 0) {
        mutex->lockedFor = nodeId;
        justEntered = true;
    }

    if (isInputDirty<input_EXIT>(ctx)
        && (mutex->lockedFor == 0 || mutex->lockedFor == nodeId)) {

        justEntered = false;
        mutex->lockedFor = 0;
        emitValue<output_EXITU0027>(ctx, 1);
    }

    if (justEntered)
        emitValue<output_ENTRU0027>(ctx, 1);

    if (isInputDirty<input_IN>(ctx) && mutex->lockedFor == nodeId)
        emitValue<output_OUT>(ctx, 1);
}
