
#define relayPin 3 // the pin relay is connected
#define potPin  A1 // the pin potentiometer is connected

#define startPin 1 // the pin where start switch is connected

#define relayType 'L' // Relay trigger type. L for low and H for high

//because the time below is in millisecond, 1000ms=1 second, 1000x60=60000 is 1 minuets. 60x60x1000=3600000 is 1 hour
const long maxTime = 30000;// maximum timer time in milliseconds. for one minute =60000, 1 hours =3600000
const long minTime = 3000; // miniimum timer time in milliseconds

// do not change anything bellow here
long duration;
int potValue;
long rememTime;
int relayState =0;

void setup() {
  pinMode(relayPin, OUTPUT);// define relayPin  as output
 
  pinMode(startPin, INPUT_PULLUP);// define input pin with pullup (watch video)

    
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  if(relayType == 'L')
  {
    digitalWrite(relayPin, HIGH);// turn the relay OFF and keep it OFF
      Serial.println("Robojax.com Relay Timer"); 
      Serial.println("Relay Type: LOW Trigger");      
  }else{
    digitalWrite(relayPin, LOW);// turn the relay OFF and keep it OFF
      Serial.println("Robojax.com Relay Timer"); 
      Serial.println("Relay Type: HIGH Trigger");
  }  
}

void loop() {
  potValue = analogRead(potPin)/10;// reads the value of the potentiometer (value between 0 and 1023)

  duration = map(potValue, 0, 102, minTime, maxTime);// convert A0 value to time set at minTime and maxTime
  
    if(digitalRead(startPin) ==LOW)
    {
     rememTime = millis();
     relayState = 1;
     controlRelay();// send command to turn the relay ON
    }
   if(  (millis()- rememTime) > duration )
   {
    relayState = 0;
    controlRelay();
   }
      Serial.print("Time: ");
      Serial.print(duration/1000);
      Serial.println(" Seconds");     
 delay(200); // wait for 200 milliseconds    
}// loop end


/*
 * 
 * @brief Turns the relay ON or OFF 
 * @param none
 * @return no return value
 */

 void controlRelay()
 {
  if(relayType == 'L')
  {
     if(relayState == 1)
     {
    digitalWrite(relayPin, LOW);// Turn ON relay
      Serial.print("LT-Relay ON for ");
      Serial.print(duration/1000);// display in seconds
      Serial.println(" Seconds");
     }else{
    digitalWrite(relayPin, HIGH); // turn OFF
      Serial.println("====Relay is OFF");
     }
      
  }else{
     if(relayState == 1)
     {    
      digitalWrite(relayPin, HIGH);
      Serial.print("HT-Relay ON for ");
      Serial.print(duration/1000);// display in seconds
      Serial.println(" Seconds");  
     }else{
      digitalWrite(relayPin, LOW); 
      Serial.println("==Relay OFF");  
     }  
  }

}//controlRelay end
