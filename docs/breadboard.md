# Funkfüürli: Breadboard-Verdrahtungsplan (Stand 2026-11-15, Entwurf)

Stufe 1 des Prototyps ([prototyp.md](prototyp.md)), **ohne RX-Board**. Grundlage ist der [Pinplan](pinplan.md). Die Teile stehen in [bom-breadboard.md](bom-breadboard.md), der Testsketch in `firmware/breadboard_test/`.

Alle Werte und Schaltungen hier sind Vorschläge für den Test. Was beim Messen anders wird, kommt zurück in Pinplan und Stückliste.

## Umfang

| Teil | Im Breadboard-Test | Bemerkung |
|---|---|---|
| ESP32-S3, Display, Encoder | ja | Pins nach Pinplan |
| I2C-Bus (GPIO 8, 9) und Reset (GPIO 7) | ja, mit OLED SSD1306 als Ersatz | Der Si4732 kommt erst mit dem RX-Board |
| Audio: PAM8403, Lautsprecher, Klinke | ja, mit Testton und Handy als Quelle | Ohne Radiosignal |
| Strom: TP4056, Akku, Diode, Schalter, LDO | ja, erst am Schluss | Zuerst alles über USB |
| Si4732 und Empfang | nein | Erst mit dem RX-Board (Lochraster, Stufe 2) |

## Sicherheit

* Zuerst alles über USB. Der Akku kommt erst in Schritt 7 dazu.
* Nur geschützte Zellen. Die ungeschützte 18650 nie ohne Schutzmodul ans Breadboard.
* **Nie USB und LDO gleichzeitig am 3V3-Pin.** Das DevKit hat einen eigenen Regler. Wird der Pin 3V3 vom LDO gespeist, bleibt USB am DevKit abgesteckt (Flashen vorher). Sonst arbeiten zwei Regler gegeneinander.
* Alles an GPIO verträgt höchstens 3.3 V. VBUS (5 V) und die Akkuspannung nur über Teiler.
* Erst Multimeter auf Kurzschluss (3V3 gegen GND), dann Spannung.

## Verdrahtung

Alle Verbindungen sind Drahtbrücken. GND aller Module an eine gemeinsame Schiene.

### ESP32-S3-DevKitC-1

Vom Foto geprüft (siehe [platine.md](platine.md)): Alle Pins sind über die Stiftleisten herausgeführt.

### Display 2.0" ST7789V (SPI)

Modulbeschriftung typisch, gegen dein Modul prüfen (Pinbelegung folgt von dir):

| Display-Pin (typisch) | ESP32 | Bemerkung |
|---|---|---|
| GND | GND | |
| VCC | 3V3 | |
| SCL (Takt) | GPIO 12 | SCLK |
| SDA (Daten) | GPIO 11 | MOSI |
| RES | GPIO 14 | Reset |
| DC | GPIO 13 | |
| CS | GPIO 10 | |
| BLK | siehe unten | Backlight |

Backlight: Hat das Modul einen eigenen Transistor, BLK direkt an GPIO 21. Sonst NPN (BC337) low-side: Emitter an GND, Basis über 1 kΩ an GPIO 21, Kollektor an BLK, und BLK über einen Widerstand (Wert nach Strom des Moduls, im Test messen) an 3V3. Ein/aus, kein PWM (Konzept Abschnitt 8).

### Drehencoder EC11

| Encoder | ESP32 | Bemerkung |
|---|---|---|
| A | GPIO 1 | 100 nF nach GND (Entprellung), interner Pull-up |
| B | GPIO 2 | 100 nF nach GND, interner Pull-up |
| C (Mitte) | GND | |
| Taster, Pin 1 | GPIO 42 | 100 nF nach GND, interner Pull-up |
| Taster, Pin 2 | GND | |

### I2C-Ersatz und Reset (anstelle des RX-Boards)

