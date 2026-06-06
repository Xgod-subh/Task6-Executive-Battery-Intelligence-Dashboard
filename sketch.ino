#define BLYNK_TEMPLATE_ID "TMPL3huinTUsY"
#define BLYNK_TEMPLATE_NAME "Executive Battery Intelligence Dashboard"
#define BLYNK_AUTH_TOKEN "EXNQHksAkUvjcGxAEObV-wikZbt5x-IS"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define POT_PIN 34

unsigned long telemetryTimer = 0;
int faultCount = 0;
String previousStatus = "";

// --------------------------------------------
// Read Battery Voltage
// --------------------------------------------

float readVoltage() {
  int adc = analogRead(POT_PIN);
  return (adc / 4095.0) * 3.3;
}

// --------------------------------------------
// Main Setup
// --------------------------------------------

void setup() {

  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Executive Battery Intelligence Dashboard Started");
}

// --------------------------------------------
// Main Loop
// --------------------------------------------

void loop() {

  Blynk.run();

  if (millis() - telemetryTimer > 1000) {

    telemetryTimer = millis();

    float cellVoltage = readVoltage();

    // Simulated 4-cell pack
    float packVoltage = cellVoltage * 4;

    int batteryHealth;
    String riskLevel;
    String systemStatus;
    String recommendation;
    String diagnostics;
    String alertLevel;

    // ----------------------------------------
    // Intelligence Engine
    // ----------------------------------------

    if (cellVoltage > 2.8) {

      batteryHealth = 95;

      riskLevel = "LOW";

      systemStatus = "NORMAL";

      recommendation =
        "Continue Monitoring";

      diagnostics =
        "All Systems Healthy";

      alertLevel = "GREEN";
    }

    else if (cellVoltage > 1.5) {

      batteryHealth = 70;

      riskLevel = "MEDIUM";

      systemStatus = "WARNING";

      recommendation =
        "Schedule Maintenance";

      diagnostics =
        "Battery Aging";

      alertLevel = "YELLOW";
    }

    else if (cellVoltage > 1.0) {

      batteryHealth = 50;

      riskLevel = "HIGH";

      systemStatus = "WARNING";

      recommendation =
        "Inspect Battery Soon";

      diagnostics =
        "Voltage Dropping";

      alertLevel = "ORANGE";
    }

    else {

      batteryHealth = 20;

      riskLevel = "CRITICAL";

      systemStatus = "FAULT";

      recommendation =
        "Immediate Inspection";

      diagnostics =
        "Critical Voltage";

      alertLevel = "RED";
    }

    // ----------------------------------------
    // Fault Counter
    // ----------------------------------------

    if (systemStatus != previousStatus &&
        systemStatus == "FAULT") {

      faultCount++;
    }

    previousStatus = systemStatus;

    // ----------------------------------------
    // Serial Monitor
    // ----------------------------------------

    Serial.println("-------------");

    Serial.print("Cell Voltage: ");
    Serial.println(cellVoltage);

    Serial.print("Pack Voltage: ");
    Serial.println(packVoltage);

    Serial.print("Health: ");
    Serial.println(batteryHealth);

    Serial.print("Risk: ");
    Serial.println(riskLevel);

    // ----------------------------------------
    // Blynk Dashboard Updates
    // ----------------------------------------

    Blynk.virtualWrite(V0, cellVoltage);

    Blynk.virtualWrite(V1, packVoltage);

    Blynk.virtualWrite(V2, batteryHealth);

    Blynk.virtualWrite(V3, riskLevel);

    Blynk.virtualWrite(V4, systemStatus);

    Blynk.virtualWrite(V5, faultCount);

    Blynk.virtualWrite(V6, recommendation);

    Blynk.virtualWrite(V7, diagnostics);

    Blynk.virtualWrite(V8, cellVoltage);

    Blynk.virtualWrite(V9, alertLevel);
  }
}