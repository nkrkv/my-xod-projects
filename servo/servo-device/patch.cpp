
{{#global}}
#include <Servo.h>
{{/global}}

using NodeId = uint16_t;

/*
  Represents some resource that should be owned/controlled exclusively by a node
  to perform a non-instant task.

  An example is a node which slowly rotates a motor shaft. The process is long
  (several seconds) and a particular rotation node can lock the motor resource
  so that other sibling rotation nodes can’t cause a conflict until the job is
  done and the motor resource is unlocked.
*/
class LockableResource {
  public:
    static constexpr NodeId NO_LOCK = 0xFFFF;

    bool lockFor(NodeId nodeId) {
        if (isLocked())
            return false;

        _lockedFor = nodeId;
        return true;
    }

    bool unlock(NodeId nodeId) {
        if (!isLockedFor(nodeId))
            return false;

        forceUnlock();
        return true;
    }

    void forceUnlock() {
        _lockedFor = NO_LOCK;
    }

    bool isLocked() const {
        return _lockedFor != NO_LOCK;
    }

    bool isLockedFor(NodeId nodeId) const {
        return _lockedFor == nodeId;
    }

  protected:
    NodeId _lockedFor = NO_LOCK;
};

/*
  A wrapper around the stock Servo object because we need to keep some details
  which the original object hides in private fields. This over-protection leads
  to increased RAM usage to duplicate the data. A pull request to the original
  library asking to add field read methods would be nice.
*/
struct XServo : public LockableResource {
    Servo servo;

    // Here are the duplicates
    bool shouldAttach = true;
    uint8_t port;
    int pulseMin;
    int pulseMax;

    // Set pulse duration according the given `value` and set pulseMin, pulseMax
    // The value is clipped to the [0; 1] range
    void write01(Number value) {
        ensureAttached();
        int pseudoAngle = constrain((int)(value * 180), 0, 180);
        servo.write(pseudoAngle);
    }

    // Performs Servo::attach with the parameters set previously
    void ensureAttached() {
        if (!shouldAttach && servo.attached())
            return;

        servo.attach(port, pulseMin, pulseMax);
        shouldAttach = false;
    }

    Number read01() const {
        int us = servo.readMicroseconds();
        return (Number)(us - pulseMin) / (Number)(pulseMax - pulseMin);
    }
};

using State = XServo;
using Type = XServo*;

{{ GENERATED_CODE }}

void evaluate(Context ctx) {
    State* state = getState(ctx);
    state->port = getValue<input_PORT>(ctx);
    state->pulseMin = getValue<input_Pmin>(ctx);
    state->pulseMax = getValue<input_Pmax>(ctx);
    state->shouldAttach = true;
    emitValue<output_DEV>(ctx, state);
}
