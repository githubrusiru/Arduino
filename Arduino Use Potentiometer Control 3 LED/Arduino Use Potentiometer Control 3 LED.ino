int i = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  i = analogRead(A0);
  if (i < 400)
  {
    digitalWrite(13, 1);
    digitalWrite(12, 0);
    digitalWrite(11, 0);
  }
  else if(i < 900)
  {
    digitalWrite(13, 0);
    digitalWrite(12, 1);
    digitalWrite(11, 0);
  }
  else
  {
    digitalWrite(13, 0);
    digitalWrite(12, 0);
    digitalWrite(11, 1);
  }

}
