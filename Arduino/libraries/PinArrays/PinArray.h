#ifndef PINARRAY_H
#define PINARRAY_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class PCA9685Channel {
private:
    Adafruit_PWMServoDriver* pca;
    uint8_t channel;

public:
    PCA9685Channel(Adafruit_PWMServoDriver* pwmDriver, uint8_t chA);
    void setPWM(uint16_t on, uint16_t off);
    void On();
    void Off();
    void setFrequency(float freq);
};

class PinActuator {
private:
    Adafruit_PWMServoDriver* pca;
    PCA9685Channel pin_plus;
    PCA9685Channel pin_minus;

public:
    PinActuator(Adafruit_PWMServoDriver* pca_ptr, int pin_num1, int pin_num2);
    void On();
    void Off();
};

class PinArray {
private:
    Adafruit_PWMServoDriver pca;
    PinActuator* actuators[8];

public:
    PinArray(uint8_t address, int pins[][2]);
    ~PinArray();
    PinActuator* getActuator(int index);
    void turnAllOn();
    void turnAllOff();
};

#endif

