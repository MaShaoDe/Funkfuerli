# Funkfüürli: provisorische Stückliste Breadboard-Test (Stand 2026-11-16, Entwurf)

Gilt für [breadboard.md](breadboard.md), ohne RX-Board. Keine Preise, Bezugsquellen erst beim Bestellen. Bestand laut [inventar.md](inventar.md), Anzahl vor dem Bestellen nachzählen.

## Vorhanden (Bestand prüfen)

| Menge | Teil | Bemerkung |
|---|---|---|
| 1 | ESP32-S3-DevKitC-1 N16R8 | Bestand prüfen |
| 1 | Display 2.0" ST7789V, 240x320 | Bestand 3 oder 4, Pinbelegung von dir |
| 1 | OLED 0.96" SSD1306 (I2C 0x3C) | Ersatz für den Si4732 am Bus |
| 1 | PAM8403 Modul HW-012 | Bestand 20 |
| 1 | Lautsprecher Visaton K 50, 8 Ω | |
| 1 | TP4056 Modul mit Schutz | |
| 1 | LiPo 103665 mit Schutz | Stecker fehlt, siehe unten |
| 1 | 18650 NCR18650B mit Halter | nur geschützt oder mit Schutzmodul |

## Zu beschaffen

| Menge | Teil | Bemerkung |
|---|---|---|
| 2 | Breadboard 830 Punkte | Display und Rest getrennt |
| 1 Set | Dupont-Drähte (m-m, m-w) | |
| 1 Set | Steckbrücken starr | |
| 1 | Drehencoder EC11 mit Taster und Knopf | |
| 1 | Klinkenbuchse 3.5 mm mit Schaltkontakt | Breakout oder THT |
| 1 | Klinkenkabel 3.5 mm für Handy | |
| 1 | Schiebeschalter | Hauptschalter |
| 1 | LDO 3.3 V, mindestens 500 mA, geringer Dropout | LF33CV oder Modul mit AP2112K-3.3, Datenblatt prüfen |
| 1 | Diode 1N5819 | Verpolschutz |
| 1 | Transistor BC337 (NPN) | Verstärkerschalter |
| 1 | Transistor BC327 (PNP) | Verstärkerschalter |
| 1 | Transistor BC337 (NPN) | Backlight, falls das Modul keinen hat |
| 1 | Ferritperle | |
| 1 | Elko 220 µF, 10 V oder mehr | |
| 1 | Elko 10 µF | LDO-Ausgang |
| 1 | Elko oder Keramik 1 µF | Audio-Kopplung |
| 6 | Keramik 100 nF | Entprellung, Teiler, LDO |
| 1 Set | Widerstände | siehe nächste Tabelle |
| 1 | LED mit Vorwiderstand | Reset-Anzeige |
| 1 | Taster | Klinken-Ersatz an GPIO 6 |
| 1 | JST-Stecker für LiPo | passend zum Akku prüfen |
| 1 | Multimeter | Strom und Spannung |
| 1 | USB-Kabel Daten | DevKit |

## Widerstände

| Menge | Wert | Zweck |
|---|---|---|
| 2 | 100 kΩ | Akku-Teiler |
| 1 | 100 kΩ | USB-Teiler oben |
| 1 | 150 kΩ | USB-Teiler unten |
| 4 | 10 kΩ | Mono-Mischer (2), Testton, Transistor-Basis |
| 2 | 10 kΩ | PNP-Basis, Reserve |
| 2 | 4.7 kΩ | I2C Pull-ups |
| 4 | 1 kΩ | Testton-Teiler, Transistor, LED |

Reserve: je 2 Stück der Werte, Wert des Backlight-Vorwiderstands nach Messung.

## Offen

* LDO-Typ nach Datenblatt festlegen.
* Display-Pinbelegung und Anschlussart prüfen.
* Stecker der Zelle prüfen (103665 ohne Stecker).
