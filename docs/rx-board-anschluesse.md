<!-- SPDX-License-Identifier: CC-BY-4.0 -->
<!-- Copyright 2026 FerienBSD aka Marcel Sauder -->

# RX-Board Rev A: Anschlüsse und Testpunkte

Quelle: KiCad-Platinendatei `RX-Board-Si4732.kicad_pcb` (Rev A), Netznamen und Pins direkt aus der Datei gelesen. Die Beschreibungen in der letzten Spalte sind aus den Netznamen und aus `breadboard.md` abgeleitet, nicht gemessen. Platine 44 x 30 mm, 2 Befestigungslöcher M2.5 (MH1, MH2).

## J1 RX_BUS (Stiftleiste 1x9, Raster 2.54 mm)

Pin 1 ist quadratisch. Verbindung zur Hauptplatine.

| Pin | Signal | Richtung | Kurzbeschreibung |
|---|---|---|---|
| 1 | AUDIO_L | Ausgang | Audio links vom Si4732 (Line-Pegel) |
| 2 | AUDIO_R | Ausgang | Audio rechts vom Si4732 (Line-Pegel) |
| 3 | GND | | Masse |
| 4 | 3V3 | Eingang | Versorgung, nur 3.3 V aus dem LDO, nie Akku oder 5 V |
| 5 | SDA | Ein/Aus | I2C-Daten (Pull-up liegt auf dem Board) |
| 6 | SCL | Ein/Aus | I2C-Takt |
| 7 | RST | Eingang | Reset des Si4732 |
| 8 | INT | Ausgang | Interrupt, optional |
| 9 | GND | | Masse |

## J2 FM_ANT (Stiftleiste 1x2)

| Pin | Signal | Kurzbeschreibung |
|---|---|---|
| 1 | FM_ANT | Antenne für UKW (und KW-Versuch P4), führt zum Chip-Eingang FMI. Pin 1 quadratisch |
| 2 | GND | Masse der Antenne |

## J3 AM_ANT (Stiftleiste 1x2)

| Pin | Signal | Kurzbeschreibung |
|---|---|---|
| 1 | AM_ANT | Ferritstab für MW und LW (und KW-Versuch P5), führt zum Chip-Eingang AMI. Pin 1 quadratisch |
| 2 | RFGND | Antennenmasse für den AM-Zweig |

## Testpunkte (SMD-Pad, 1.5 mm Durchmesser)

| Nr. | Signal | Kurzbeschreibung |
|---|---|---|
| TP1 | 3V3 | Versorgung, Spannung prüfen |
| TP2 | GND | Masse, Bezugspunkt für Messungen |
| TP3 | SDA | I2C-Daten |
| TP4 | SCL | I2C-Takt |
| TP5 | AUDIO_L (Beschriftung L) | Audio links |
| TP6 | AUDIO_R (Beschriftung R) | Audio rechts |
| TP7 | RST | Reset |

## Offen

* RFGND und GND: ob und wie sie auf dem Board verbunden sind, ist hier nicht geprüft.
* Pegel und Werte der Signale stehen im Datenblatt des Si4732 und in `rx-board.md`.