| Signal | ESP32 | Bemerkung |
|---|---|---|
| SDA | GPIO 8 | Pull-up 4.7 kΩ nach 3V3 |
| SCL | GPIO 9 | Pull-up 4.7 kΩ nach 3V3 |
| RST | GPIO 7 | LED mit 1 kΩ nach GND als Anzeige, später RX-Board |

OLED 0.96" SSD1306 (Adresse 0x3C) an SDA, SCL, 3V3, GND. Der I2C-Scan muss 0x3C finden. Damit ist der Bus geprüft, bevor das RX-Board kommt (dort wird die Adresse 0x11 erwartet). Die meisten OLED-Module haben schon Pull-ups, dann die externen weglassen oder parallel prüfen.

### Audio

| Von | Nach | Bemerkung |
|---|---|---|
| GPIO 15 (Testton) | 10 kΩ, dann Knoten T | Reserve-Pin, PWM 1 kHz |
| Knoten T | 1 kΩ nach GND und 100 nF nach GND | Teiler und Tiefpass, etwa 0.3 Vpp |
| Handy oder Player, Klinke L | 10 kΩ, dann Knoten M | Quelle Ersatz für den Si4732 |
| Handy oder Player, Klinke R | 10 kΩ, dann Knoten M | Mono-Mischer |
| Knoten T oder M (Jumper) | 1 µF in Reihe, dann PAM8403 L-IN | Eingang wählen. Koppel-Kondensator nur, wenn das Modul keinen hat |
| PAM8403 R-IN | offen | Mono |
| PAM8403 GND | GND | |
| PAM8403 VCC | siehe Versorgung | |
| PAM8403 L+ und L- | Lautsprecher K 50 | Minuspol nicht an Masse (BTL) |
| GPIO 6 | Taster oder Jumper nach GND | Ersatz für den Klinken-Schaltkontakt, Pull-up intern |

Der Widerstandswert des Mischers (10 kΩ) ist ein Startwert. Pegel und Eingangsimpedanz des Moduls im Test prüfen.

**Versorgung des Verstärkers:**
* 5a (erster Test): PAM8403 an 5 V von USB (Anschluss "USB" des DevKits oder Powerbank), GPIO 5 nicht benutzt.
* 5b (Schalter über GPIO 5): High-Side-Schalter mit zwei Transistoren. NPN BC337: Emitter GND, Basis über 10 kΩ an GPIO 5, Kollektor über 1 kΩ an die Basis eines PNP BC327. PNP: Emitter an Akkuspannung (nach Schottky-Diode und Schalter), Basis zusätzlich über 10 kΩ an Emitter, Kollektor an PAM8403 VCC. Das ist ein Prüfvorschlag, weil P-FETs im Durchsteckgehäuse selten Logic-Level sind. Spannungsabfall und Ruhestrom messen. Ein BC327 verträgt 500 mA, das reicht für das Modul bei Zimmerlautstärke.

### Strom (erst ab Schritt 7)

Kette: USB, TP4056, Akku, Schottky-Diode 1N5819, Hauptschalter, Ferritperle und Elko, LDO 3.3 V, 3V3-Pin des DevKits.

| Verbindung | Bemerkung |
|---|---|
| Micro-USB, TP4056 | Laden nur bei ausgeschaltetem Gerät (Schalter aus) |
| TP4056 B+ und B- | LiPo 103665 mit Schutzplatine (JST) |
| TP4056 B+ | Anode 1N5819, Kathode zum Hauptschalter |
| Hauptschalter | zum Ferritpärchen, dann 220 µF Elko und 100 nF nach GND |
| LDO 3.3 V (Eingang, Ausgang, GND) | 100 nF am Ein- und Ausgang, ausserdem Elko 10 µF am Ausgang |
| LDO-Ausgang | Pin 3V3 des DevKits (USB abgesteckt) |

