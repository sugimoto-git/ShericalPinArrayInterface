int spr = 200; //17HS4401は200ステップ1回転。
int gear1 = 32; //歯車1の歯数は32。
int gear2 = 4;  //歯車2の歯数は4。
float rps = 10;  //1秒での回転数。これで回転速度を指定する。

MyStepping stepper1(4, 5, 6, 7);

void setup(){
    stepper1.makeStepper();
}

void loop(){
    stepper1.move(-spr / 2 * gear1 / gear2, rps);
    delay(1000);
    stepper1.move(spr * gear1 / gear2, rps);
    delay(1000);
    stepper1.move(-spr * gear1 / gear2, rps);
    delay(1000);
    stepper1.move(spr / 2 * gear1 / gear2, rps);
    delay(1000);
    delay(2000);
}
