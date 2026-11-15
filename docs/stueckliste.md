# Funkfüürli: Stückliste (Stand 2026-11-15, Entwurf)

Stückliste für den Prototyp und den späteren Kurssatz. Grundlage sind das [Konzept](konzept.md), das [Inventar](inventar.md), die [Anforderungen](anforderungen.md) und der [Pinplan](pinplan.md).

**Reihenfolge:** Zuerst entsteht **1 Prototyp**. Der Kurssatz (10 Sätze) kommt erst danach. Der Prototyp dient zum Messen (Laufzeit, Störungen auf MW und KW, Falltest, Akku-Vergleich) und zum Entscheiden der offenen Punkte. Das Kostenziel von 30 bis 60 CHF gilt für den späteren Bausatz, nicht für den Prototyp.
**Rechenbasis:** Die Spalte "Pro Satz" gilt für den Prototyp. Die Spalte "10 Sätze" ist die Vorschau für den Kurssatz (8 Teilnehmer, 1 Prüfstück, 1 Reserve).
**Preise:** Nur Stichproben, mit Quelle. Wo "offen" steht, ist der Preis nicht geprüft. Eine Gesamtsumme ist deshalb noch nicht sinnvoll.
**Form:** Modul = fertig bestückt, wird gesteckt oder angeschlossen. THT = durchsteckmontiert, wird von den Teilnehmern gelötet.

## Einkaufsliste Prototyp (1 Stück)

Bestand ist im [Inventar](inventar.md) geführt. Zu besorgen ist, was dort fehlt:

| Was | Menge | Bemerkung |
|---|---|---|
| Si4732-Modul | 1 | Bestellt (Mikroe AM/FM 2 Click, 29 USD). Eigenes Mini-Modul später |
| Drehencoder EC11 mit Taster, Drehknopf | 1 | |
| Klinkenbuchse 3.5 mm mit Schaltkontakt | 1 | |
| BNC-Buchse, Teleskopantenne, Ferritstab MW | je 1 | Ferritstab-Typ klären |
| Hauptschalter | 1 | |
| LDO 3.3 V (THT), Pufferelko, Ferrit-Drosselperle | je 1 | LDO-Typ im Datenblatt prüfen |
| Widerstände, Kondensatoren, Transistor (Backlight, Verstärker-Schalter), Dioden | Sortiment | Werte aus dem Schaltplan |
| JST-Stecker für LiPo, Stiftleisten, Buchsenleisten 2 x 22, Jumper | Sortiment | Gedrehte Kontakte für den ESP32 |
| Lochraster (Streifen- oder Punktraster, doppelseitig mit Massefläche bevorzugt) | 1 | Entschieden 2026-11-15: Prototyp auf Lochraster. Eigene Platine erst nach bestandenem Test |
| Gehäuse (Testdruck PETG), TPU, M3-Schrauben, Schaumstoff | 1 Satz | Nach dem CAD |
| Kleber für den Test (Heissleim, neutrales Silikon, Epoxid) | kleine Mengen | Noch nicht entschieden |

Vorhanden und ausreichend für den Prototyp: ESP32-S3-DevKitC-1, Display 2.0" ST7789V, PAM8403 HW-012, TP4056-Lader, LiPo 103665, NCR18650B mit Halter, 14500, Visaton K 50.
Beim Prototyp bewusst beide Akku-Varianten (LiPo und 18650) aufbauen und vergleichen.

## 1. Module

| Nr | Bauteil | Pro Satz | 10 Sätze (später) | Form | Vorhanden (Inventar) | Bemerkung und Preis |
|---|---|---|---|---|---|---|
| 1 | ESP32-S3-DevKitC-1 N16R8 | 1 | 10 | Modul, gesteckt | Stückzahl offen (Nr 1) | Waveshare-Variante CHF 18.90 (bastelgarage.ch), Clones etwa 6 bis 7 EUR plus Versand (eBay) |
| 2 | Display 2.0" TFT, ST7789V, 240x320 | 1 | 10 | Modul, Stiftleiste | 4 (Nr 15) | Fehlmenge 6, Preis offen |
| 3 | Si4732-Empfängermodul | 1 | 10 | Modul, gesteckt | bestellt, noch nicht da | Siehe Abschnitt "Kostentreiber" |
| 4 | Verstärker PAM8403, HW-012 | 1 | 10 | Modul | 20 (Nr 28) | Reicht |
| 5 | Lader TP4056 mit Schutz | 1 | 10 | Modul | Stückzahl offen (Nr 25) | Micro-USB im Prototyp, später USB-C. Schutz gegen Tiefentladung nur mit dem Schutzmodul (siehe Abschnitt "THT-Konflikte") |

