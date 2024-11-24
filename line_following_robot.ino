
//senser
int sR = A0;
int sL = A1;
//Right motor
int enL = 5;
int RF = 7;
int RR = 8;

//Left motor
int enR =3;
int LF = 9;
int LR = 6;

void setup()
{



  // put your setup code here, to run once:
  pinMode(enR, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RR, OUTPUT);

  pinMode(enL, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LR, OUTPUT);

  pinMode(sL, INPUT);
  pinMode(sR, INPUT);

}


void loop()
{
  int vL = analogRead(A0);
  int vR = analogRead(A1);
  Serial.print(vL);
  Serial.print("_");
  Serial.println(vR);

  analogWrite(enL, 130);
  analogWrite(enR, 130);

  //forward
  digitalWrite(7, HIGH);
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
  digitalWrite(9, LOW);
  delay(1000);

  //turn left
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  delay(1000);

  //turn rihgt
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  delay(1000);

  //Backword
  digitalWrite(8, HIGH);
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  digitalWrite(6, LOW);
  delay(1000);

  
}
