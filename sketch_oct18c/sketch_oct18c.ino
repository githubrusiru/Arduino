
//senser
int sR = A1;
int sL = A0;
//Right motor
int enL = 5;
int RF = 7;
int RR = 8;

//Left motor
int enR = 3;
int LF = 9;
int LR = 6;

void setup()
{



  pinMode(enR, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RR, OUTPUT);

  pinMode(enL, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LR, OUTPUT);

  Serial.begin(9600);
  pinMode(sL, INPUT);
  pinMode(sR, INPUT);

}

void loop() {
  int vL = analogRead(A0);
  int vR = analogRead(A1);
  Serial.print(vL);
  Serial.print("_");
  Serial.println(vR);

 // if () {
  //  analogWrite(enL, 0);
  //  analogWrite(enR, 0);
 // }
 // else {
    analogWrite(enL, 140);
    analogWrite(enR, 140);
//  }


  if  (vL < 40 && vR > 40 )
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    delay(300);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);

  } else if  (vL > 40 && vR < 40 )
  {
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    delay(300);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);

  }
  else if (vR < 40 && vL < 40 )
  {
    digitalWrite(7, HIGH);
    digitalWrite(9, HIGH);
    delay(300);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);

  } else {
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);

  }
}
