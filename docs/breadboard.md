# Funkfüürli: Breadboard-Verdrahtungsplan (Stand 2026-11-19, Entwurf)

Stufe 1 des Prototyps ([prototyp.md](prototyp.md)). Alles ausser dem Empfänger lässt sich sofort testen, das **RX-Board Rev A** (UKW, MW, LW, ohne KW) kommt dazu, sobald es geliefert ist. Grundlage ist der [Pinplan](pinplan.md). Die Teile stehen in [bom-breadboard.md](bom-breadboard.md), der Testsketch in `firmware/breadboard_test/`. Das RX-Board ist im Repo [RX-Board-Si4732](https://github.com/MaShaoDe/RX-Board-Si4732) beschrieben.

Alle Werte und Schaltungen hier sind Vorschläge für den Test. Was beim Messen anders wird, kommt zurück in Pinplan und Stückliste.

## Umfang

| Teil | Im Breadboard-Test | Bemerkung |
|---|---|---|
| ESP32-S3, Display, Encoder | ja | Pins nach Pinplan |
| I2C-Bus (GPIO 8, 9) und Reset (GPIO 7) | ja, zuerst mit OLED SSD1306, dann mit dem RX-Board | Si4732 antwortet auf 0x11 |
| Audio: PAM8403, Lautsprecher, Klinke | ja, mit Testton und Handy als Quelle | Ohne Radiosignal |
| Strom: TP4056, Akku, Diode, Schalter, LDO | ja, erst am Schluss | Zuerst alles über USB |
| Si4732 und Empfang UKW, MW (LW) | ja, mit RX-Board Rev A | Ab Lieferung |
| Empfang KW | ja, als Test P4 und P5 | Rev A hat keinen KW-Zweig. Zwei Wege: Antenne an J2 (FMI) oder Zusatzschaltung an J3 (AMI), siehe unten |

## Sicherheit

* Zuerst alles über USB. Der Akku kommt erst in Schritt 7 dazu.
* Nur geschützte Zellen. Die ungeschützte 18650 nie ohne Schutzmodul ans Breadboard.
* **Nie USB und LDO gleichzeitig am 3V3-Pin.** Das DevKit hat einen eigenen Regler. Wird der Pin 3V3 vom LDO gespeist, bleibt USB am DevKit abgesteckt (Flashen vorher). Sonst arbeiten zwei Regler gegeneinander.
* Alles an GPIO verträgt höchstens 3.3 V. VBUS (5 V) und die Akkuspannung nur über Teiler.
* Erst Multimeter auf Kurzschluss (3V3 gegen GND), dann Spannung.
* RX-Board zuerst ohne Antenne und ohne Audioleitung anschliessen, erst I2C prüfen, dann Antenne und Ton.
* **Keine LED am Reset-Pin, wenn das RX-Board dranhängt.** Das RX-Board hat einen 4.7-kΩ-Pull-up am Reset. Eine LED mit 1 kΩ gegen GND zieht RST auf etwa 0.6 V, der Chip bleibt dauernd im Reset.

## Verdrahtung

Alle Verbindungen sind Drahtbrücken. GND aller Module an eine gemeinsame Schiene.

### Pin-Übersicht (alle GPIO des Breadboard-Tests)

| GPIO | Ziel | Hinweis |
|---|---|---|
| 1 | Encoder A | |
| 2 | Encoder B | |
| 4 | Akkuspannung (ADC1) über Teiler | ab Schritt 7 |
| 5 | Verstärker-Versorgung ein/aus | optional, Schritt 5c |
| 6 | Klinken-Ersatz (Taster nach GND) | |
| 7 | RST (OLED-Ersatz-LED, dann RX-Board J1 Pin 7) | LED abklemmen, sobald das RX-Board steckt |
| 8 | SDA (OLED 0x3C und RX-Board J1 Pin 5) | |
| 9 | SCL (OLED und RX-Board J1 Pin 6) | |
| 10 | Display CS | |
| 11 | Display MOSI | |
| 12 | Display SCLK | |
| 13 | Display DC | |
| 14 | Display RST | |
| 15 | Testton (nur Test) | Im Basisboard als I2S-Reserve vorgesehen, hier nur für den Test |
| 16 | Lader CHRG | ab Schritt 7 |
| 17 | USB-Erkennung über Teiler | ab Schritt 7 |
| 21 | Display Backlight | |
| 42 | Encoder Taster | |
| 3V3, GND | RX-Board J1 Pin 4, Pin 3 und 9 | 3V3 vom DevKit, später vom LDO |

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

### RX-Board Rev A (ab Lieferung)

Das Board kommt voll bestückt. Die Stiftleisten J1 (1x9), J2 (1x2, FM) und J3 (1x2, AM) werden von Hand angelötet, Pin 1 ist quadratisch und bei J1 oben. Pinbelegung und Werte stehen im RX-Board-Repo (`docs/rx-board.md`).

| J1 Pin | Signal | Verbindung am Breadboard | Bemerkung |
|---|---|---|---|
| 1 | AUDIO_L | über 22 kΩ an Knoten M (Mischer) | statt Handy, nie beides gleichzeitig |
| 2 | AUDIO_R | über 22 kΩ an Knoten M | Mono-Mischer |
| 3 | GND | GND | |
| 4 | 3V3 | 3V3 des DevKits | nur 3.3 V, nie Akku oder 5 V |
| 5 | SDA | GPIO 8 | Pull-up 4.7 kΩ liegt auf dem Board, externe weglassen |
| 6 | SCL | GPIO 9 | |
| 7 | RST | GPIO 7 | LED und Pull-up am Breadboard entfernen |
| 8 | INT | offen | nicht nötig |
| 9 | GND | GND | |

| Anschluss | Pins | Antenne |
|---|---|---|
| J2 (FM_ANT) | 1 Antenne, 2 GND | Teleskopantenne für UKW |
| J3 (AM_ANT) | 1 Antenne, 2 RFGND | Ferritstab (180 bis 450 µH) für MW und LW |

Anordnung: Ferritstab und Antennenleitungen möglichst weit von ESP32, Display und Verstärker (mindestens eine Handbreit), sonst fängt das Radio nur Störungen auf.

Start des Chips (nach AN332): Spannung anlegen, Reset kurz auf Low, dann POWER_UP mit XOSCEN = 1 und OPMODE = 0x05 (analoger Ausgang), danach mindestens 500 ms warten, bevor der erste Abstimmbefehl kommt. Der Chip-Test (POWER_UP mit FUNC = 15) gibt die Teilenummer zurück.

### Kurzwelle an Rev A (Tests P4 und P5)

Rev A hat keinen KW-Zweig. Beide Wege kosten keinen Umbau am Board. Der Chip hört KW von 2.3 bis 26.1 MHz (Kurzdatenblatt Si4732-A10). Welcher Chip-Eingang bei KW der richtige ist, ist aus den Unterlagen nicht eindeutig (siehe RX-Board-Pflichtenheft, Abschnitt 3). Darum werden beide probiert.

**P4: KW an J2 (FMI).** Teleskopantenne oder 5 m Draht an J2 statt der UKW-Antenne, KW-Band abstimmen. Keine weiteren Teile.

**P5: KW an J3 (AMI) mit Zusatzschaltung nach AN383, Abschnitt 10.** Kleine Lochrasterplatte mit Stiftleiste, die auf J3 steckt (Ferritstab dafür abnehmen):

```
Antenne (Teleskop oder Draht) --- L1 4.7 uH --- J3 Pin 1 (AMI-Knoten)
J3 Pin 1 --- C3 33 pF --- Spule 220 uH --- J3 Pin 2 (GND)
```

* L1: 4.7 µH, Güte mindestens 20 bei 25 MHz, kleiner Gleichstromwiderstand. AN383 nennt eine SMD-Spule (1008). Eine durchsteckbare Drossel mit guter Güte reicht für den Test, wenn sie die Güte erreicht.
* C3: 33 pF, C0G, 5 %.
* Die 220-µH-Spule ersetzt den Ferritstab, wenn kein MW gebraucht wird (AN383). Alternativ dient der Ferritstab selbst als Spule.
* AN383 beschreibt diese Schaltung für Si4734/35, den Si4732 führt es nicht auf. Ob sie beim Si4732 gleich wirkt, zeigt der Test.
* Die Spule ist auf eine Teleskopantenne bis etwa 56 cm ausgelegt. Eine lange Drahtantenne verstimmt das Filter, das ist ein Messpunkt.
* Aussenantenne bei Gewitter immer trennen.

Testbänder (abends, Richtwerte): 49 m um 6 MHz, 31 m um 9.5 MHz, 25 m um 11.7 MHz, 19 m um 15.3 MHz. Notieren: Band, Antenne, Eingang (J2 oder J3), wie viele Sender verständlich sind.

### Klinkenbuchse (Kopfhörer und Line-Out)

**Der Chip kann keine Kopfhörer treiben.** Er liefert Line-Pegel (80 mV eff, Last mindestens 10 kΩ, höchstens 50 pF, Datenblatt Si473x-B20). Das Mikroe-Click löst es mit einem Kopfhörerverstärker (LM4910). Für das Funkfüürli ist deshalb ein eigener Kopfhörerverstärker vorgesehen (TPA6132A2, siehe [projektdefinition.md](projektdefinition.md) T6). Auf dem Breadboard ist er nicht ohne Weiteres aufbaubar (Gehäuse WQFN 3x3 mm), darum gilt für den Test:

| Test | Aufbau |
|---|---|
| Line-Out (Schritt 5d) | Buchse, Spitze an J1 Pin 1 (AUDIO_L), Ring an J1 Pin 2 (AUDIO_R), Hülse GND, Kabel zu Aktivlautsprecher oder Stereoanlage. Kein Kopfhörer anschliessen |
| Schaltkontakt | an GPIO 6, Low beim Einstecken (am Multimeter prüfen). Die Firmware schaltet die PAM8403-Versorgung über GPIO 5 ab, ein Hardware-Umschalter ist nicht nötig |
| Kopfhörer (Schritt 5f) | erst mit einem Testmodul mit TPA6132A2, sobald vorhanden (Beschaffung: siehe Stückliste, offen) |

### Audio

| Von | Nach | Bemerkung |
|---|---|---|
| GPIO 15 (Testton) | 10 kΩ, dann Knoten T | Reserve-Pin, PWM 1 kHz |
| Knoten T | 1 kΩ nach GND und 100 nF nach GND | Teiler und Tiefpass, etwa 0.3 Vpp |
| Handy oder Player, Klinke L | 22 kΩ, dann Knoten M | Quelle Ersatz, solange das RX-Board fehlt |
| Handy oder Player, Klinke R | 22 kΩ, dann Knoten M | Mono-Mischer |
| Knoten T oder M (Jumper) | 1 µF in Reihe, dann PAM8403 L-IN | Eingang wählen. Koppel-Kondensator nur, wenn das Modul keinen hat |
| PAM8403 R-IN | offen | Mono |
| PAM8403 GND | GND | |
| PAM8403 VCC | siehe Versorgung | |
| PAM8403 L+ und L- | Lautsprecher K 50 | Minuspol nicht an Masse (BTL) |
| GPIO 6 | Taster oder Jumper nach GND | Ersatz für den Klinken-Schaltkontakt, Pull-up intern |

**Mischer und Pegel (aus den Datenblättern gerechnet):**
* Der Chip verlangt eine Last von mindestens 10 kΩ pro Kanal (Datenblatt Si473x-B20, Si4732-A10 nennt den Wert nicht, messen). Auf dem RX-Board liegt je Kanal schon ein 20-kΩ-Widerstand nach GND (nach 470 nF). Mit 10 kΩ im Mischer läge die Last bei Modul-Eingang 10 kΩ nur noch bei etwa 8.6 kΩ. Mit 22 kΩ bleibt sie über 11 kΩ.
* Ausgangspegel des Chips: 80 mV eff typisch (72 bis 90). Nach dem Mischer (Modul-Eingang 10 kΩ angenommen) bleiben etwa 38 mV, nach dem PAM8403 (24 dB) etwa 0.6 V eff, das sind etwa 0.045 W am 8-Ω-Lautsprecher. Das ist Zimmerlautstärke. Ist es zu leise, wird der Mischer durch einen Operationsverstärker ersetzt (Rev B des Basisboards).
* Vor Schritt 5b den Eingangswiderstand des HW-012 zwischen Eingang und GND mit dem Multimeter messen (Poti auf Maximum) und ins Messprotokoll eintragen.

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

LDO (Entscheid): **AP2112K-3.3** (Diodes, SOT-23-5). Datenblatt: 600 mA, Dropout typisch 250 mV bei 600 mA (höchstens 400 mV), Eingang 2.5 bis 6 V, Ruhestrom 55 µA, Rauschen 50 µV eff, Unterdrückung 65 dB bei 1 kHz. Der ESP32-S3 braucht 3.0 bis 3.6 V und Espressif empfiehlt mindestens 500 mA, der Si4732 2.7 bis 3.6 V. Für das Breadboard ein fertiges Modul oder eine SOT-23-5-Adapterplatine (mit dem vorhandenen Lötgerät und der Lupe lötbar). Der LF33CV (TO-220, 400 mV Dropout bei 500 mA, 500 µA Ruhestrom) ist nur Notlösung. MCP1700 reicht nicht, AMS1117 hat zu viel Spannungsabfall.

Grenze, gerechnet: Nach der Schottky-Diode (etwa 0.3 V) liegen noch Akku minus 0.3 V am LDO. Er regelt auf 3.3 V, solange der Akku über etwa 3.7 bis 3.9 V liegt. Darunter folgt der Ausgang dem Eingang. Der ESP32 hält bis 3.0 V, also etwa bis Akku 3.5 bis 3.6 V. Abschaltschwelle in der Firmware um 3.5 V, Wert nach Schritt 7d festlegen.

Messteiler an den ADC-Eingängen:

| Signal | Teiler | ESP32 | Bemerkung |
|---|---|---|---|
| Akkuspannung | 100 kΩ von Akku plus nach GPIO 4, 100 kΩ von GPIO 4 nach GND, 100 nF am Pin | GPIO 4 (ADC1) | 4.2 V ergibt 2.1 V |
| USB-Erkennung (VBUS) | 100 kΩ von VBUS nach GPIO 17, 150 kΩ von GPIO 17 nach GND | GPIO 17 | 5 V ergibt 3.0 V |
| Ladestatus CHRG | TP4056 CHRG-Pin nach GPIO 16 | GPIO 16 | Open-Collector, interner Pull-up, Low heisst laden |

## Aufbau in der Kartonschachtel

Vorschlag, damit der Prototyp ein Gerät ist und nicht ein Kabelhaufen:

* Zwei Breadboards auf dem Boden festkleben (Doppelklebeband): links Steuerung (ESP32, Display, Encoder), rechts Audio und Strom.
* Display und Encoder in den Deckel oder die Frontseite, Löcher schneiden. Lautsprecher dahinter.
* Ferritstab und RX-Board an das andere Ende der Schachtel, mindestens eine Handbreit von ESP32, Display, Verstärker und Akku. Teleskopantenne durch ein Loch nach oben.
* Akku in eine eigene Ecke, Kabel mit Kabelbinder fixieren, USB-Buchse des DevKits erreichbar lassen.
* Erst alles offen testen, dann schliessen. Der Karton schirmt nichts ab, er dient nur der Ordnung.

## Wenn alles da ist: Vorbereitung

1. Arduino IDE mit ESP32-Core 3.x. Board "ESP32S3 Dev Module", Flash 16 MB, PSRAM OPI, USB CDC On Boot aktiviert (Vorschlag, gegen die Boardliste prüfen). USB-Kabel am Anschluss "USB" (nativ). Bibliotheken: Adafruit GFX, Adafruit ST7789.
2. Der Sketch in `firmware/breadboard_test/` ist noch nicht kompiliert. Fehler beim ersten Übersetzen sind zu erwarten und gehören ins Messprotokoll.
3. Reihenfolge einhalten: Schritte 1 bis 3 ohne RX-Board, Schritt 4 mit RX-Board, Strom (Schritt 7) zuletzt.
4. Jeden Schritt im Messprotokoll abhaken. Bei einem Fehler nicht weiterbauen, sondern die Fehlersuche unten abarbeiten.

## Testablauf

Jeweils erst weiter, wenn der Schritt läuft. Die Befehle gehören zum Testsketch.

| Schritt | Was | Erwartung | Ergebnis |
|---|---|---|---|
| 1 | ESP32 allein über USB, Sketch flashen, serieller Monitor (115200) | Menü erscheint | |
| 2 | Display: Befehl `d` | Farbfläche und Text, 240x320 | |
| 3 | Encoder: Befehl `e` | Drehen und Klick als Ausgabe, ohne Prellen | |
| 3a | I2C: Befehl `i` mit OLED | Adresse 0x3C | |
| 3b | Reset: Befehl `r` | LED blinkt kurz | |
| 4a | RX-Board anschliessen (ohne Antenne, ohne Audio), 3V3 und GND prüfen | kein Kurzschluss, `i` zeigt 0x11 | |
| 4b | Chip-Test: POWER_UP mit FUNC = 15 | Teilenummer Si4732 kommt zurück | |
| 4c | UKW abstimmen, Teleskop an J2, Ton über PAM8403 und Lautsprecher | Sender hörbar (P2) | |
| 4d | MW und LW abstimmen, Ferritstab an J3 | Sender hörbar (P3) | |
| 4e | KW über J2 (FMI) | Sender hörbar oder nicht (P4) | |
| 4f | KW über J3 (AMI) mit Zusatzschaltung | Sender hörbar oder nicht (P5) | |
| 5a | Audio: Befehl `t` | 1 kHz Ton aus dem Lautsprecher | |
| 5b | Handy über Klinke | Musik hörbar, Mono-Mischer prüfen | |
| 5c | Schalter über GPIO 5: Befehl `p` | Verstärker ein und aus, Ruhestrom messen | |
| 5d | Klinken-Ersatz: Befehl `j` | Pegel wechselt beim Jumper | |
| 5e | Störtest Verstärker: MW-Sender abstimmen, PAM8403 mit Lautsprecher ein und aus (GPIO 5) | Rauschen oder Pfeifen im MW-Band mit Verstärker ein, ja oder nein | |
| 5f | Kopfhörer: Testmodul mit TPA6132A2 an J1 Pin 1 und 2 | Ton auf Kopfhörer, Pegel, Rauschen | |
| 6 | Menü und Lautstärke | später mit Firmware aus dem Fork | |
| 7a | Strom über USB messen (ohne und mit Display, ohne und mit Verstärker, ohne und mit RX-Board) | Werte notieren | |
| 7b | LDO-Kette aufbauen, USB am DevKit abstecken, Akku anschliessen | 3V3 am Pin | |
| 7c | Befehl `a` | Akkuspannung stimmt mit Multimeter | |
| 7d | Entladekurve und Spannung, ab der der LDO nicht mehr regelt | Dropout mit Schottky-Diode (etwa 0.3 V) | |
| 8 | Pinplan korrigieren | Abweichungen vom Fork notieren | |

Weiter zu Stufe 2 (Lochraster), wenn Display, Encoder, I2C, Ton über Lautsprecher und die Stromkette laufen.

## Fehlersuche

| Symptom | Zuerst prüfen |
|---|---|
| Sketch lädt nicht | richtiger USB-Anschluss, Boot-Taste halten beim Verbinden, Datenkabel |
| Display bleibt weiss oder schwarz | Pins CS, DC, RST, Backlight, Betriebsspannung 3.3 V, Modulbeschriftung gegen Tabelle |
| `i` findet nichts | SDA und SCL vertauscht, 3V3 und GND am Modul, Pull-ups, Kontakt der Stiftleiste |
| 0x11 fehlt, aber 0x3C geht | Reset-LED noch dran, RST nicht an GPIO 7, SENB-Pegel (0x11 erwartet), Lötstellen J1 |
| Chip antwortet, kein Ton | 500 ms nach POWER_UP gewartet, Lautstärke, OPMODE 0x05, Koppel-Kondensator, Mischer-Jumper |
| Nur Rauschen oder Brummen | Abstand zu ESP32, Display und Verstärker, Antenne angeschlossen, Netzgerät statt USB-Hub probieren |
| UKW geht, KW nicht | erwartet bei Rev A, Ergebnis in P4 und P5 notieren |
| Verstärker pfeift | Eingangsleitungen kurz halten, Masse sternförmig, Eingang abklemmen als Gegenprobe |
| 3V3 bricht ein | Akku leer, Dropout der LDO-Kette, USB und LDO gleichzeitig am 3V3-Pin |

## Grenzen

* Lange Kabel und die Federkontakte machen SPI und Audio störanfällig. Ein Fehler hier ist kein Beweis gegen das Konzept.
* Empfang auf MW und KW und der Störtest sind auf dem Breadboard nur eingeschränkt aussagekräftig (lange Kabel, keine Massefläche). Die Tests liefern Funktions- und Vergleichswerte, die endgültige Messung folgt auf der Lochraster-Stufe und der Platine.
* Der Testsketch kennt noch keine Si4732-Befehle (Chip-Test, Frequenz setzen). Für 4b bis 4f braucht er eine Erweiterung mit der PU2CLR-Bibliothek (MIT).
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
| Strom mit RX-Board (UKW, MW) | | | |
| I2C-Adresse und Teilenummer des Chips | | | |
| Eingangswiderstand HW-012 (Poti Maximum) | | | |
| Audiopegel am Chip-Ausgang (mVeff), Pegel am Lautsprecher | | | |
| MW-Störung durch PAM8403 (ja, nein, Stärke) | | | |
| UKW: Anzahl Sender, Antenne | | | |
| MW: Anzahl Sender, Antenne | | | |
| KW über J2 (P4): Band, Antenne, Anzahl Sender | | | |
| KW über J3 (P5): Band, Antenne, Anzahl Sender | | | |

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
