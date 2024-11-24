//senser
int sL = A0;
int sR = A1;
//pwm
int enL = 5;
int enR = 6;
//Motor
int inR1 = 8;
int inR2 = 9;
int inL1 = 10;
int inL2 = 11;


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

  digitalWrite(inL1, HIGH);
  
}
