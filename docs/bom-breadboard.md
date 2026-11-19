# Funkfüürli: Stückliste Breadboard-Test (Stand 2026-11-19, Entwurf)

Einkaufsliste für den Prototyp auf dem Breadboard und in der Kartonschachtel. Gilt für [breadboard.md](breadboard.md) mit RX-Board Rev A. Bezugsquellen erst beim Bestellen.

Status: **vorhanden** = laut [inventar.md](inventar.md) da. **Sortiment** = aus dem Bauteilsortiment, vor dem Bestellen nachzählen. **beschaffen** = fehlt. Die Spalte "Schritt" verweist auf den Testablauf in breadboard.md.

## 1. Module

| Menge | Teil | Schritt | Status |
|---|---|---|---|
| 1 | ESP32-S3-DevKitC-1 N16R8 | 1 bis 8 | vorhanden, Stückzahl prüfen |
| 1 | Display 2.0" ST7789V, 240x320 | 2 | vorhanden, Pinbelegung des Moduls prüfen |
| 1 | RX-Board Rev A (Si4732) | 4 | bestellt, voll bestückt, Stiftleisten fehlen |
| 1 | OLED 0.96" SSD1306 (I2C 0x3C) | 3a | vorhanden, Bustest vor Lieferung des RX-Boards |
| 1 | PAM8403 Modul HW-012 | 5 | vorhanden (20) |
| 1 | Lautsprecher Visaton K 50, 8 Ω | 5 | vorhanden |
| 1 | TP4056 Modul mit Schutz | 7 | vorhanden |
| 1 | LiPo 103665 mit Schutz | 7 | vorhanden, Stecker fehlt |

## 2. Bedienung und Anschlüsse

| Menge | Teil | Schritt | Status |
|---|---|---|---|
| 1 | Drehencoder EC11 mit Taster und Knopf | 3 | beschaffen |
| 1 | Klinkenbuchse 3.5 mm stereo mit Schaltkontakt (Breakout oder THT) | 4, 5d | beschaffen |
| 1 | Klinkenkabel 3.5 mm beidseitig | 5b | Sortiment |
| 1 | Schiebeschalter | 7 | beschaffen |
| 1 | Taster | 5d | Sortiment |
| 1 | Kopfhörer oder Aktivlautsprecher mit Line-Eingang | 4c | Sortiment, nur Zusatztest (Last am Chip prüfen) |

## 3. Empfang und Antennen

| Menge | Teil | Schritt | Status |
|---|---|---|---|
| 1 | Stiftleiste 1x9 und 2 Stück 1x2, 2.54 mm | 4a | Sortiment (J1, J2, J3 anlöten) |
| 1 | Teleskopantenne mit Anschlusskabel oder Krokodilklemme | 4c, 4e | beschaffen |
| 1 | Ferritstab MW, 180 bis 450 µH | 4d | beschaffen, Typ klären. AN383 nennt 8x50 mm (SL8X50MW70T) oder 4x30 mm (SL4X30MW100T) von Jiaxin |
| 1 | Drahtantenne 5 bis 10 m (Litze) mit Krokodilklemme | 4e | Sortiment |

KW-Zusatzschaltung für Test P5 (an J3), Schritt 4f:

| Menge | Teil | Status |
|---|---|---|
| 1 | Spule 4.7 µH, Güte mindestens 20 bei 25 MHz (AN383: 1008CS-472, SMD) | beschaffen. Durchsteckdrossel nur, wenn die Güte erreicht wird |
| 1 | Kondensator 33 pF, C0G, 5 % | Sortiment prüfen |
| 1 | Spule 220 µH (ersetzt den Ferritstab für KW) | beschaffen |
| 1 | Lochrasterplatte klein mit Stiftleiste 1x2 | Sortiment |

## 4. Strom (Schritt 7, erst nach den übrigen Tests)

| Menge | Teil | Status |
|---|---|---|
| 1 | LDO 3.3 V, mindestens 500 mA, kleine Dropout-Spannung: Modul mit AP2112K-3.3 oder LF33CV (TO-220) | beschaffen, Datenblatt vor Bestellung prüfen |
| 1 | Diode 1N5819 | Sortiment |
| 1 | JST-Stecker für den LiPo | beschaffen, passend zur Zelle prüfen |
| 1 | Ferritperle | Sortiment |
| 1 | Elko 220 µF, 10 V oder mehr | Sortiment |
| 1 | Elko 10 µF (LDO-Ausgang) | Sortiment |
| 1 | USB-Datenkabel für das DevKit | Sortiment |
| 1 | Micro-USB-Kabel für den TP4056 | Sortiment |

## 5. Halbleiter und Kleinteile

| Menge | Teil | Zweck | Status |
|---|---|---|---|
| 2 | Transistor BC337 (NPN) | Verstärkerschalter, Backlight (falls das Modul keinen hat) | Sortiment |
| 1 | Transistor BC327 (PNP) | Verstärkerschalter | Sortiment |
| 6 | Keramik 100 nF | Entprellung, Teiler, LDO | Sortiment |
| 1 | Elko oder Keramik 1 µF | Audio-Kopplung | Sortiment |
| 1 | LED mit Vorwiderstand | Reset-Anzeige, nur vor Lieferung des RX-Boards | Sortiment |

## 6. Widerstände (Sortiment)

| Menge | Wert | Zweck |
|---|---|---|
| 3 | 100 kΩ | Akku-Teiler (2), USB-Teiler oben (1) |
| 1 | 150 kΩ | USB-Teiler unten |
| 8 | 10 kΩ | Mischer Handy L und R (2), Mischer Radio L und R (2), Testton, NPN-Basis, PNP-Basis, Reserve |
| 2 | 4.7 kΩ | I2C Pull-ups, nur wenn das Modul keine hat |
| 4 | 1 kΩ | Testton-Teiler, Transistor-Basis, Transistor-Kollektor, LED |

Reserve: je 2 Stück der Werte. Wert des Backlight-Vorwiderstands nach Messung.

## 7. Aufbau in der Kartonschachtel

| Menge | Teil | Status |
|---|---|---|
| 2 | Breadboard 830 Punkte (Display und Rest getrennt) | vorhanden |
| 1 Set | Dupont-Drähte (m-m, m-w) und Steckbrücken | vorhanden |
| 1 | Schachtel etwa 25 x 18 x 8 cm (Schuhschachtel genügt) | Sortiment |
| 1 | Doppelklebeband, Kabelbinder, Heissleim | vorhanden |

## Offen

* LDO-Typ nach Datenblatt festlegen.
* Display-Pinbelegung und Anschlussart prüfen.
* Stecker der Zelle prüfen (103665 ohne Stecker).
* Ferritstab-Typ festlegen.
* Spule 4.7 µH mit ausreichender Güte beschaffen.

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
