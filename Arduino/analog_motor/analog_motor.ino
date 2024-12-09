const int MT_F = 5;
const int MT_R = 6;

void setup(){
    pinMode( MT_F, OUTPUT );
    pinMode( MT_R, OUTPUT );
}

void loop(){
    int speed;
    
    analogWrite( MT_F, 0 );
    analogWrite( MT_R, 0 );
    
    speed = 0;
    while( speed <= 255 ){
        analogWrite( MT_F, speed );
        delay( 100 );
        speed = speed + 5;
    }
    
    delay( 5000 );

    speed = 255;
    while( speed >= 0 ){
        analogWrite( MT_F, speed );
        delay( 100 );
        speed = speed - 5;
    }

    delay( 5000 );

}