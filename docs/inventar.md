# Funkfüürli: Inventar und Einstufung (Stand 2026-11-13)

Vorhandene Teile für Prototyp und Kurs. Leere Stückzahl heisst: noch zu prüfen.

Einstufung: A = Basis, B = Reserve oder Prototyp, C = Test, D = nicht verwendbar.

## Mikrocontroller-Module

| Nr | Bezeichnung | Chip | Stück | Einstufung | Bemerkung |
|---|---|---|---|---|---|
| 1 | ESP32-S3-DevKitC-1, N16R8, Dual Type-C, 44 Pins | ESP32-S3 | | A | Stückzahl und Masse prüfen |
| 2 | ESP32-S3-DevKitC-1 (Variante unklar) | ESP32-S3 | | B | Aufdruck auf dem Schirm prüfen |
| 3 | ESP32-S3 mit Erweiterungsadapter, N8R2 oder N16R8, CP2102 | ESP32-S3 | | B | N8R2 knapp (8 MB Flash) |
| 4 | ESP32-WROOM-32, 38 Pins | ESP32 klassisch | | C | A2DP-Versuch |
| 5 | ESP32-WROOM-32D | ESP32 klassisch | | C | A2DP-Versuch |
| 6 | ESP32 Board 30/38 Pins, CH340C oder CP2102 | ESP32 klassisch | | C | Evtl. identisch mit Nr 4 oder 5 |
| 7 | ESP32 DevKitC mit Antenne optional | ESP32 klassisch | | C | Evtl. identisch mit Nr 4 bis 6 |
| 8 | T-Display 1.14" | ESP32 klassisch | | C | Nur Experiment, Display fest verbaut |
| 9 | ESP32-C3 SuperMini, unverlötet | ESP32-C3 | | D | Fork braucht den S3 |
| 10 | ESP32-C3 mit 0.42" OLED | ESP32-C3 | 4 | D | C3, winziges Display |
| 11 | ESP32-C6, Dual Type-C | ESP32-C6 | | D | Fork braucht den S3 |
| 12 | ESP32-C2 im D1-mini-Format | ESP32-C2 | | D | Fork braucht den S3 |
| 13 | Heltec Wireless Paper (E-Paper, LoRa) | ESP32-S3FN8 | | D | Kein PSRAM, Display und LoRa fest |
| 14 | Heltec LoRa 32 V3 (0.96" OLED, SX1262) | ESP32-S3 | 1 | D | Display und LoRa fest |

## Displays

| Nr | Bezeichnung | Treiber | Stück | Einstufung | Bemerkung |
|---|---|---|---|---|---|
| 15 | 2.0" TFT 240x320, SPI | ST7789V | 4 | A | Prüfen, ob 3 oder 4. Pins und Stiftleiste klären |
| 16 | 0.96" OLED 128x64, I2C | SSD1306 | 2 plus weitere | B | Prototyp |
| 17 | 1.3" OLED 128x64, I2C | SH1107 | 2 | B | Prototyp, anderer Treiber |
| 18 | 0.91" OLED 128x32, I2C | SSD1306 | 18 | D | Zu klein |
| 19 | 0.66" OLED 64x48, Shield für D1 mini | SSD1306 | 4 | D | Zu klein |
| 20 | 2.8" TFT 240x320 mit Touch | unklar | | C | Klären: nur Display oder Board mit ESP32 |

## Strom

| Nr | Bezeichnung | Stück | Einstufung | Bemerkung |
|---|---|---|---|---|
| 21 | LiPo 103665, 3.7 V, 3000 mAh (11.1 Wh), mit Schutzplatine | 10, nachbestellbar | A | Stecker fehlt (Aderendhülsen), Aufdrucke der Schutzplatine lesen |
| 22 | NCR18650B (3400 mAh laut Typ), ungeschützt | | A | Kapazität messen, Schutz auf der Platine nötig |
| 23 | Halter für 1 x 18650, offener Rahmen, Federkontakte, Lötfahnen | | A | Masse nachmessen |
| 24 | 14500 (AA-Format), 800 mAh, 3.7 V (2.96 Wh), vermutlich ungeschützt | mindestens 4 | B | Zu wenig Kapazität für den Standard, Reserve, Verwechslungsgefahr mit AA |
| 25 | TP4056-Lademodul mit Schutz, Micro-USB | | A | Prototyp, später USB-C oder eigene Schaltung |
| 26 | Schaltlader mit Induktivität und I2C | | D | Nicht im Gerät (Störungen) |
| 27 | Spannungsregler | | offen | Typ klären |

## Audio

| Nr | Bezeichnung | Stück | Einstufung | Bemerkung |
|---|---|---|---|---|
| 28 | PAM8403-Modul HW-012 mit Lautstärkepoti | 20 | A | Prototyp und Kurssatz |
| 29 | Lautsprecher mit Gehäuse und 4 Befestigungsohren | 2 | B | Variante mit mehr Bass, Ohm, Watt und Masse noch klären |
| 30 | Visaton K 50 (Art. 2901), 8 Ohm, 2 W, 50 x 17 mm | mindestens 1 | A | Standard-Lautsprecher, kommt aus einem Bausatz, Stückzahl prüfen |

## Noch zu beschaffen
* Si4732-Modul oder Chip (Variante im Datenblatt prüfen)
* Drehencoder, Klinkenbuchse mit Schaltkontakt, BNC-Buchse, Teleskopantenne, Ferritstab
* JST-Stecker für den LiPo, Stiftleisten und Jumper
