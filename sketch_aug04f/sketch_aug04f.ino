#include "Adafruit_FONA.h"
#include <SoftwareSerial.h>

// Pin Definitions
#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

// Button Pin Definitions
#define NUM_BUTTON 3
#define SEND_BUTTON_PIN 8
#define CALL_BUTTON_PIN 7
#define HANGUP_BUTTON_PIN 6
#define NO_PRESS -1
#define SEND_BUT 0
#define CALL_BUT 1
#define HANGUP_BUT 2

#define RELAY_PIN 9
#define START_RELAY_PIN 10

char replybuffer[255];
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

short gsArray_But_Pin[NUM_BUTTON] = {SEND_BUTTON_PIN, CALL_BUTTON_PIN, HANGUP_BUTTON_PIN};
short sButton_Read = NO_PRESS;
String smsString = "";
unsigned short gusIsSend_Bef = 0;

char szPhoneNum[] = "+94787970764"; // Fill in your phone number
char imei[16] = {0}; // Global variable for IMEI

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(START_RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(START_RELAY_PIN, HIGH);

  for (short i = 0; i < NUM_BUTTON; i++) {
    pinMode(gsArray_But_Pin[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
  Serial.println(F("FONA SMS caller ID test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  fonaSerial->begin(4800);
  if (!fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));

  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("SIM card IMEI: ");
    Serial.println(imei);
  }

  fonaSerial->print("AT+CNMI=2,1\r\n"); // Set up the FONA to send a +CMTI notification when an SMS is received

  Serial.println("FONA Ready");

  // Check network status
  checkNetworkStatus();
}

char fonaNotificationBuffer[64]; // For notifications from the FONA
char smsBuffer[250];

void loop() {
  char* bufPtr = fonaNotificationBuffer; // Handy buffer pointer

  sButton_Read = sRead_Button();

  if (sButton_Read == SEND_BUT) {
    if (gusIsSend_Bef == 0) {
      String message = "Warning: Unauthorized access to bike! Type txt - stop, 1hstop, reset, start. IMEI: " + String(imei);
      if (!fona.sendSMS(szPhoneNum, message.c_str())) {
        Serial.println(F("Failed to send SMS"));
      } else {
        Serial.println(F("SMS Sent!"));
      }
      gusIsSend_Bef = 1;
    }
  } else if (sButton_Read == CALL_BUT) {
    if (gusIsSend_Bef == 0) {
      if (!fona.callPhone(szPhoneNum)) {
        Serial.println(F("Failed to call"));
      } else {
        Serial.println(F("Calling..."));
      }
      gusIsSend_Bef = 1;
    }
  } else if (sButton_Read == HANGUP_BUT) {
    if (gusIsSend_Bef == 0) {
      if (!fona.hangUp()) {
        Serial.println(F("Failed to hang up"));
      } else {
        Serial.println(F("Call ended"));
      }
      gusIsSend_Bef = 1;
    }
  } else {
    gusIsSend_Bef = 0;
  }

  if (fona.available()) { // Any data available from the FONA?
    int slot = 0; // This will be the slot number of the SMS
    int charCount = 0;

    // Read the notification into fonaNotificationBuffer
    do {
      *bufPtr = fona.read();
      Serial.write(*bufPtr);
      delay(1);
    } while ((*bufPtr++ != '\n') && (fona.available()) && (++charCount < (sizeof(fonaNotificationBuffer) - 1)));

    *bufPtr = 0;

    Serial.print(F("Notification buffer: ")); Serial.println(fonaNotificationBuffer);

    if (1 == sscanf(fonaNotificationBuffer, "+CMTI: \"SM\",%d", &slot)) {
      Serial.print("SMS slot: "); Serial.println(slot);

      char callerIDbuffer[32]; // We'll store the SMS sender number in here

      if (!fona.getSMSSender(slot, callerIDbuffer, 31)) {
        Serial.println("Didn't find SMS message in slot!");
      }
      Serial.print(F("FROM: ")); Serial.println(callerIDbuffer);

      uint16_t smslen;
      if (fona.readSMS(slot, smsBuffer, 250, &smslen)) { // Pass in buffer and max len!
        smsBuffer[smslen] = '\0'; // Null-terminate the string
        smsString = String(smsBuffer);
        Serial.print("Received SMS: "); Serial.println(smsString);
      } else {
        Serial.println("Failed to read SMS");
      }
    }
  }
}

short sRead_Button(void) {
  short sStatus = NO_PRESS;

  for (short i = 0; i < NUM_BUTTON; i++) {
    if (digitalRead(gsArray_But_Pin[i]) == 0) {
      delay(50);
      if (digitalRead(gsArray_But_Pin[i]) == 0) {
        sStatus = i;
      }
    }
  }
  return sStatus;
}

void checkNetworkStatus() {
  uint8_t n = fona.getNetworkStatus();
  Serial.print(F("Network status: "));
  Serial.println(n);

  if (n == 0) {
    Serial.println(F("Not registered, not searching"));
  } else if (n == 1) {
    Serial.println(F("Registered (home)"));
  } else if (n == 2) {
    Serial.println(F("Not registered, searching"));
  } else if (n == 3) {
    Serial.println(F("Registration denied"));
  } else if (n == 4) {
    Serial.println(F("Unknown"));
  } else if (n == 5) {
    Serial.println(F("Registered roaming"));
  } else {
    Serial.println(F("Unknown network status"));
  }
}
