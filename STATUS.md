# Status Funkfüürli

Höchstens 30 Zeilen. Immer überschreiben, nicht anhängen. Erledigtes streichen.

Massgebend ist die [Projektdefinition](docs/projektdefinition.md) (Funktionen, Anforderungen, Technik, Offene Punkte O1 ff.).

## Stand (2026-11-19)
- Projektdefinition und Pflichtenhefte liegen im Repo (Funkfuerli, RX-Board-Si4732, Funkbasis-ESP32).
- RX-Board Rev A ist bestellt, Lieferung steht aus. Rev A hat keinen KW-Zweig.
- Breadboard-Plan für den Test mit RX-Board Rev A: docs/breadboard.md, docs/bom-breadboard.md.
- Noch keine KiCad-Datei der Basisplatine, keine eigene Firmware, kein Gehäuse.

## Als Nächstes
- Testsketch um Si4732-Befehle erweitern (Chip-Test, Frequenz).
- Rev-A-Tests P1 bis P9 durchführen, besonders KW über J2 (P4) und J3 (P5).
- Danach Entscheid KW-Eingang, Layout RX-Board Rev B, dann Basisboard (Funkbasis-ESP32).

## Stolpersteine
- KW-Eingang des Si4732 (FMI oder AMI) ist aus den Unterlagen nicht eindeutig.
- UKW der SRG: Wiederinbetriebnahme ab Mitte November 2026, politisch unsicher. Kurzwelle bleibt unabhängig.
