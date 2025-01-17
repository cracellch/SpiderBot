 /*
 0 0 RC
 0 1 Dacta
 1 0 Evasor
 1 1 Baile
 */
#include <Servo.h>
#include <SoftwareSerial.h>
#define trigPin A3
#define echoPin A2
#define INCH 0
#define CM 1
int dato;
int datos [20];
int datos2 [20];
int i = 0;
int z = 0;
int l1 = 12;
int l2 = 13;
int da =  -12,  // Left Front Pivot
    db =   10,  // Left Back Pivot
    dc =  -18,  // Right Back Pivot
    dd =   12;  // Right Front Pivot
int a90  = (90  + da),
    a120 = (120 + da),
    a150 = (150 + da),
    a180 = (180 + da);
int b0   = (0   + db),
    b30  = (30  + db),
    b60  = (60  + db),
    b90  = (90  + db);
int c90  = (90  + dc),
    c120 = (120 + dc),
    c150 = (150 + dc),
    c180 = (180 + dc);
int d0   = (0   + dd),
    d30  = (30  + dd),
    d60  = (60  + dd),
    d90  = (90  + dd);
int s11 = 90; // Front Left Pivot Servo
int s12 = 90; // Front Left Lift Servo
int s21 = 90; // Back Left Pivot Servo
int s22 = 90; // Back Left Lift Servo
int s31 = 90; // Back Right Pivot Servo
int s32 = 90; // Back Right Lift Servo
int s41 = 90; // Front Right Pivot Servo
int s42 = 90; // Front Right Lift Servo
int f    = 0;
int b    = 0;
int l    = 0;
int r    = 0;
int spd  = 3;
int high = 0;
// Define 8 Servos
Servo myServo1; // Front Left Pivot Servo
Servo myServo2; // Front Left Lift Servo
Servo myServo3; // Back Left Pivot Servo
Servo myServo4; // Back Left Lift Servo
Servo myServo5; // Back Right Pivot Servo
Servo myServo6; // Back Right Lift Servo
Servo myServo7; // Front Right Pivot Servo
Servo myServo8; // Front Right Lift Servo
bool debug = false;
void setup() {
  pinMode(l1, INPUT);
  pinMode(l2, INPUT);
  myServo1.attach(2);
  myServo2.attach(3);
  myServo3.attach(4);
  myServo4.attach(5);
  myServo5.attach(6);
  myServo6.attach(7);
  myServo7.attach(8);
  myServo8.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  center_servos();
  delay(1000);
  Serial.begin (9600);
}
void loop(){
if(digitalRead(l1) == 0 && digitalRead(l2) == 0){//RC
    center_servos();
    if (Serial.available()){
    dato = Serial.read();
    Serial.print(dato); 
    }
     switch(dato){
      case 'w':
    forward();
    forward();
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
     break;
      case 's': 
      back();
      back();
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
     break;
      case 'a':
      turn_left();
      turn_left();
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
     break;
      case 'd':
      turn_right();
      turn_right();
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
     break;
    }
}
if(digitalRead(l1) == 0 &&  digitalRead(l2) == 1){//Dacta
    if (Serial.available()){
    center_servos();
    dato = Serial.read();
    datos[i] = dato;
    Serial.print(dato);   
    if(dato == 1){
    for(i = 0; i < z; i++){
    Serial.print(datos2[i]);
    if(datos2[i] == 8){
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
      forward();
      forward();
    }
    center_servos();
    if(datos2[i] == 2){
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
      back();
      back();
    }
    center_servos();
    if(datos2[i] == 4){
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
      turn_left();
      turn_left();

    }
    center_servos();
    if(datos2[i] == 6){
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
      turn_right();
      turn_right();
    }
    center_servos();
  }  
   }
    center_servos();
   if(dato == 3){
     for(i = 0; i < z; i++){
      datos2[i] = 0;
      datos[i] = 0;
    }
    i = 0;
    z = 0;
   }
   if(dato == 7){
      z = i;
      for(i = 0; i < z; i++){
        datos2[i] = datos[i];
      }
   }
    i++;   
   }
}
if(digitalRead(l1) == 1 &&  digitalRead(l2) == 0){ //Evasor
    if(get_distance(1) < 10){
    back();
    back();
    turn_left();
    turn_left();
  }else{
    unsigned long value;
    unsigned long lastValue;
    long distancia=0;
    center_servos();  // Center all servos
    high = 15;        // Set hight to 15
    spd = 5;          // Set speed to 3
    forward();
  }
}
if(digitalRead(l1) == 1 &&  digitalRead(l2) == 1){//Baile
    if(get_distance(1) < 15){
    baile();
  }
  else{
    center_servos();  // Center all servos
  }
}
}
void trim_left()
{
  da--; // Left Front Pivot
  db--; // Left Back Pivot
  dc--; // Right Back Pivot
  dd--; // Right Front Pivot
}
void trim_right()
{
  da++; // Left Front Pivot
  db++; // Left Back Pivot
  dc++; // Right Back Pivot
  dd++; // Right Front Pivot
}
void forward()
{
  // Left Front Pivot
  a90 = (90 + da),
  a120 = (120 + da),
  a150 = (150 + da),
  a180 = (180 + da);

  // Left Back Pivot
  b0 = (0 + db),
  b30 = (30 + db),
  b60 = (60 + db),
  b90 = (90 + db);

  // Right Back Pivot
  c90 = (90 + dc),
  c120 = (120 + dc),
  c150 = (150 + dc),
  c180 = (180 + dc);

  // Right Front Pivot
  d0 = (0 + dd),
  d30 = (30 + dd),
  d60 = (60 + dd),
  d90 = (90 + dd);

  // set servo positions and speeds needed to walk forward one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(a180, b0 , c120, d60, 42,  33,  33,  42,  1,  3,  1,  1);
  srv( a90, b30, c90,  d30, 6,   33,  33,  42,  3,  1,  1,  1);
  srv( a90, b30, c90,  d30, 42,  33,  33,  42,  3,  1,  1,  1);
  srv(a120, b60, c180, d0,  42,  33,  6,   42,  1,  1,  3,  1);
  srv(a120, b60, c180, d0,  42,  33,  33,  42,  1,  1,  3,  1);
  srv(a150, b90, c150, d90, 42,  33,  33,  6,   1,  1,  1,  3);
  srv(a150, b90, c150, d90, 42,  33,  33,  42,  1,  1,  1,  3);
  srv(a180, b0,  c120, d60, 42,  6,   33,  42,  1,  3,  1,  1);
  //srv(a180, b0,  c120, d60, 42,  15,  33,  42,  1,  3,  1,  1);
  
}
void back ()
{
  // set servo positions and speeds needed to walk backward one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(180, 0,  120, 60, 42, 33, 33, 42, 3,  1, 1, 1);
  srv(150, 90, 150, 90, 42, 18, 33, 42, 1,  3, 1, 1);
  srv(150, 90, 150, 90, 42, 33, 33, 42, 1,  3, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1,  1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1,  1, 1, 3);
  srv(90,  30, 90,  30, 42, 33, 18, 42, 1,  1, 3, 1);
  srv(90,  30, 90,  30, 42, 33, 33, 42, 1,  1, 3, 1);
  srv(180, 0,  120, 60, 6,  33, 33, 42, 3,  1, 1, 1);

}
void turn_left ()
{
  // set servo positions and speeds needed to turn left one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv(150,  90, 90,  30, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(150,  90, 90,  30, 42, 33, 33, 42, 1, 3, 1, 1);
  srv(120,  60, 180, 0,  42, 33, 6,  42, 1, 1, 3, 1);
  srv(120,  60, 180, 0,  42, 33, 33, 24, 1, 1, 3, 1);
  srv(90,   30, 150, 90, 42, 33, 33, 6,  1, 1, 1, 3);
  srv(90,   30, 150, 90, 42, 33, 33, 42, 1, 1, 1, 3);
  srv(180,  0,  120, 60, 6,  33, 33, 42, 3, 1, 1, 1);
  srv(180,  0,  120, 60, 42, 33, 33, 33, 3, 1, 1, 1);
}
void turn_right ()
{
  // set servo positions and speeds needed to turn right one step
  // (LFP,  LBP, RBP,  RFP, LFL, LBL, RBL, RFL, S1, S2, S3, S4)
  srv( 90, 30, 150, 90, 6,  33, 33, 42, 3, 1, 1, 1);
  srv( 90, 30, 150, 90, 42, 33, 33, 42, 3, 1, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1, 1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1, 1, 1, 3);
  srv(150, 90, 90,  30, 42, 33, 6,  42, 1, 1, 3, 1);
  srv(150, 90, 90,  30, 42, 33, 33, 42, 1, 1, 3, 1);
  srv(180, 0,  120, 60, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 33, 42, 1, 3, 1, 1);
}
void center_servos()
{
  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
  myServo5.write(90);
  myServo6.write(90);
  myServo7.write(90);
  myServo8.write(90);
  int s11 = 90; // Front Left Pivot Servo
  int s12 = 90; // Front Left Lift Servo
  int s21 = 90; // Back Left Pivot Servo
  int s22 = 90; // Back Left Lift Servo
  int s31 = 90; // Back Right Pivot Servo
  int s32 = 90; // Back Right Lift Servo
  int s41 = 90; // Front Right Pivot Servo
  int s42 = 90; // Front Right Lift Servo
}
void increase_speed()
{
  if (spd > 3)
    spd--;
}
void decrease_speed()
{
  if (spd < 50)
    spd++;
}
void srv( int  p11, int p21, int p31, int p41, int p12, int p22, int p32, int p42, int sp1, int sp2, int sp3, int sp4)
{

  // p11: Front Left Pivot Servo
  // p21: Back Left Pivot Servo
  // p31: Back Right Pivot Servo
  // p41: Front Right Pivot Servo
  // p12: Front Left Lift Servo
  // p22: Back Left Lift Servo
  // p32: Back Right Lift Servo
  // p42: Front Right Lift Servo
  // sp1: Speed 1
  // sp2: Speed 2
  // sp3: Speed 3
  // sp4: Speed 4

  // Multiply lift servo positions by manual height adjustment
  p12 = p12 + high * 3;
  p22 = p22 + high * 3;
  p32 = p32 + high * 3;
  p42 = p42 + high * 3;

  while ((s11 != p11) || (s21 != p21) || (s31 != p31) || (s41 != p41) || (s12 != p12) || (s22 != p22) || (s32 != p32) || (s42 != p42))
  {

    // Front Left Pivot Servo
    if (s11 < p11)            // if servo position is less than programmed position
    {
      if ((s11 + sp1) <= p11)
        s11 = s11 + sp1;      // set servo position equal to servo position plus speed constant
      else
        s11 = p11;
    }

    if (s11 > p11)            // if servo position is greater than programmed position
    {
      if ((s11 - sp1) >= p11)
        s11 = s11 - sp1;      // set servo position equal to servo position minus speed constant
      else
        s11 = p11;
    }

    // Back Left Pivot Servo
    if (s21 < p21)
    {
      if ((s21 + sp2) <= p21)
        s21 = s21 + sp2;
      else
        s21 = p21;
    }

    if (s21 > p21)
    {
      if ((s21 - sp2) >= p21)
        s21 = s21 - sp2;
      else
        s21 = p21;
    }

    // Back Right Pivot Servo
    if (s31 < p31)
    {
      if ((s31 + sp3) <= p31)
        s31 = s31 + sp3;
      else
        s31 = p31;
    }

    if (s31 > p31)
    {
      if ((s31 - sp3) >= p31)
        s31 = s31 - sp3;
      else
        s31 = p31;
    }

    // Front Right Pivot Servo
    if (s41 < p41)
    {
      if ((s41 + sp4) <= p41)
        s41 = s41 + sp4;
      else
        s41 = p41;
    }

    if (s41 > p41)
    {
      if ((s41 - sp4) >= p41)
        s41 = s41 - sp4;
      else
        s41 = p41;
    }

    // Front Left Lift Servo
    if (s12 < p12)
    {
      if ((s12 + sp1) <= p12)
        s12 = s12 + sp1;
      else
        s12 = p12;
    }

    if (s12 > p12)
    {
      if ((s12 - sp1) >= p12)
        s12 = s12 - sp1;
      else
        s12 = p12;
    }

    // Back Left Lift Servo
    if (s22 < p22)
    {
      if ((s22 + sp2) <= p22)
        s22 = s22 + sp2;
      else
        s22 = p22;
    }

    if (s22 > p22)
    {
      if ((s22 - sp2) >= p22)
        s22 = s22 - sp2;
      else
        s22 = p22;
    }

    // Back Right Lift Servo
    if (s32 < p32)
    {
      if ((s32 + sp3) <= p32)
        s32 = s32 + sp3;
      else
        s32 = p32;
    }

    if (s32 > p32)
    {
      if ((s32 - sp3) >= p32)
        s32 = s32 - sp3;
      else
        s32 = p32;
    }

    // Front Right Lift Servo
    if (s42 < p42)
    {
      if ((s42 + sp4) <= p42)
        s42 = s42 + sp4;
      else
        s42 = p42;
    }

    if (s42 > p42)
    {
      if ((s42 - sp4) >= p42)
        s42 = s42 - sp4;
      else
        s42 = p42;
    }

    // Write Pivot Servo Values
    myServo1.write(s11 + da);
    myServo3.write(s21 + db);
    myServo5.write(s31 + dc);
    myServo7.write(s41 + dd);

    // Write Lift Servos Values
    myServo2.write(s12);
    myServo4.write(s22);
    myServo6.write(s32);
    myServo8.write(s42);

    delay(spd); // Delay before next movement

  }
}