## 2. Strom

| Nr | Bauteil | Pro Satz | 10 Sätze (später) | Form | Vorhanden | Bemerkung |
|---|---|---|---|---|---|---|
| 6 | Akku, Variante offen: LiPo 103665 mit Schutz | 1 | 10 | JST | 10 (Nr 21) | Nur mit Schutzplatine |
| 6a | Alternative: NCR18650B plus Halter | 1 | | Halter gelötet | Stückzahl offen (Nr 22, 23) | Schutz nötig |
| 6b | Alternative: 14500 oder 14650 | 1 | | Halter gelötet | 14500: mindestens 4 (Nr 24) | 14650 noch nicht im Inventar |
| 7 | JST-Stecker für LiPo | 1 | 10 | THT | fehlt | |
| 8 | Hauptschalter (Schiebeschalter) | 1 | 10 | THT | nein | Preis offen |
| 9 | LDO 3.3 V, THT | 1 | 10 | THT | nein | Vorschlag MCP1700 (TO-92, 250 mA), im Datenblatt prüfen. Reicht für den Si4732, nicht für den ESP32 (siehe Konzept Abschnitt 6) |
| 10 | Pufferkondensator (Elko) | 1 | 10 | THT | nein | Wert beim Prototyp festlegen |
| 11 | Ferrit-Drosselperle in der Versorgung | 1 | 10 | THT | nein | Typ offen |
| 11a | Schottky-Diode 1N5819 (1 A, DO-41) als Verpolschutz | 1 | 10 | THT | nein | Entschieden 2026-11-15. In der Lastleitung, nicht im Ladepfad. Preis offen |
| 12 | Spannungsteiler (Widerstände) für Akku-ADC und USB-Erkennung | 2 Sätze | 20 | THT | nein | Werte nach Pinplan |

## 3. Audio

| Nr | Bauteil | Pro Satz | 10 Sätze (später) | Form | Vorhanden | Bemerkung und Preis |
|---|---|---|---|---|---|---|
| 13 | Lautsprecher Visaton K 50, 8 Ohm (Art. 2901) | 1 | 10 | Kabel oder Lötfahne | mindestens 1 (Nr 30) | 4.35 EUR (eBay, WITTKO, inkl. MwSt.), 4.95 EUR (soundimports.eu). alltron.ch führt ihn ebenfalls (Preis nicht geprüft) |
| 14 | Klinkenbuchse 3.5 mm, stereo, mit Schaltkontakt | 1 | 10 | THT | nein | Preis offen |
| 15 | Widerstände für den Mono-Mischer (2 gleiche) | 2 | 20 | THT | nein | Wert vor dem Layout prüfen |
| 16 | Stiftleiste 3-polig plus Jumper (Mono oder Stereo) | 1 | 10 | THT | nein | |
| 17 | Schaltung Verstärker-Versorgung (Transistor oder FET) | 1 | 10 | THT | nein | Typ offen, siehe Pinplan |
| 18 | Bluetooth-Sendemodul, optional | 1 | optional | Modul | nein | Nur wenn die Option bestückt wird |

## 4. Antennen

| Nr | Bauteil | Pro Satz | 10 Sätze (später) | Form | Vorhanden | Bemerkung |
|---|---|---|---|---|---|---|
| 19 | Teleskopantenne | 1 | 10 | Gehäuse verschraubt | nein | Preis offen. Für UKW und KW |
| 20 | BNC-Buchse, Platinenmontage | 1 | 10 | THT | nein | Preis offen. Mit Mutter durch die Gehäusewand |
| 21 | Ferritstab für MW | 1 | 10 | am Gehäuserand | nein | Typ und Anschluss offen |
| 22 | Schutz des Antenneneingangs gegen statische Aufladung | 1 | 10 | THT | nein | THT-Lösung offen (Dioden gibt es meist nur als SMD) |

## 5. Bedienung

