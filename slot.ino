#include <sim900.h>
#include <Adafruit_FONA.h>
#include "Adafruit_FONA.h"
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

char replybuffer[255];

#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

#define RELAY_PIN 9
#define START_RELAY_PIN 10

#define NUM_BUTTON 3
#define SEND_BUTTON_PIN 8
#define CALL_BUTTON_PIN 7
#define HANGUP_BUTTON_PIN 6
#define NO_PRESS -1
#define SEND_BUT 0
#define CALL_BUT 1
#define HANGUP_BUT 2

short gsArray_But_Pin[NUM_BUTTON] = {SEND_BUTTON_PIN, CALL_BUTTON_PIN, HANGUP_BUTTON_PIN};
short sButton_Read = NO_PRESS;
String smsString = "";
unsigned short gusIsSend_Bef = 0;

char szPhoneNum[] = "+94787970764";
char imei[16] = {0};

const unsigned long START_DELAY = 2500;

void setup() 
{
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(START_RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(START_RELAY_PIN, HIGH);

  for(short i = 0; i < NUM_BUTTON; i++)
  {
    pinMode(gsArray_But_Pin[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  fonaSerial->begin(9600); // Adjust if needed
  if (!fona.begin(*fonaSerial))
  {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));

  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) 
  {
    Serial.print("SIM card IMEI: "); Serial.println(imei);
  }

  fonaSerial->print("AT+CNMI=2,1\r\n"); // Set up the FONA to send a +CMTI notification when an SMS is received

  Serial.println("FONA Ready");
}

char fonaNotificationBuffer[64];
char smsBuffer[250];

void loop() 
{
  sButton_Read = sRead_Button();

  if(sButton_Read == SEND_BUT && gusIsSend_Bef == 0)
  {
    String message = "Warning: Unauthorized access_bike!! Typ txt - stop, 1hstop, reset, start IMEI: " + String(imei);
    if(!fona.sendSMS(szPhoneNum, message.c_str()))
    {
      Serial.println(F("Failed to send SMS"));
    } 
    else 
    {
      Serial.println(F("SMS Sent!"));
    }
    gusIsSend_Bef = 1;
  }
  else if(sButton_Read == CALL_BUT && gusIsSend_Bef == 0)
  {
    if (!fona.callPhone(szPhoneNum)) 
    {
      Serial.println(F("Failed to call"));
    } 
    else 
    {
      Serial.println(F("Call Sent!"));
    }
    gusIsSend_Bef = 1;
  }
  else if(sButton_Read == HANGUP_BUT && gusIsSend_Bef == 0)
  {
    if (! fona.hangUp()) 
    {
      Serial.println(F("Failed to hang up"));
    } 
    else 
    {
      Serial.println(F("Call hung up successfully"));
    }
    gusIsSend_Bef = 1;
  }
  else
  {
    gusIsSend_Bef = 0;
  }

  if(fona.available()) 
  {
    int slot = 0;
    int charCount = 0;
    char* bufPtr = fonaNotificationBuffer;

    // Read notification into buffer
    do
    {
      *bufPtr = fona.read();
      Serial.write(*bufPtr);
      delay(1);
    } while ((*bufPtr++ != '\n') && (fona.available()) && (++charCount < (sizeof(fonaNotificationBuffer)-1)));

    *bufPtr = 0;

    if (1 == sscanf(fonaNotificationBuffer, "+CMTI: " FONA_PREF_SMS_STORAGE ",%d", &slot)) 
    {
      Serial.print("SMS slot: "); Serial.println(slot);

      char callerIDbuffer[32];

      if (!fona.getSMSSender(slot, callerIDbuffer, 31)) 
      {
        Serial.println("Didn't find SMS sender in slot!");
      }
      Serial.print(F("FROM: ")); Serial.println(callerIDbuffer);

      uint16_t smslen;
      if (fona.readSMS(slot, smsBuffer, 250, &smslen)) 
      { 
        smsString = String(smsBuffer);
        Serial.print("Received SMS: ");
        Serial.println(smsString);
      }

      if (smsString == "start")
      {
        Serial.println("Activating start relay...");
        digitalWrite(START_RELAY_PIN, LOW);
        delay(START_DELAY);
        digitalWrite(START_RELAY_PIN, HIGH);
        Serial.println("Start relay deactivated.");

        fona.sendSMS(callerIDbuffer, "Bike start relay activated for 2 seconds.");
      }
      else if (smsString == "stop")
      {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Bike stop relay activated.");
        fona.sendSMS(callerIDbuffer, "Relay is activated. bike stop ");
      }
      else if(smsString == "1hstop")
      {
        digitalWrite(RELAY_PIN, LOW);
        Serial.println("Relay activated for 1 hour.");
        fona.sendSMS(callerIDbuffer, "Relay is activated for 1 hour.");
        delay(3600000); // 1 hour
        digitalWrite(RELAY_PIN, HIGH);
        fona.sendSMS(callerIDbuffer, "Relay is deactivated after 1 hour.");
      } 
      else if(smsString == "reset")
      {
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("Relay deactivated.");
        fona.sendSMS(callerIDbuffer, "Relay is deactivated.");
      }
    }  
  }
}

short sRead_Button(void)
{
  short sStatus = NO_PRESS;

  for(short i = 0; i < NUM_BUTTON; i++)
  {
    if(digitalRead(gsArray_But_Pin[i]) == 0)
    {
      delay(50);
      if(digitalRead(gsArray_But_Pin[i]) == 0)
      {
        sStatus = i;
      }
    }
  }
  return sStatus;
}
