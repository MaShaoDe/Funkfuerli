# Funkfüürli: Hauptplatine (Stand 2026-11-15, Entwurf)

Anforderungen und Entscheide für die eigene Platine (Stufe 3 des Prototyps, siehe [prototyp.md](prototyp.md)). Die Platine wird jetzt entworfen und erst nach bestandenem Lochraster-Test bestellt (Entscheid 2026-11-15, Vorgehensplan unverändert).

## Entscheide 2026-11-15

| Nr | Entscheid |
|---|---|
| 1 | Der ESP32 wird über einen LDO am Pin 3V3 des DevKits gespeist (kein 5-V-Boost, kein Schaltregler). Der LDO muss die WLAN-Spitzen liefern (mindestens 500 mA) und eine kleine Dropout-Spannung haben, weil der Akku bis 3.0 V entladen wird und die Schottky-Diode etwa 0.3 V kostet. Der MCP1700 (250 mA) reicht nicht. Kandidat: LF33CV (TO-220), Datenblatt vor der Wahl prüfen. |
| 2 | Akku: Lötpads für einen 14650-Halter (1 Zelle, Masse laut Angabe 77.1 x 20.65 x 14.9 mm) und ein JST-Stecker für den LiPo 103665. Es wird nur einer bestückt. |
| 3 | TP4056-Lader und PAM8403 (HW-012) bleiben fertige Module auf Stiftleisten. Die Kinder löten Stiftleisten und Buchsen. |
| 4 | RX-Board gesteckt über J1 (1x9), Pinbelegung siehe [RX-Board-Repo](https://github.com/MaShaoDe/RX-Board-Si4732/blob/main/docs/rx-board.md). |

## ESP32-S3-DevKitC-1 (Foto vom Modul geprüft)

Zwei Reihen mit je 22 Pins im Raster 2.54 mm. Das Modul hat 2 USB-C-Buchsen am einen Ende und eine Antennenfläche mit U.FL am anderen Ende. Beschriftung auf dem Foto:

| Reihe | Reihenfolge von der Antennenseite zur USB-Seite |
|---|---|
| Oben (J1) | 3V3, 3V3, RST, 4, 5, 6, 7, 15, 16, 17, 18, 8, 3, 46, 9, 10, 11, 12, 13, 14, 5V, GND |
| Unten (J3) | GND, TX, RX, 1, 2, 42, 41, 40, 39, 38, 37, 36, 35, 0, 45, 48, 47, 21, 20, 19, GND, GND |

Hinweise:
* Auf dem Foto steht bei den Pins 13 und 14 zweimal "13". Das ist vermutlich ein Druckfehler des Clones (der Original-Plan hat 14). Vor dem Layout mit dem Multimeter prüfen.
* Die beiden USB-Seitenpins 5V und GND sind auf dem Foto verdeckt, die Reihenfolge stammt aus dem Datenblatt des Originals.
* Alle Pins des Pinplans (1, 2, 4 bis 14, 16, 17, 21, 42) sind herausgeführt.
* Reihenabstand der beiden Reihen: noch zu messen (Schätzung aus dem Foto etwa 22 bis 23 mm, mit Messschieber prüfen).
* Unter der Antennenfläche des Moduls kein Kupfer und keine Bauteile. Die USB-C-Buchsen liegen am Platinenrand und brauchen einen Ausschnitt im Gehäuse.

## Auf der Platine

* Buchsenleisten 1x22 (2 Stück, gedrehte Kontakte) für den ESP32
* Stiftleiste oder Buchsenleiste 1x9 für das RX-Board (J1 des RX-Boards)
* Display 2.0" ST7789V (Stiftleiste, Pins noch zu liefern)
* Drehencoder mit Taster, Entprell-RC
* LDO 3.3 V, Pufferelko, Ferrit-Drosselperle
* Hauptschalter, Schottky-Diode 1N5819 (Verpolschutz), Teiler für Akkuspannung (ADC) und USB-Erkennung
* Anschluss für das TP4056-Modul, den PAM8403 (HW-012) und den Klinkenstecker mit Schaltkontakt
* Mono/Stereo-Jumper, Steckplatz für das optionale Bluetooth-Sendemodul
* BNC-Buchse, Anschluss für Teleskopantenne und Ferritstab (am Platinenrand, weit weg von Akku, Lautsprecher, ESP32, Display und Lader)
* Akku: Pads für den 14650-Halter und JST für den LiPo

## Noch zu liefern

1. Reihenabstand der ESP32-Stiftleisten (Messschieber)
2. Pinbelegung und Masse des 2.0"-Displays
3. Masse und Pinreihenfolge der Module HW-012 (PAM8403) und TP4056
4. Anschlussart des 14650-Halters (Lötfahnen oder Drähte, Abstand der Kontakte)
5. Ferritstab: Typ und Länge
6. LDO: Datenblatt prüfen und festlegen

## Reihenfolge

1. Anforderungen und Entscheide (dieses Dokument)
2. Schaltplan und Platine als KiCad-Entwurf (Generator, wie beim RX-Board)
3. ERC und DRC, Gerber, Vorschau
4. Bestellung erst nach bestandenem Lochraster-Test

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