LDO: braucht mindestens 500 mA und kleine Dropout-Spannung (Entscheid 1 in [platine.md](platine.md)). Für das Breadboard am einfachsten ein fertiges Modul mit AP2112K-3.3 oder ein LF33CV (TO-220), Datenblatt vor dem Einsatz prüfen. Ein MCP1700 reicht nicht, ein AMS1117 hat zu viel Spannungsabfall.

Messteiler an den ADC-Eingängen:

| Signal | Teiler | ESP32 | Bemerkung |
|---|---|---|---|
| Akkuspannung | 100 kΩ von Akku plus nach GPIO 4, 100 kΩ von GPIO 4 nach GND, 100 nF am Pin | GPIO 4 (ADC1) | 4.2 V ergibt 2.1 V |
| USB-Erkennung (VBUS) | 100 kΩ von VBUS nach GPIO 17, 150 kΩ von GPIO 17 nach GND | GPIO 17 | 5 V ergibt 3.0 V |
| Ladestatus CHRG | TP4056 CHRG-Pin nach GPIO 16 | GPIO 16 | Open-Collector, interner Pull-up, Low heisst laden |

## Testablauf

Jeweils erst weiter, wenn der Schritt läuft. Die Befehle gehören zum Testsketch.

| Schritt | Was | Erwartung | Ergebnis |
|---|---|---|---|
| 1 | ESP32 allein über USB, Sketch flashen, serieller Monitor (115200) | Menü erscheint | |
| 2 | Display: Befehl `d` | Farbfläche und Text, 240x320 | |
| 3 | Encoder: Befehl `e` | Drehen und Klick als Ausgabe, ohne Prellen | |
| 3a | I2C: Befehl `i` mit OLED | Adresse 0x3C | |
| 3b | Reset: Befehl `r` | LED blinkt kurz | |
| 4 | Si4732 | entfällt, kommt mit dem RX-Board | |
| 5a | Audio: Befehl `t` | 1 kHz Ton aus dem Lautsprecher | |
| 5b | Handy über Klinke | Musik hörbar, Mono-Mischer prüfen | |
| 5c | Schalter über GPIO 5: Befehl `p` | Verstärker ein und aus, Ruhestrom messen | |
| 5d | Klinken-Ersatz: Befehl `j` | Pegel wechselt beim Jumper | |
| 6 | Menü und Lautstärke | später mit Firmware aus dem Fork | |
| 7a | Strom über USB messen (ohne und mit Display, ohne und mit Verstärker) | Werte notieren | |
| 7b | LDO-Kette aufbauen, USB am DevKit abstecken, Akku anschliessen | 3V3 am Pin | |
| 7c | Befehl `a` | Akkuspannung stimmt mit Multimeter | |
| 7d | Entladekurve und Spannung, ab der der LDO nicht mehr regelt | Dropout mit Schottky-Diode (etwa 0.3 V) | |
| 8 | Pinplan korrigieren | Abweichungen vom Fork notieren | |

Weiter zu Stufe 2 (Lochraster), wenn Display, Encoder, I2C, Ton über Lautsprecher und die Stromkette laufen.

## Grenzen

* Lange Kabel und die Federkontakte machen SPI und Audio störanfällig. Ein Fehler hier ist kein Beweis gegen das Konzept.
* Empfang auf MW und KW und der Störtest sind auf dem Breadboard nicht aussagekräftig und ohne RX-Board nicht möglich.
* Kein Falltest.

## Messprotokoll

| Messung | Wert | Datum | Bemerkung |
|---|---|---|---|
| Strom ESP32 allein (USB) | | | |
| Strom mit Display (Backlight ein) | | | |
| Strom mit Display (Backlight aus) | | | |
| Strom mit Verstärker (Ruhe) | | | |
| Strom mit Verstärker (Zimmerlautstärke) | | | |
| Ruhestrom Verstärker über Schalter (GPIO 5 aus) | | | |
| Spannungsabfall Schottky-Diode bei 150 mA | | | |
| Dropout LDO (Akkuspannung, ab der 3.3 V fallen) | | | |
| Akkuspannung ADC gegen Multimeter | | | |

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
