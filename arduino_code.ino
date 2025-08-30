/*
  🔆 Smart Home Lighting System
  Arduino Uno + PIR + LDR + Manual Switch

  Features:
  - Lights turn ON when motion is detected and it's dark
  - Lights turn OFF automatically when no motion is detected
  - Manual switch can override the system (force ON/OFF)
*/

#define PIR_PIN 2         // PIR motion sensor input
#define LDR_PIN A0        // LDR sensor input
#define SWITCH_PIN 3      // Manual push button
#define LIGHT_PIN 13      // Light output (LED or relay)

int ldrValue = 0;         // Store LDR reading
int motionDetected = 0;   // Store PIR state
int manualState = 0;      // Manual switch state

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP); 
  pinMode(LIGHT_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Smart Home Lighting System Started");
}

void loop() {
  // Read sensors
  ldrValue = analogRead(LDR_PIN);
  motionDetected = digitalRead(PIR_PIN);
  manualState = digitalRead(SWITCH_PIN);

  // Print debug info
  Serial.print("LDR: "); Serial.print(ldrValue);
  Serial.print(" | PIR: "); Serial.print(motionDetected);
  Serial.print(" | Switch: "); Serial.println(manualState);

  // Manual override (button pressed = force ON)
  if (manualState == LOW) {
    digitalWrite(LIGHT_PIN, HIGH);
    Serial.println("Manual Override: Light ON");
  } 
  else {
    // Auto mode: check sensors
    if (motionDetected == HIGH && ldrValue < 400) { 
      digitalWrite(LIGHT_PIN, HIGH);
      Serial.println("Motion + Dark: Light ON");
    } else {
      digitalWrite(LIGHT_PIN, LOW);
      Serial.println("No motion or enough light: Light OFF");
    }
  }

  delay(500);
}
