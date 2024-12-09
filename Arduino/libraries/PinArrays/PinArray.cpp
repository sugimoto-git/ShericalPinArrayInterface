#include "PinArray.h"

// PCA9685Channelのコンストラクタ
PCA9685Channel::PCA9685Channel(Adafruit_PWMServoDriver* pwmDriver, uint8_t chA)
    : pca(pwmDriver), channel(chA) {}

void PCA9685Channel::setPWM(uint16_t on, uint16_t off) {
    pca->setPWM(channel, on, off);
}

void PCA9685Channel::On() {
    pca->setPWM(channel, 0, 4096);
}

void PCA9685Channel::Off() {
    pca->setPWM(channel, 4096, 0);
}

void PCA9685Channel::setFrequency(float freq) {
    pca->setPWMFreq(freq);
}

// PinActuatorのコンストラクタ
PinActuator::PinActuator(Adafruit_PWMServoDriver* pca_ptr, int pin_num1, int pin_num2)
    : pca(pca_ptr), pin_plus(pca, pin_num1), pin_minus(pca, pin_num2) {
    pca->begin();
    pca->setPWMFreq(60);
}

void PinActuator::On() {
    pin_plus.On();
    pin_minus.Off();
}

void PinActuator::Off() {
    pin_plus.Off();
    pin_minus.On();
}

// PinArrayのコンストラクタ
PinArray::PinArray(uint8_t address, int pins[][2]) : pca(address) {
    pca.begin();
    pca.setPWMFreq(60);

    for (int i = 0; i < 8; i++) {
        actuators[i] = new PinActuator(&pca, pins[i][0], pins[i][1]);
    }
}

// PinArrayのデストラクタ
PinArray::~PinArray() {
    for (int i = 0; i < 8; i++) {
        delete actuators[i];
    }
}

PinActuator* PinArray::getActuator(int index) {
    if (index >= 0 && index < 8) {
        return actuators[index];
    }
    return nullptr;
}

void PinArray::turnAllOn() {
    for (int i = 0; i < 8; i++) {
        actuators[i]->On();
    }
}

void PinArray::turnAllOff() {
    for (int i = 0; i < 8; i++) {
        actuators[i]->Off();
    }
}

