#ifndef MYSTEPPING_H
#define MYSTEPPING_H

#include <Arduino.h>

class MyStepping {
    public:
        MyStepping(int pin1, int pin2, int pin3, int pin4);
        void makeStepper();
        int setIntval(float speed);
        void move(int target, float speed);
    private:
        int phasA, enblA, phasB, enblB, i, mode;
};

#endif // MYSTEPPING_H
