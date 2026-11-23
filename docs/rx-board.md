<!-- SPDX-License-Identifier: CC-BY-4.0 -->
<!-- Copyright 2026 FerienBSD aka Marcel Sauder -->

# RX-Board im Funkfüürli

Alle Details zum RX-Board (Schaltung, Pinbelegung von J1, J2, J3, Testpunkte, Stückliste, Tests) stehen im Repo [RX-Board-Si4732](https://github.com/MaShaoDe/RX-Board-Si4732), dort vor allem in [docs/rx-board.md](https://github.com/MaShaoDe/RX-Board-Si4732/blob/main/docs/rx-board.md). Diese Seite beschreibt nur die Rolle im Funkfüürli und die Verdrahtung mit der Hauptplatine.

## Aufgabe im Gerät

Das RX-Board ist der Empfänger: Antennensignal rein, Ton links und rechts raus, Steuerung per I2C. Es steckt über J1 auf der Hauptplatine (Projektdefinition T1, T8).

## Verdrahtung mit der Hauptplatine

| RX-Board-Signal | Ziel im Funkfüürli |
|---|---|
| AUDIO_L, AUDIO_R | Verstärker PAM8403 und Klinke (Mono über zwei gleiche Widerstände, Jumper Mono/Stereo) |
| 3V3 | 3.3 V aus dem LDO, nie Akku oder 5 V |
| GND (zwei Pins) | Masse |
| SDA, SCL | I2C des ESP32-S3, GPIO 8 und 9 |
| RST | GPIO 7 |
| INT | offen, nur bei Bedarf der Firmware |

Welcher J1-Pin welches Signal führt, steht im RX-Board-Repo. Die Buchsenleiste der Hauptplatine muss dieser Reihenfolge folgen, Pin 1 ist markiert.

## Antennen

* J2: Teleskopantenne (UKW), über BNC am Gehäuse und dünnes 50-Ohm-Koax (Projektdefinition T4).
* J3: Ferritstab für MW und LW.
* Die Antennen gehen direkt an das RX-Board, nicht über die Hauptplatine.
* Ferritstab und Antennenleitungen möglichst weit weg von ESP32, Display und Verstärker.
