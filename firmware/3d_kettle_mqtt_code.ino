#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <math.h>

// DS18B20 data pin
#define ONE_WIRE_BUS 4

// Relay control pin
#define RELAY_PIN 18

// Assumes an active-LOW relay module
const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;

// Temperature hysteresis: 1 degree C
const float HYSTERESIS_C = 1.0;

// Wi-Fi details
const char* WIFI_SSID = "Oneplus13s";
const char* WIFI_PASSWORD = "Dhanush1760";

// Computer IPv4 address running Mosquitto
const char* MQTT_SERVER = "10.46.137.194";
const int MQTT_PORT = 1883;

// MQTT topics
const char* TEMP_TOPIC = "kettle/temperature";
const char* SETPOINT_TOPIC = "kettle/setpoint";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long lastPublish = 0;
const unsigned long PUBLISH_INTERVAL_MS = 1000;

// Initial setpoint
float setpointC = 60.0;
bool setpointReceived = false;

// Relay starts OFF
bool heaterOutput = false;

// Receive setpoint from Unity
void mqttCallback(char* topic, byte* payload,
                  unsigned int length) {
  if (strcmp(topic, SETPOINT_TOPIC) == 0) {
    char message[32];

    if (length == 0 || length >= sizeof(message)) {
      Serial.println("Invalid setpoint message length");
      return;
    }

    memcpy(message, payload, length);
    message[length] = '\0';

    char* endPtr;
    float receivedSetpoint = strtof(message, &endPtr);

    if (endPtr == message || *endPtr != '\0' ||
        !isfinite(receivedSetpoint) ||
        receivedSetpoint < 30.0 ||
        receivedSetpoint > 100.0) {
      Serial.println("Invalid setpoint; expected 30-100 C");
      return;
    }

    setpointC = receivedSetpoint;
    setpointReceived = true;

    Serial.print("New setpoint received: ");
    Serial.print(setpointC, 1);
    Serial.println(" C");
  }
}

void connectWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

bool connectMQTT() {
  if (mqttClient.connected()) {
    return true;
  }

  String clientId = "KettleESP32-" +
                    String((uint32_t)ESP.getEfuseMac(), HEX);

  Serial.print("Connecting to MQTT... ");

  if (mqttClient.connect(clientId.c_str())) {
    Serial.println("connected");

    if (mqttClient.subscribe(SETPOINT_TOPIC)) {
      Serial.println("Subscribed to kettle/setpoint");
    } else {
      Serial.println("Setpoint subscription failed");
    }

    return true;
  }

  Serial.print("Failed, MQTT state = ");
  Serial.println(mqttClient.state());
  return false;
}

// ON/OFF controller with hysteresis
void controlRelay(float temperatureC) {
  if (temperatureC <= setpointC - HYSTERESIS_C) {
    heaterOutput = true;
  }
  else if (temperatureC >= setpointC) {
    heaterOutput = false;
  }

  digitalWrite(
    RELAY_PIN,
    heaterOutput ? RELAY_ON : RELAY_OFF
  );
}

void setup() {
  Serial.begin(115200);

  // Initialize relay safely in OFF state
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  sensors.begin();

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
  mqttClient.setBufferSize(256);

  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqttClient.connected()) {
    if (!connectMQTT()) {
      // Keep relay OFF while MQTT is disconnected
      heaterOutput = false;
      digitalWrite(RELAY_PIN, RELAY_OFF);
      delay(2000);
      return;
    }
  }

  // Process setpoint messages from Unity
  mqttClient.loop();

  if (millis() - lastPublish >= PUBLISH_INTERVAL_MS) {
    lastPublish = millis();

    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);

    if (temperatureC == DEVICE_DISCONNECTED_C ||
        !isfinite(temperatureC)) {
      // Sensor error: turn relay OFF
      heaterOutput = false;
      digitalWrite(RELAY_PIN, RELAY_OFF);

      Serial.println(
        "DS18B20 sensor error - Relay OFF"
      );
      return;
    }

    // Execute ON/OFF controller
    controlRelay(temperatureC);

    // Publish actual temperature to Unity
    char payload[16];
    snprintf(payload, sizeof(payload), "%.2f",
             temperatureC);

    if (mqttClient.publish(TEMP_TOPIC, payload)) {
      Serial.print("Actual temperature: ");
      Serial.print(temperatureC, 2);

      Serial.print(" C | Setpoint: ");
      Serial.print(setpointC, 1);

      Serial.print(" C | Relay: ");
      Serial.print(heaterOutput ? "ON" : "OFF");

      if (setpointReceived) {
        Serial.println(" | Setpoint received from Unity");
      } else {
        Serial.println(" | Using default setpoint");
      }
    } else {
      Serial.println("Temperature MQTT publish failed");
    }
  }
}