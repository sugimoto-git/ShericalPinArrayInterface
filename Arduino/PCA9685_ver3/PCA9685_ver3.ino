#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PCA9685クラスは、PCA9685ドライバを操作するためのクラスです。
class PCA9685Channel {
    private:
        Adafruit_PWMServoDriver* pca;
        uint8_t channel;

    public:
        // コンストラクタはPCA9685ドライバのインスタンスとチャンネル番号を受け取ります。
        PCA9685Channel(Adafruit_PWMServoDriver* pwmDriver, uint8_t chA) :
            pca(pwmDriver), channel(chA){
        
        }

        // サーボを制御するための関数。dutyCycleを設定します。
        void setPWM(uint16_t on, uint16_t off) {
            pca->setPWM(channel, on, off);
        }

        void On(){
          pca->setPWM(channel, 0, 4096);
        }
        
        void Off(){
          pca->setPWM(channel, 4096, 0);
        }  
        
        // 周波数を設定する関数
        void setFrequency(float freq) {
            pca->setPWMFreq(freq);
        }
};

class PinActuator {
    private:
        Adafruit_PWMServoDriver* pca;  // PCAインスタンス
        PCA9685Channel pin_plus;  // チャンネル1
        PCA9685Channel pin_minus;  // チャンネル2
    
    public:
        PinActuator(Adafruit_PWMServoDriver* pca_ptr, int pin_num1, int pin_num2) : 
            pca(pca_ptr), pin_plus(pca, pin_num1), pin_minus(pca, pin_num2){
            // PCAの初期化
            pca->begin();
            pca->setPWMFreq(60);
        }

    void On() {
      pin_plus.On();
      pin_minus.Off();
    }

    void Off() {
      pin_plus.Off();
      pin_minus.On();
    }
};

class PinArray {
    private:
        Adafruit_PWMServoDriver pca;  // PCAインスタンス
        PinActuator* actuators[8];    // PinActuatorのポインタ配列
        int pins[8][2] = {{0, 1},{2, 3},{4, 5},{6, 7},{8, 9},{10, 11},{12, 13},{14, 15}};

    public:
        // コンストラクタでI2Cアドレスを受け取り、8つのPinActuatorインスタンスを初期化
        PinArray(uint8_t address) : pca(address) {
            pca.begin();
            pca.setPWMFreq(60);
    
            for (int i = 0; i < 8; i++) {
                actuators[i] = new PinActuator(&pca, pins[i][0], pins[i][1]);
            }
        }

        ~PinArray() {
            for (int i = 0; i < 8; i++) {
                delete actuators[i];
            }
        }

        PinActuator* getActuator(int index) {
            if (index >= 0 && index < 8) {
                return actuators[index];
            }
            return nullptr;  // 範囲外のインデックスの場合はnullptrを返す
        }

        void turnAllOn() {
            for (int i = 0; i < 8; i++) {
                actuators[i]->On();
            }
        }

        void turnAllOff() {
            for (int i = 0; i < 8; i++) {
                actuators[i]->Off();
            }
        }
};


// グローバル変数としてPinArrayインスタンスを宣言
PinArray pinarr1(0x41);
PinArray pinarr2(0x42);

PinArray pinarr3(0x43);
PinArray pinarr4(0x44);

PinArray pinarr5(0x45);
PinArray pinarr6(0x46);

PinArray pinarr7(0x47);
PinArray pinarr8(0x48);

PinArray pinarr9(0x49);
PinArray pinarr10(0x50);

void setup() {
    Serial.begin(9600);
}

void loop() {
    pinarr1.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr1.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr2.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr2.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr3.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr3.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr4.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr4.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr5.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr5.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr6.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr6.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr7.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr7.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr8.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr8.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr9.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr9.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

    pinarr10.turnAllOn();  // すべてのPinActuatorをオンにする
    delay(1000);         // 1秒待つ
    pinarr10.turnAllOff(); // すべてのPinActuatorをオフにする
    delay(1000);         // 1秒待つ

}
