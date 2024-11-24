
// Define the solenoid pins and sensor pins
#define S1 5  // Upper inlet solenoid
#define S2 6 // Lower inlet solenoid
#define S3 7 // Lower outlet solenoid
#define S4 8 // Lower outlet solenoid

#define L1 1 // Upper level sensor
#define L2 2 // Upper level sensor
#define L3 3 // Lower level sensor
#define L4 4 // Lower level sensor

#define HEAT_SENSOR 9 // Temperature sensor input (1 for hot)

void setup() {
  // Initialize the solenoid pins as outputs
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S4, OUTPUT);
  
  // Initialize the sensor pins as inputs
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);
  pinMode(HEAT_SENSOR, INPUT);
  
  // Set initial states for solenoids (Closed)
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  digitalWrite(S4, LOW);

  Serial.begin(9600); // Start serial communication for monitoring
}

void loop() {
  // Read sensor values
  int l1 = digitalRead(L1);
  int l2 = digitalRead(L2);
  int l3 = digitalRead(L3);
  int l4 = digitalRead(L4);
  int heatStatus = digitalRead(HEAT_SENSOR);
  
  // Check if the tank is empty (L1 or L2 and L3 or L4 are 0)
  if ((l1 == 0 || l2 == 0) && (l3 == 0 || l4 == 0)) {
    // Open upper and lower inlets (S1, S2) and close outlets (S3, S4)
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, LOW);
    digitalWrite(S4, LOW);
    Serial.println("Inlets are open, outlets are closed.");
  }
  
  // Check if the tank is full (L1, L2, L3, L4 are all 1)
  if (l1 == 1 && l2 == 1 && l3 == 1 && l4 == 1) {
    // Close all solenoids
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    digitalWrite(S4, LOW);
    Serial.println("All solenoids are closed, tank is full.");
  }
  
  // Second step: Activate valves S2, S3, S4 when heat is detected
  if (heatStatus == 1 && l1 == 1 && l2 == 1 && l3 == 1 && l4 == 1) {
    // Open S2 (lower inlet), S3, and S4 (lower outlets)
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    digitalWrite(S4, HIGH);
    Serial.println("Heat detected, activating S2, S3, S4.");
  }
  
  // After water is emptied, cycle activation as required
  if (l1 == 0 && l2 == 0 && l3 == 0 && l4 == 0 && heatStatus == 0) {
    // Reset solenoids for another cycle
    digitalWrite(S1, HIGH); // Open upper inlet
    digitalWrite(S2, HIGH); // Open lower inlet
    digitalWrite(S3, LOW);  // Close outlets
    digitalWrite(S4, LOW);  // Close outlets
    Serial.println("Tank is empty, resetting cycle.");
  }

  delay(1000); // Short delay for monitoring
}
