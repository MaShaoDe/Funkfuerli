// Funkfuerli Breadboard-Test ohne RX-Board.
// Nicht kompiliert, im Test pruefen. Arduino-ESP32 Core 3.x,
// Bibliotheken: Adafruit GFX, Adafruit ST7789.
// Befehle ueber den seriellen Monitor (115200):
// d Display, e Encoder, i I2C-Scan, r Reset-Puls, t Testton, p Verstaerker,
// j Klinke, a Akku und USB, h Hilfe
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "pins.h"

// Software-SPI, damit GPIO 13 (DC) nicht mit dem Standard-MISO kollidiert
Adafruit_ST7789 tft(PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_MOSI, PIN_TFT_SCLK, PIN_TFT_RST);

static bool ampOn = false;
static bool toneOn = false;
static bool encMode = false;
static uint8_t lastAB = 0;
static int encPos = 0;

void help() {
  Serial.println(F("d Display, e Encoder an/aus, i I2C-Scan, r Reset-Puls"));
  Serial.println(F("t Testton an/aus, p Verstaerker an/aus, j Klinke, a Akku/USB"));
}

void testDisplay() {
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_RED);   delay(400);
  tft.fillScreen(ST77XX_GREEN); delay(400);
  tft.fillScreen(ST77XX_BLUE);  delay(400);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(10, 10);
  tft.print("Funkfuerli");
  pinMode(PIN_TFT_BL, OUTPUT);
  digitalWrite(PIN_TFT_BL, HIGH);
  Serial.println(F("Display: Farben und Text sichtbar?"));
}

void scanI2C() {
  Serial.println(F("I2C-Scan:"));
  int n = 0;
  for (uint8_t a = 1; a < 127; a++) {
    Wire.beginTransmission(a);
    if (Wire.endTransmission() == 0) {
      Serial.printf("  0x%02X\n", a);
      n++;
    }
  }
  if (!n) Serial.println(F("  nichts gefunden"));
}

void resetPulse() {
  digitalWrite(PIN_SI_RESET, LOW);
  delay(200);
  digitalWrite(PIN_SI_RESET, HIGH);
  Serial.println(F("Reset-Puls gesendet"));
}

void toggleTone() {
  toneOn = !toneOn;
  if (toneOn) ledcWriteTone(PIN_TONE, 1000);
  else ledcWriteTone(PIN_TONE, 0);
  Serial.println(toneOn ? F("Ton an (1 kHz)") : F("Ton aus"));
}

void toggleAmp() {
  ampOn = !ampOn;
  digitalWrite(PIN_AMP_EN, ampOn ? HIGH : LOW);
  Serial.println(ampOn ? F("Verstaerker an") : F("Verstaerker aus"));
}

void readPower() {
  uint32_t mv = analogReadMilliVolts(PIN_VBAT);
  Serial.printf("Akku: Pin %lu mV, Akku ca. %lu mV (Teiler 1:2)\n",
                (unsigned long)mv, (unsigned long)(mv * 2));
  uint32_t usb = analogReadMilliVolts(PIN_VBUS);
  Serial.printf("USB-Pin: %lu mV, USB %s\n", (unsigned long)usb,
                usb > 1500 ? "vorhanden" : "nicht vorhanden");
  Serial.printf("CHRG: %s\n", digitalRead(PIN_CHRG) ? "hoch (nicht laden)" : "tief (laedt)");
}

void pollEncoder() {
  uint8_t ab = (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B);
  if (ab != lastAB) {
    // einfache Auswertung, Raster des EC11 beachten, im Test anpassen
    if (lastAB == 0b11 && ab == 0b01) { encPos++; Serial.printf("Encoder %d\n", encPos); }
    if (lastAB == 0b11 && ab == 0b10) { encPos--; Serial.printf("Encoder %d\n", encPos); }
    lastAB = ab;
  }
  static bool lastBtn = true;
  bool b = digitalRead(PIN_ENC_BTN);
  if (b != lastBtn) {
    lastBtn = b;
    Serial.println(b ? F("Taste los") : F("Taste gedrueckt"));
    delay(5);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Wire.begin(PIN_SDA, PIN_SCL);
  pinMode(PIN_SI_RESET, OUTPUT);
  digitalWrite(PIN_SI_RESET, HIGH);
  pinMode(PIN_AMP_EN, OUTPUT);
  digitalWrite(PIN_AMP_EN, LOW);
  pinMode(PIN_JACK, INPUT_PULLUP);
  pinMode(PIN_ENC_A, INPUT_PULLUP);
  pinMode(PIN_ENC_B, INPUT_PULLUP);
  pinMode(PIN_ENC_BTN, INPUT_PULLUP);
  pinMode(PIN_CHRG, INPUT_PULLUP);
  pinMode(PIN_VBUS, INPUT);
  ledcAttach(PIN_TONE, 1000, 8);
  lastAB = (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B);
  Serial.println(F("Funkfuerli Breadboard-Test"));
  help();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case 'd': testDisplay(); break;
      case 'e': encMode = !encMode; Serial.println(encMode ? F("Encoder an") : F("Encoder aus")); break;
      case 'i': scanI2C(); break;
      case 'r': resetPulse(); break;
      case 't': toggleTone(); break;
      case 'p': toggleAmp(); break;
      case 'j': Serial.println(digitalRead(PIN_JACK) ? F("Klinke: offen (hoch)") : F("Klinke: Kontakt (tief)")); break;
      case 'a': readPower(); break;
      case 'h': help(); break;
      default: break;
    }
  }
  if (encMode) pollEncoder();
}
