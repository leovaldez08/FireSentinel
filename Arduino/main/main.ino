#define FLAME_SENSOR_PIN 6  
#define MQ135_PIN A1        
#define SOIL_MOISTURE_PIN A0 
#define RED_LED_PIN 3       
#define BUZZER_PIN 7   

#define FLAME_THRESHOLD LOW  
#define AIR_QUALITY_THRESHOLD 500
#define SOIL_MOISTURE_THRESHOLD 500 

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pin modes
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Turn off LED and buzzer initially
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  // Read sensor values
  int flameDetected = digitalRead(FLAME_SENSOR_PIN);
  int airQuality = analogRead(MQ135_PIN);
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);

  // Print sensor values to Serial Monitor
  Serial.print("Flame Detected: ");
  Serial.println(flameDetected == FLAME_THRESHOLD ? "YES" : "NO");
  Serial.print("Air Quality: ");
  Serial.println(airQuality);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);
  Serial.println("-------------------");

  // Check for flame detection
  if (flameDetected == FLAME_THRESHOLD) {
    // Trigger alert (LED and buzzer)
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("ALERT: Flame Detected!");
  } else {
    // Turn off alert
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Optional: Add checks for air quality and soil moisture
  if (airQuality > AIR_QUALITY_THRESHOLD) {
    Serial.println("Warning: Poor Air Quality Detected!");
  }
  if (soilMoisture < SOIL_MOISTURE_THRESHOLD) {
    Serial.println("Warning: Low Soil Moisture Detected!");
  }

  // Delay before next reading
  delay(1000);
}