void baile(){
  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
  myServo5.write(90);
  myServo6.write(90);
  myServo7.write(90);
  myServo8.write(90);

  delay(500);
  //Inclinaciones 
  myServo2.write(50);
  myServo8.write(50);
  myServo6.write(130);
  myServo4.write(130);

  delay(500);

  myServo2.write(130);
  myServo8.write(130);
  myServo6.write(50);
  myServo4.write(50);

  delay(500);

  myServo2.write(50);
  myServo8.write(130);
  myServo6.write(130);
  myServo4.write(50);

  delay(500);

  myServo2.write(130);
  myServo8.write(50);
  myServo6.write(50);
  myServo4.write(130);

  delay(500);

  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
  myServo5.write(90);
  myServo6.write(90);
  myServo7.write(90);
  myServo8.write(90);

  delay(500);

  //Movimiento patas separadas
  //Pata izquierda
  myServo2.write(50);
  myServo6.write(50);
  delay(200);
  myServo1.write(30);
  delay(300);
  myServo1.write(150);
  delay(300);
  myServo1.write(30);
  delay(300);
  myServo1.write(150);
  delay(300);
  myServo1.write(30);
  delay(300);
  myServo1.write(150);
  delay(300);
  myServo1.write(90);
  delay(300);
  myServo2.write(90);
  myServo6.write(90);  
  delay(300);
  //Pata Derecha 
  myServo8.write(50);
  myServo4.write(50);
  delay(300);
  myServo7.write(30);
  delay(300);
  myServo7.write(150);
  delay(300);
  myServo7.write(30);
  delay(300);
  myServo7.write(150);
  delay(300);
  myServo7.write(30);
  delay(300);
  myServo7.write(150);
  delay(300);
  myServo7.write(90);
  delay(300);
  myServo8.write(90);
  myServo4.write(90);
  delay(300);
  //Pata trasera izquierda 
  myServo4.write(50);
  myServo8.write(50);
  delay(200);
  myServo3.write(30);
  delay(300);
  myServo3.write(150);
  delay(300);
  myServo3.write(30);
  delay(300);
  myServo3.write(150);
  delay(300);
  myServo3.write(30);
  delay(300);
  myServo3.write(150);
  delay(300);
  myServo3.write(90);
  delay(300);
  myServo4.write(90);
  myServo8.write(90);
  delay(300);
  //Pata trasera derecha 
  myServo6.write(50);
  myServo2.write(50);
  delay(200);
  myServo5.write(30);
  delay(300);
  myServo5.write(150);
  delay(300);
  myServo5.write(30);
  delay(300);
  myServo5.write(150);
  delay(300);
  myServo5.write(30);
  delay(300);
  myServo5.write(150);
  delay(300);
  myServo5.write(90);
  delay(300);
  myServo6.write(90);
  myServo2.write(90);
  delay(300);

  //Jarabe Tapatio
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);

  //Levantamiento de cada pata secuencial
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo4.write(50);
  delay(200);
  myServo4.write(90);
  delay(200);
  myServo6.write(50);
  delay(200);
  myServo6.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo4.write(50);
  delay(200);
  myServo4.write(90);
  delay(200);
  myServo6.write(50);
  delay(200);
  myServo6.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo4.write(50);
  delay(200);
  myServo4.write(90);
  delay(200);
  myServo6.write(50);
  delay(200);
  myServo6.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo6.write(50);
  delay(200);
  myServo6.write(90);
  delay(200);
  myServo4.write(50);
  delay(200);
  myServo4.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo6.write(50);
  delay(200);
  myServo6.write(90);
  delay(200);
  myServo4.write(50);
  delay(200);
  myServo4.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);
  myServo8.write(50);
  delay(200);
  myServo8.write(90);
  delay(200);
  myServo6.write(50);
  delay(200);
  myServo6.write(90);
  delay(200);
  myServo4.write(50);
  delay(200);
  myServo4.write(90);
  delay(200);
  myServo2.write(50);
  delay(200);
  myServo2.write(90);
  delay(200);

  //MovimientoLadoaLado

  myServo2.write(20);
  myServo4.write(20);
  myServo8.write(110);
  myServo6.write(110);
  delay(300);
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(20);
  myServo6.write(20);
  delay(300);
  myServo2.write(20);
  myServo4.write(20);
  myServo8.write(110);
  myServo6.write(110);
  delay(300);
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(20);
  myServo6.write(20);
  delay(300);
  myServo2.write(20);
  myServo4.write(20);
  myServo8.write(110);
  myServo6.write(110);
  delay(300);
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(20);
  myServo6.write(20);
  delay(300);
  myServo2.write(20);
  myServo4.write(20);
  myServo8.write(110);
  myServo6.write(110);
  delay(300);
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(20);
  myServo6.write(20);
  delay(300);
  myServo2.write(20);
  myServo4.write(20);
  myServo8.write(110);
  myServo6.write(110);
  delay(300);
  myServo2.write(20);
  myServo4.write(20);
  myServo8.write(110);
  myServo6.write(110);
  delay(300);
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(20);
  myServo6.write(20);
  delay(300);
  myServo2.write(20);
  myServo4.write(20);
  myServo8.write(110);
  myServo6.write(110);
  delay(300);

  //Sube y Baja
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(110);
  myServo6.write(110);
  delay(400);
  myServo2.write(40);
  myServo4.write(40);
  myServo8.write(40);
  myServo6.write(40);
  delay(400);
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(110);
  myServo6.write(110);
  delay(400);
  myServo2.write(40);
  myServo4.write(40);
  myServo8.write(40);
  myServo6.write(40);
  delay(400);
  myServo2.write(110);
  myServo4.write(110);
  myServo8.write(110);
  myServo6.write(110);
  delay(400);
  myServo2.write(40);
  myServo4.write(40);
  myServo8.write(40);
  myServo6.write(40);
  delay(400);
}

long get_distance(bool unit)
{
  // if unit == 0 return inches, else return cm

  long duration = 0, 
       cm = 0, 
       inches = 0;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;

  if (unit == INCH)
    return inches;
  else
    return cm;
}