| Nr | Bauteil | Pro Satz | 10 Sätze (später) | Form | Vorhanden | Bemerkung und Preis |
|---|---|---|---|---|---|---|
| 23 | Drehencoder EC11 mit Taster | 1 | 10 | THT | nein | Alps EC11 4.86 EUR (Mouser, Einzelpreis, Status NRND), Clones ab etwa 1.80 EUR (eBay) |
| 24 | Drehknopf | 1 | 10 | | nein | Passend zur Achse (6 mm, D-Achse, laut Typ prüfen) |
| 25 | Entprell-RC für den Encoder (Widerstände, Kondensatoren) | 1 | 10 | THT | nein | |
| 26 | Transistor für das Display-Backlight (z.B. BC337 oder 2N7000) | 1 | 10 | THT | nein | |
| 27 | Taster für Bluetooth, optional | 1 | optional | THT | nein | |

## 6. Verbinder

| Nr | Bauteil | Pro Satz | 10 Sätze (später) | Form | Vorhanden | Bemerkung |
|---|---|---|---|---|---|---|
| 28 | Buchsenleisten 2 x 22 mit gedrehten Kontakten (für den ESP32) | 2 | 20 | THT | nein | Gedrehte Kontakte halten besser (Konzept Abschnitt 11) |
| 29 | Buchsen- oder Stiftleisten für Display, Si4732 und Verstärker | nach Layout | | THT | nein | Nach dem Layout zählen |
| 30 | USB-C-Buchse oder Micro-USB am Lader | | | am Lader-Modul | Teil des Moduls | |

## 7. Platine und Gehäuse

| Nr | Bauteil | Pro Satz | 10 Sätze (später) | Bemerkung |
|---|---|---|---|---|
| 31 | Trägerplatine, KiCad 9, 2 Lagen | 1 | 10 | JLCPCB oder PCBWay. Mindestmenge meist 5, Preis offen |
| 32 | Gehäuse, 3D-Druck PETG | 1 | 10 | Vor dem Kurs gedruckt, 1 bis 2 im Kurs. Druckzeit höchstens 2 bis 3 Stunden |
| 33 | TPU für Stossecken und Pads | | | Filament oder fertige Pads |
| 34 | M3-Schrauben, Abstandsbolzen, Heat-Set-Einsätze | | | Nach CAD zählen |
| 35 | Schaumstoff oder Moosgummi (Sicherung ESP32, Polster Akku) | | | Weich, nur leicht angedrückt |
| 36 | Dichtungen für IP54 | | | An Öffnungen, Konzept offen |
| 37 | Klettband oder wiederlösbarer Kabelbinder | 1 | 10 | Für die Zelle im Halter |
| 38 | Kleber (Heissleim, neutral vernetzendes Silikon oder Epoxid) | | | Noch nicht entschieden |
| 39 | Beschriftung: Symbole, evtl. Lasergravur oder Aufkleber | | | Kein Rufzeichen |

## Prototyp: Tests vor der Platine

Der Prototyp wird auf Lochraster gebaut (Entscheid 2026-11-15). Wenn die Tests bestanden sind, folgt die eigene Platine in KiCad. Vorschlag für die Tests:

1. Empfang UKW, MW, KW mit Teleskopantenne und Drahtantenne, Vergleich mit einem bekannten Radio.
2. Störtest nach Konzept Abschnitt 8: Modul, Verstärker und Lader einzeln zuschalten, MW und KW auf leerem Kanal messen.
3. Laufzeit mit LiPo und mit 18650, Stromaufnahme mit und ohne Display.
4. Bedienung: Abstimmung mit dem Encoder, Anzeige, Lautstärke.
5. Falltest aus 1 m (nur mit Testgehäuse, nicht mit offenem Lochrasteraufbau).

Grenze: Ein Lochrasteraufbau hat lange Leitungen und keine durchgehende Massefläche. Störungen und Empfang fallen dort meist schlechter aus als auf einer Platine. Ein schlechter Wert ist darum kein Beweis gegen das Konzept, ein guter Wert ist ein gutes Zeichen. Die endgültige Messung folgt auf der Platine.

## Kostentreiber

