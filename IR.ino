#include<IRremote.h>
IRrecv Rusiru(11);
decode_results results;
//senser
int Ls1 = 4;
int Ls2 = A0;
int Rs1 = 2;
int Rs2 = A1;

//Right motor
int enL = 5;

int LF = 7;
int RF = 4;

//Left motor
int enR = 3;

int RR = 6;
int LR = 8;

void setup() {
  Serial.begin(9600);
  Rusiru.enableIRIn();
  pinMode(13, OUTPUT);

  pinMode(enR, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RR, OUTPUT);

  pinMode(enL, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LR, OUTPUT);




  pinMode(Ls1, INPUT);
  pinMode(Ls2, INPUT);
  pinMode(Rs1, INPUT);
  pinMode(Rs2, INPUT);

}

void loop() {
  int Ls1 = digitalRead(4);
  int Ls2 = digitalRead(A0);
  int Rs1 = digitalRead(2);
  int Rs2 = digitalRead(A1);


  if (Rusiru.decode(&results)) {
    Serial.println(results.value, DEC);
    Rusiru.resume();

    if (results.value == 4294967295) {
      Serial.print("ujiji");
      digitalWrite(13, HIGH);
      analogWrite(enL, 0);
      analogWrite(enR, 0);
      delay(1500);
      digitalWrite(13, LOW);

    } else if  (Ls1 == 0 && Rs1 == 0 || Ls2 == 1 && Rs2 == 1 )//dekama issrhata
    {
      analogWrite(enL, 120);
      analogWrite(enR, 120);
      digitalWrite(7, HIGH);
      digitalWrite(4, HIGH);
      delay(50);
      digitalWrite(7, LOW);
      digitalWrite(4, LOW);

    } else if  ( Ls1 == 0 && Rs1 == 1 || Ls2 == 1 && Rs2 == 0 )//dakunta ganna
    {
      analogWrite(enL, 140);
      analogWrite(enR, 140);
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
      delay(100);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);


    }
    else if (Ls2 == 0 && Rs2 == 1 || Ls1 == 1 && Rs1 == 0 )//wamta gnna
    {
      analogWrite(enL, 140);
      analogWrite(enR, 140);
      digitalWrite(8, HIGH);
      digitalWrite(4, HIGH);
      delay(100);
      digitalWrite(8, LOW);
      digitalWrite(4, LOW);

    } else {
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(9, LOW);
      digitalWrite(8, LOW);

    }
  }
}
