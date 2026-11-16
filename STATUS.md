# Status Funkfüürli

Höchstens 30 Zeilen. Immer überschreiben, nicht anhängen. Erledigtes streichen.

## Stand (2026-11-16)
- Konzept, Pinplan, Blockschaltbild, Stückliste, Inventar liegen in docs/ (Entwürfe).
- RX-Board (Si4732): Beschreibung und Pinbelegung in docs/rx-board.md (Entwurf).
- Hauptplatine: Anforderungen und Entscheide in docs/platine.md (Entwurf, wird entworfen, Bestellung erst nach Lochraster-Test).
- Prototyp in 3 Stufen (docs/prototyp.md): Breadboard, Lochraster, eigene Platine.
- Breadboard Aufbau und Test: PR 17 gemergt (docs/breadboard.md, firmware/breadboard_test/).
- Noch keine KiCad-Datei, keine eigene Firmware, kein Gehäuse.

## Als Nächstes
- Vorschlag: Breadboard-Test durchführen und Ergebnis dokumentieren.
- Vorschlag: ESP32-Modul bestätigen (Footprint, Pinbelegung, Flash/PSRAM).
- Vorschlag: LDO-Datenblatt prüfen (Kandidat LF33CV, mind. 500 mA).
- Plan siehe README, Abschnitt «Plan».

## Entscheide (Marcel Sauder, 2026-11-15)
- Breadboard zuerst, dann Lochraster, Platine erst nach bestandenem Test.
- ESP32 über LDO am Pin 3V3 des DevKits (kein Boost, kein Schaltregler).
- Akku: Pads für 14650-Halter und JST für LiPo 103665, nur einer bestückt.
- TP4056 und PAM8403 als Module auf Stiftleisten, RX-Board gesteckt über J1.

## Stolpersteine
- Si4732-Modul ist noch nicht bestellt (PR 12).
- UKW der SRG: Wiederinbetriebnahme ab Mitte November 2026, politisch unsicher. Kurzwelle bleibt unabhängig.
