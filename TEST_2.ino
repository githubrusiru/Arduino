
//senser
int Ls1 = 2;
int Ls2 = A0;
int Rs1 = 13;
int Rs2 = 11;

//Right motor
int enL = 5;

int LF = 7;
int RF = 4;

//Left motor
int enR = 3;

int RR = 6;
int LR = 8;

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
  int Ls1 = digitalRead(2);
  int Ls2 = digitalRead(A0);
  int Rs1 = digitalRead(11);
  int Rs2 = digitalRead(A1);

  Serial.print(Ls1);
  Serial.print("_");
  Serial.println(Rs1);
  

  analogWrite(enL, 200);
  analogWrite(enR, 200);


  // digitalWrite(7, HIGH); //wama issrhata
  // digitalWrite(4, HIGH); // dauna issraha

  //digitalWrite(8, HIGH); //wama passta
  // digitalWrite(6, HIGH); // dakuna passta

  //dakunta herenna
  //digitalWrite(7, HIGH);
  //digitalWrite(6, HIGH);

  //wamata  herenna
  //digitalWrite(8, HIGH);
  //digitalWrite(4, HIGH);

   if  (Ls1 == 0 && Rs1 == 0)//dekama issrhata
  {
    digitalWrite(7, HIGH);
    digitalWrite(4, HIGH);


  } else if  (Ls1 == 0 && Rs1 == 1 )//dakunta ganna
  {
    digitalWrite(7, HIGH);
    digitalWrite(6, HIGH);
    delay(500);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);


  }
  else if (Ls1 == 1 && Rs1 == 0 )//wamta gnna
  {
    digitalWrite(8, HIGH);
    digitalWrite(4, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    digitalWrite(4, LOW);

  } else {
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);

  }
}
