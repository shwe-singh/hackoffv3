#include <Servo.h>

Servo servo_test;

int angle = 0;
//----------------------------------------INITIALISATION-----------------------------------------------
int UDmotorpin1 = 2;
int UDmotorpin2 = 3;
int UDen = 10;

int LRmotorpin1 = 4;
int LRmotorpin2 = 5;
int LRen = 11;
const int t = 200;
int curr_flr = 0;

//-------------------------------------------SETUP------------------------------------------------------

void setup()
{
  servo_test.attach(9);
  pinMode(UDmotorpin1, OUTPUT);
  pinMode(UDmotorpin2, OUTPUT);
  pinMode(LRmotorpin1, OUTPUT);
  pinMode(LRmotorpin2, OUTPUT);
  Serial.begin(9600);
}

// MOTOR CONTROL
void up()
{
  Serial.println("moving up");
  digitalWrite(UDen, HIGH);
  digitalWrite(LRen, LOW);
  digitalWrite(UDmotorpin1, HIGH);
  digitalWrite(UDmotorpin2, LOW);
  delay(t);
  digitalWrite(LRmotorpin1, LOW);
  digitalWrite(LRmotorpin2, LOW);
  curr_flr += 2;
  Serial.println(curr_flr);

}
void down()
{
  digitalWrite(UDen, HIGH);
  digitalWrite(LRen, LOW);
  Serial.println("going down");
  digitalWrite(UDmotorpin1, LOW);
  digitalWrite(UDmotorpin2, HIGH);
  delay(t);
  digitalWrite(LRmotorpin1, LOW);
  digitalWrite(LRmotorpin2, LOW);
  curr_flr -= 2;
  Serial.println(curr_flr);
}

void forward()
{
  digitalWrite(UDen, LOW);
  digitalWrite(LRen, HIGH);
  Serial.println("going right");
  digitalWrite(UDmotorpin1, LOW);
  digitalWrite(UDmotorpin2, LOW);
  delay(t);
  digitalWrite(LRmotorpin1, HIGH);
  digitalWrite(LRmotorpin2, LOW);
  curr_flr += 1;
  Serial.println(curr_flr);

}
void back()
{
  Serial.println("going left");
  digitalWrite(UDmotorpin1, LOW);
  digitalWrite(UDmotorpin2, LOW);
  delay(t);
  digitalWrite(LRmotorpin1, LOW);
  digitalWrite(LRmotorpin2, HIGH);
  curr_flr -= 1;
  Serial.println(curr_flr);
}
void stops()
{
  digitalWrite(UDmotorpin1, LOW);
  digitalWrite(UDmotorpin2, LOW);
  digitalWrite(LRmotorpin1, LOW);
  digitalWrite(LRmotorpin2, LOW);
}

void clicks() //Press Button
{
  for (angle = 0; angle < 180; angle += 1)
  {
    servo_test.write(angle);
    delay(15);
  }

  delay(1000);

  for (angle = 180; angle >= 1; angle -= 5)
  {
    servo_test.write(angle);
    delay(5);
  }
  Serial.println("click button");
}

//----------------------------------------LOOP---------------------------------------

void loop() {
  Serial.println("Enter floor");
  while (Serial.available()==0){}             // wait for user input
  int flr_num = Serial.parseInt();
  Serial.setTimeout(43200000);    //if no button is pressed for 12 hrs, lift goes to zero

  if (flr_num <= 7 && flr_num >= 0) //check for valid floor input
  {
    //x-axis movement
    if (curr_flr%2 == 0)
    {
      if (flr_num % 2 != 0)
      {
        forward();
        delay(2000);
      }
    }
    else
    {
      if (flr_num % 2 == 0)
      {
        back();
        delay(2000);
      }
    }
    if(curr_flr == flr_num){
        clicks();
      }
    //y-axis movement
    int diff = flr_num - curr_flr;
    if  (curr_flr == 0 || flr_num == 0)
    {
      if(diff > 0){
      for(int i =0; i < abs(diff)/2; i++)
      {
        up();
        delay(2000);
      }
      if(curr_flr == flr_num){
        clicks();
      }
    }
    else
    {
      for(int i =0; i < abs(diff)/2; i++)
      {
        down();
        delay(2000);
      }
      if(curr_flr == flr_num){
        clicks();
      }
    }
    } 
    else
    {
      if(diff > 0){
        for(int i =0; i< (abs(diff)+1)/2; i++)
        {
          up();
          delay(2000);
        }
        if(curr_flr == flr_num){
        clicks();
      }
      }
      else
      {
        for(int i =0; i< (abs(diff)+1)/2; i++)
        {
          down();
          delay(2000);
        }
        if(curr_flr == flr_num){
        clicks();
      }
      }
    }
  }
  else
  {
    Serial.println("INVALID FLOOR, Try Again"); //print in OLED
  }
}