* **Si4732-Modul:** Das Mikroe AM/FM 2 Click kostet 29 USD (Einzelpreis bei Digikey). Es hat zusätzlich einen Kopfhörerverstärker (LM4910) und ist 57.15 x 25.4 mm gross (Format L). Allein verbraucht es etwa die Hälfte des Kostenziels von 30 bis 60 CHF. Es taugt für den Prototyp, nicht für den Kurssatz. Fertige Si4732-Module auf eBay (17 bis 21 EUR) sind Umbaumodule für Funkgeräte (UV-K5) und passen nicht. Für den Kurssatz braucht es ein eigenes Mini-Modul oder ein günstigeres Breakout.
* **ESP32-S3-Modul:** CHF 18.90 beim Schweizer Händler, 6 bis 7 EUR bei einem Clone aus China. Das ist die zweite grosse Position.
* **Weiter:** Platine (offen), Display (offen), Akku und Lader (vorhanden, aber zum Nachbestellen offen).
* **Fazit:** Mit den bisher geprüften Preisen sind erst 4 von 39 Positionen belegt. Das Kostenziel lässt sich erst mit den restlichen Angeboten prüfen.

## Bewertet und verworfen: Si4732-Umbaumodul für UV-K5/K6

Geprüft am 2026-11-15: "SI4732 SSB Receiver Modification Board with Crystal Oscillator for Quansheng UV-K5/K6, FPC-Version". Nicht geeignet:

* Flexplatine mit kleinen Lötpads (G, R, A, AUDIO) und SMD-Bauteilen. Keine Stiftleisten, nicht steckbar, nicht THT.
* Gebaut für den Einbau ins Funkgerät. Es gibt keine Pinbelegung, keinen offenen Schaltplan und keine Lizenz.
* Preis je nach Händler etwa 18 bis 47 EUR oder USD plus Versand, die Chargen schwanken.
* Als Referenz ansehen ist in Ordnung. Nicht nachbauen und nicht abzeichnen (Lizenz unklar).

Bleibt dabei: Prototyp mit dem Mikroe AM/FM 2 Click, Kurssatz mit eigenem Mini-Modul nach der PU2CLR-Vorlage (MIT).

## THT-Konflikte

Diese Positionen widersprechen "nur Nicht-SMD löten":

1. **Si4732:** Der Chip ist meines Wissens nur SMD. Lösung: Modul auf Stiftleisten (Abschnitt 1).
2. **Schutz-IC für den Akku:** Schutz-ICs mit Doppel-MOSFET gibt es meist nur als SMD. Lösung: TP4056-Modul mit Schutz und geschützte Zellen. Das Konzept sieht den Schutz noch "auf der Platine" vor. Das ist zu ändern, wenn THT gelten soll.
3. **Verpolschutz:** Entschieden 2026-11-15: Schottky-Diode im Durchsteckgehäuse (1N5819), weil P-FETs im Durchsteckgehäuse selten Logic-Level sind. Die Diode verliert etwa 0.3 V (messen). Folge: Bei Zellspannungen unter etwa 3.6 bis 3.8 V regelt ein 3.3-V-LDO nicht mehr sauber, und ein Teil der Akkukapazität bleibt ungenutzt. Beim Prototyp die Entladekurve messen. Ein LDO mit kleiner Dropout-Spannung hilft. Zusätzlich bleiben die JST-Stecker und die Halter mechanisch gegen Verpolung kodiert.
4. **ESD-Schutz am Antenneneingang:** THT-Lösung offen.
5. **Einspeisung des ESP32:** Ein 250-mA-LDO reicht nicht für WLAN-Spitzen. Entscheidung 3.3 V direkt oder 5 V steht noch aus (Konzept Abschnitt 6).

## Offen

1. Testkriterien für den Prototyp festlegen, ab wann die Platine gestartet wird (Abschnitt "Prototyp: Tests vor der Platine").
2. Preise für Abschnitt 2 bis 7 holen, besonders Platine, Display und die Si4732-Alternative (für den Kurssatz).
3. Eigenes Si4732-Mini-Modul: Preis des Chips und der Fertigung klären (für den Kurssatz).
4. Fehlmengen für den Kurssatz (erst nach dem Prototyp): Displays 6, Lautsprecher mindestens 9, ESP32-Module je nach Bestand.
5. Stückliste mit dem Layout abgleichen, sobald die Platine steht.

*Quellen der Preise (Stand 2026-11-15, Stichproben): Digikey (Mikroe), bastelgarage.ch, eBay, Mouser, soundimports.eu.*

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
