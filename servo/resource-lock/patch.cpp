
struct State {
};

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    auto res = getValue<input_RES>(ctx);

    if (isSettingUp()) {
        // Short-circuit RES and RES'
        emitValue<output_RESU0027>(ctx, res);
    }

    bool justEntered = false;
    auto nodeId = getNodeId(ctx);

    if (isInputDirty<input_ENTR>(ctx) && res->lockedFor == 0) {
        res->lockedFor = nodeId;
        justEntered = true;
    }

    if (isInputDirty<input_EXIT>(ctx)
        && (res->lockedFor == 0 || res->lockedFor == nodeId)) {

        justEntered = false;
        res->lockedFor = 0;
        emitValue<output_EXITU0027>(ctx, 1);
    }

    if (justEntered)
        emitValue<output_ENTRU0027>(ctx, 1);

    if (isInputDirty<input_IN>(ctx) && res->lockedFor == nodeId)
        emitValue<output_OUT>(ctx, 1);
}
