# Status Funkfüürli

Höchstens 30 Zeilen. Immer überschreiben, nicht anhängen. Erledigtes streichen.

Was beschlossen ist: [docs/festlegungen.md](docs/festlegungen.md). Nicht neu fragen. Alles andere (Offenes, Vorschläge): [Projektdefinition](docs/projektdefinition.md), O1 ff. Prototyp: [Cookbook](docs/cookbook-prototyp.md). RX-Board: Repo RX-Board-Si4732 ist die Wahrheit, hier nur [Verweis](docs/rx-board.md).

## Stand (2026-11-25)
- Projektdefinition im Review, gelesen bis T7, weiter ab T7.
- RX-Board Rev A ist angekommen, noch nicht getestet. Stiftleisten J1, J2, J3 anzulöten.
- Cookbook Prototyp mit BOM (1 Gerät) liegt vor, v0.1-1. Viele BOM-Felder stehen als ____.
- Noch keine KiCad-Datei der Basisplatine, keine eigene Firmware, kein Gehäuse.

## Als Nächstes
- Pinplan gegen Cookbook abgleichen.
- Review Projektdefinition ab T7.
- Rev-A-Tests nach Cookbook Schritt 4 (UKW, MW, KW über J2 P4 und J3 P5, RDS).
- BOM-Lücken: Display-Pinbelegung, Teleskopantenne, Lautsprecher (Typ, Anzahl), Zellenstecker.
- O22: Partitionsgrössen des Fork prüfen (OTA). O24: Sendersuche im Fork prüfen.

## Stolpersteine
- KW-Eingang des Si4732 (FMI oder AMI) ist aus den Unterlagen nicht eindeutig.
- Rückspeisung bei USB und DC-Eingang gleichzeitig: Lösung offen (O22).
- Alte Branches lassen sich aus der Sitzung nicht löschen, von Hand in GitHub.
- Ältere Dokumente (konzept, anforderungen, stueckliste, platine) enthalten Überholtes (Kurs, USB-C, SMA, Bluetooth). Es gilt die Projektdefinition.
