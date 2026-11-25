# Status Funkfüürli

Höchstens 30 Zeilen. Immer überschreiben, nicht anhängen. Erledigtes streichen.

Entscheide stehen in der [Projektdefinition](docs/projektdefinition.md) (Funktionen, Anforderungen, Technik, Offene Punkte O1 ff.). Bau und BOM stehen im [Cookbook](docs/cookbook-prototyp.md), Abschnitt 9. Bei Widerspruch gelten diese beiden. `docs/stueckliste.md` ist nur noch Entwurf für Stufe 2 und 3. RX-Board: Repo RX-Board-Si4732 ist die Wahrheit, hier nur [Verweis](docs/rx-board.md).

## Stand (2026-11-25)
- Akku im Prototyp: LiPo 103665 (Marcel, 2026-11-25). Ob 18650 im Gerät bleibt (T5), ist offen.
- Pinplan mit Cookbook und RX-Board abgeglichen (J1-Tabelle). GPIO 15 (I2S-Reserve oder Testton): offen.
- Projektdefinition gelesen ab T7 bis zum Ende. Vor T7 (Funktionen, Anforderungen, T1 bis T6) noch nicht.
- RX-Board Rev A ist angekommen, noch nicht getestet. Stiftleisten J1, J2, J3 anzulöten.
- Cookbook Prototyp mit BOM (1 Gerät), v0.1-1. Rund 68 BOM-Felder stehen als `____`. Frühere Entscheide dazu stehen nicht im Repo.
- Noch keine KiCad-Datei der Basisplatine, keine eigene Firmware, kein Gehäuse.

## Als Nächstes
- Entscheide aus früheren Chats zu den BOM-Feldern einmal in Projektdefinition oder Cookbook eintragen.
- Rev-A-Tests nach Cookbook Schritt 4. Der Sketch kennt noch keine Si4732-Befehle (Erweiterung offen).
- BOM-Lücken: Display-Pinbelegung, Teleskopantenne, Lautsprecher (Typ, Anzahl), Zellenstecker.
- O22: Partitionsgrössen des Fork prüfen (16 MB für 2 Firmware-Plätze), OTA-Menü.
- O24: Fork-Suchlauf und Senderliste prüfen, Kriterien Pegel, SNR, RDS.
- Review Projektdefinition vor T7.

## Stolpersteine
- KW-Eingang des Si4732 (FMI oder AMI) ist aus den Unterlagen nicht eindeutig.
- Rückspeisung bei USB und DC-Eingang gleichzeitig: Lösung offen (O22).
- Alte Branches lassen sich aus der Sitzung nicht löschen, von Hand in GitHub.
