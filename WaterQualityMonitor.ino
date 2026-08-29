#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// --- Configuration ---
// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak settings
unsigned long myChannelNumber = 0; // Replace 0 with your ThingSpeak Channel ID (e.g., 1234567)
const char * myWriteAPIKey = "YOUR_WRITE_API_KEY";

// --- Pin Definitions ---
const int turbidityPin = A0; // Analog pin for Turbidity Sensor

// L293D Motor Driver pins
// We need two pins to control the motor direction (and thus turning it on/off)
const int motorPin1 = D1; // Input 1 on L293D
const int motorPin2 = D2; // Input 2 on L293D

// --- Thresholds ---
// Define the threshold for turbidity. 
// Note: You will need to calibrate this value based on your specific sensor.
// Depending on the sensor, lower voltage might mean higher turbidity.
// Adjust the condition in the loop() accordingly.
const int turbidityThreshold = 500; // Example threshold value

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  // Ensure motor is off initially
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // 1. Read Turbidity Sensor
  int sensorValue = analogRead(turbidityPin);
  
  // Convert analog value to voltage or NTU based on calibration.
  // For simplicity, we use the raw analog value (0-1023).
  // A typical sensor might give a lower voltage (lower analog reading) for higher turbidity.
  // For this logic, we assume higher sensorValue = higher turbidity.
  // Please adjust this logic based on your specific sensor's characteristics.
  
  Serial.print("Turbidity Sensor Value: ");
  Serial.println(sensorValue);

  // 2. Control Motor based on threshold
  int motorStatus = 0; // 0 for OFF, 1 for ON
  
  // If your sensor works opposite (lower value = more turbid), change '>' to '<'
  if (sensorValue > turbidityThreshold) {
    Serial.println("High turbidity detected! Activating purification motor...");
    // Turn motor ON (Forward direction)
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    motorStatus = 1;
  } else {
    Serial.println("Water is clear. Motor is OFF.");
    // Turn motor OFF
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    motorStatus = 0;
  }

  // 3. Send Data to ThingSpeak
  // Set the fields with the values
  ThingSpeak.setField(1, sensorValue); // Field 1: Turbidity Level
  ThingSpeak.setField(2, motorStatus); // Field 2: Motor Status (1 = ON, 0 = OFF)

  // Write to ThingSpeak.
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // Wait 20 seconds to update the channel again
  // ThingSpeak requires a minimum 15-second delay between updates on the free tier
  delay(20000);
}
