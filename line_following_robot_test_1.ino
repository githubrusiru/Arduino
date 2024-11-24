//senser
int sL = A0;
int sR = A1;
//pwm
int enL = 5;
int enR = 6;
//Motor
int inR2 = 8;
int inR1 = 9;
int inL2 = 10;
int inL1 = 11;


void setup() {

  Serial.begin(9600);

  pinMode(sL, INPUT);
  pinMode(sR, INPUT);

  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);

  pinMode(inR1, OUTPUT);
  pinMode(inR2, OUTPUT);

  pinMode(inL1, OUTPUT);
  pinMode(inL2, OUTPUT);


}


void loop() {
  int vL = analogRead(A0);
  int vR = analogRead(A1);
  Serial.print(vL);
  Serial.print("_");
  Serial.println(vR);

  analogWrite(enL,255);
  analogWrite(enR,255);

  
  if (vR > 40) {
    digitalWrite(inL1, HIGH);
    digitalWrite(inL2, LOW);

  } else {
    digitalWrite(inL1, LOW);
    digitalWrite(inL2, HIGH);

  }


  if (vL > 40) {
    digitalWrite(inR1, HIGH);
    digitalWrite(inR2, LOW);

  } else {
    digitalWrite(inR1, LOW);
    digitalWrite(inR2, HIGH);

  }


}
