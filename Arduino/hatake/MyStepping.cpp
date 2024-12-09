#include "MyStepping.h"

MyStepping::MyStepping(int pin1, int pin2, int pin3, int pin4) {
    phasA = pin1;
    enblA = pin2;
    phasB = pin3;
    enblB = pin4;
}

void MyStepping::makeStepper() {
    pinMode(phasA, OUTPUT);
    pinMode(enblA, OUTPUT);
    pinMode(phasB, OUTPUT);
    pinMode(enblB, OUTPUT);
    digitalWrite(enblA, HIGH);
    digitalWrite(enblB, HIGH);
}

int MyStepping::setIntval(float speed) { // speed[rot/s]
    int intval = int(5000.0f / speed); // intval[microsec/step]
    return intval;
}

void MyStepping::move(int target, float speed) {
    mode = 1;
    if (target < 0) {
        target *= -1;
        mode = -1;
    }

    int intval = setIntval(speed);

    for (i = 0; i < target; i++) {
        switch ((i * mode) % 4) {
            case 0:
                digitalWrite(phasA, HIGH);
                break;
            case 1:
                digitalWrite(phasB, HIGH);
                break;
            case 2:
                digitalWrite(phasA, LOW);
                break;
            case 3:
                digitalWrite(phasB, LOW);
                break;
        }
        delayMicroseconds(intval);
    }
}
