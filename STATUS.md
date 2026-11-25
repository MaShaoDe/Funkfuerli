# Status Funkfüürli

Höchstens 30 Zeilen. Immer überschreiben, nicht anhängen. Erledigtes streichen.

Massgebend ist die [Projektdefinition](docs/projektdefinition.md) (Funktionen, Anforderungen, Technik, Offene Punkte O1 ff.). Prototyp: [Cookbook](docs/cookbook-prototyp.md). RX-Board: Repo RX-Board-Si4732 ist die Wahrheit, hier nur [Verweis](docs/rx-board.md).

## Stand (2026-11-25)
- Projektdefinition im Review, gelesen bis T7, weiter ab T7. Nur Funkfüürli selbst.
- Neu: Sendersuche F16 bis F18, Flashen per OTA als Vorschlag (O22), Reparierbarkeit, BNC, DC-Buchse 5 V.
- RX-Board Rev A ist angekommen, noch nicht getestet. Stiftleisten J1, J2, J3 anzulöten.
- Cookbook Prototyp mit BOM (1 Gerät) liegt vor, Version v0.1-1. Viele BOM-Felder stehen als `____`.
- Noch keine KiCad-Datei der Basisplatine, keine eigene Firmware, kein Gehäuse.

## Als Nächstes
- Rev-A-Tests nach Cookbook Schritt 4 (UKW, MW, KW über J2 P4 und J3 P5, RDS).
- BOM im Cookbook ausfüllen (`____`), Display-Pinbelegung, Teleskopantenne, Lautsprecher (Typ, Anzahl), Zellenstecker.
- Pinplan gegen Cookbook abgleichen.
- O22: Partitionsgrössen des Fork prüfen (16 MB für 2 Firmware-Plätze), OTA-Menü.
- O24: Fork-Suchlauf und Senderliste prüfen, Kriterien Pegel, SNR, RDS.
- Review Projektdefinition ab T7 fortsetzen.

## Stolpersteine
- KW-Eingang des Si4732 (FMI oder AMI) ist aus den Unterlagen nicht eindeutig.
- Rückspeisung bei USB und DC-Eingang gleichzeitig: Lösung offen (O22).
- Alte Branches lassen sich aus der Sitzung nicht löschen, von Hand in GitHub.
