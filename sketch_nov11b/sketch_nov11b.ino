#include <Adafruit_FONA.h>
#include <SoftwareSerial.h>

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

SoftwareSerial fonaSS(FONA_TX, FONA_RX);
Adafruit_FONA fona(FONA_RST);

const char* targetPhoneNumber = "+94787970764"; // Replace with your phone number
char smsBuffer[250]; // Buffer to store received SMS content
char fonaNotificationBuffer[64]; // Buffer for notifications from the FONA

void setup() {
  Serial.begin(9600);
  fonaSS.begin(4800);

  Serial.println("Initializing FONA...");
  if (!fona.begin(fonaSS)) {
    Serial.println("Couldn't find FONA");
    while (1);
  }
  Serial.println("FONA initialized");

  // Set FONA to notify when an SMS is received
  fonaSS.print("AT+CNMI=2,1,0,0,0\r\n");
  Serial.println("Waiting for SMS...");
}

void loop() {
  if (fona.available()) {
    int slot;
    if (checkForSMS(slot)) {
      handleSMS(slot);
      deleteSMS(slot);
    }
  }
}

bool checkForSMS(int &slot) {
  // Read the notification into fonaNotificationBuffer
  char* bufPtr = fonaNotificationBuffer;
  int charCount = 0;

  while (fona.available() && charCount < sizeof(fonaNotificationBuffer) - 1) {
    *bufPtr = fona.read();
    Serial.write(*bufPtr); // Print notification for debugging
    bufPtr++;
    charCount++;
    delay(1);
  }
  *bufPtr = '\0'; // Null-terminate the notification buffer

  // Check if notification indicates an SMS
  return sscanf(fonaNotificationBuffer, "+CMTI: \"SM\",%d", &slot) == 1;
}

void handleSMS(int slot) {
  char senderNumber[32]; // To store sender's phone number

  if (fona.getSMSSender(slot, senderNumber, 31)) {
    Serial.print("From: ");
    Serial.println(senderNumber);

    uint16_t smsLen;
    if (fona.readSMS(slot, smsBuffer, sizeof(smsBuffer) - 1, &smsLen)) {
      String message = String(smsBuffer);
      Serial.print("Message: ");
      Serial.println(message);

      if (message == "start") {
        Serial.println("Received 'start' command. (Add start functionality here)");
        fona.sendSMS(senderNumber, "Bike start command received.");
      }
      else if (message == "stop") {
        Serial.println("Received 'stop' command. (Add stop functionality here)");
        fona.sendSMS(senderNumber, "Bike stop command received.");
      }
      // Add additional commands as needed
    }
  }
}

void deleteSMS(int slot) {
  if (fona.deleteSMS(slot)) {
    Serial.println("SMS deleted successfully.");
  } else {
    Serial.println("Failed to delete SMS.");
  }
}
