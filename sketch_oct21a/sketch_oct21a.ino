//senser
int Ls1 = 4;
int Ls2 = A0;
int Rs1 = 2;
int Rs2 = A1;
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

  Serial.print(Ls2);
  Serial.print("_");
  Serial.println(Rs2);

  analogWrite(enL, 200);
  analogWrite(enR, 200);

  if  (Ls2 > 300 && Rs2 > 300)//forwad
  {
    digitalWrite(7, HIGH);
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(7, LOW);
    digitalWrite(9, LOW);///ok

  }  }
