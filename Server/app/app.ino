#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Arduino Cloud variables
float temperature;
float humidity;
int airQuality;
int soilMoisture;
bool flameDetected;
bool alert;

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi connected");

  // Initialize Arduino Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop() {
  ArduinoCloud.update();

  // Read data from Arduino Uno via Serial
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    int values[5];
    int index = 0;
    char* token = strtok((char*)data.c_str(), ",");
    while (token != NULL && index < 5) {
      values[index++] = atoi(token);
      token = strtok(NULL, ",");
    }

    // Assign values to variables
    temperature = values[0];
    humidity = values[1];
    airQuality = values[2];
    soilMoisture = values[3];
    flameDetected = values[4];

    // Check for fire risk
    if (flameDetected || airQuality > 500 || temperature > 40) {
      alert = true;
    } else {
      alert = false;
    }
  }

  delay(1000); // Wait 1 second before next reading
}

void initProperties() {
  ArduinoCloud.addProperty(temperature, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(humidity, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(airQuality, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(soilMoisture, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(flameDetected, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(alert, READ, ON_CHANGE, NULL);
}