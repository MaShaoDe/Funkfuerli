# Status Funkfüürli

Höchstens 30 Zeilen. Immer überschreiben, nicht anhängen. Erledigtes streichen.

Massgebend ist die [Projektdefinition](docs/projektdefinition.md) (Funktionen, Anforderungen, Technik, Offene Punkte O1 ff.).

## Stand (2026-11-20)
- Projektdefinition im Review (PR 27), Kapitel bis T7 gelesen, weiter ab T7. Nur Funkfüürli selbst, nichts zu Kurs oder anderen Projekten.
- Neu eingetragen als Vorschlag oder offen: Reparierbarkeit (H6, C4), BNC-Antenne, DC-Buchse 5 V mit Eingangsschutz, Flashen per OTA statt USB am Gehäuse (O22), Gehäusehöhe offen.
- RX-Board Rev A ist bestellt, Lieferung steht aus. Rev A hat keinen KW-Zweig.
- Noch keine KiCad-Datei der Basisplatine, keine eigene Firmware, kein Gehäuse.

## Als Nächstes
- Marcel: PR 27 mergen, Review ab T7 fortsetzen.
- Lautsprecher: Typ und Anzahl (1 oder 2) offen, T6 Punkt 1 nennt noch den Visaton K 50 (ungeprüft).
- O22: OTA prüfen (Fork, Speicher, WLAN nur zum Update per Menüeintrag), Rückspeisung bei USB und DC-Eingang.
- Weitere Bluetooth- und Kurs-Reste in anderen Dokumenten (README, Anforderungen, Stückliste, Pinplan) bereinigen, eigener PR, offen.
- Rev-A-Tests P1 bis P9, danach Entscheid KW-Eingang, Rev B, Basisboard.

## Stolpersteine
- Teleskopantenne (Typ, Länge), DC-Buchse (Innendurchmesser) noch nicht bestimmt.
- KW-Eingang des Si4732 (FMI oder AMI) ist aus den Unterlagen nicht eindeutig.
- UKW der SRG: Wiederinbetriebnahme ab Mitte November 2026, politisch unsicher.
