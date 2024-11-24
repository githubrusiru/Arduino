//senser
int sR = A0;
int sL = A1;


void setup()
{


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
}
