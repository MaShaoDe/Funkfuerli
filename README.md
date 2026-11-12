# Funkfüürli: DIY-Notfallradio

[Deutsch](README.md) | [English](README.en.md)

*Ein kleines Feuer im Dunkeln. UKW, MW und KW in der Hosentasche, wenn das Netz ausfällt.*

("Füürli" ist Schweizerdeutsch für ein kleines Feuer.)

**Stand: Konzept.** Es gibt noch keine Hardware und keine Firmware. Diese Seite und [docs/konzept.md](docs/konzept.md) sammeln alles, was bisher entschieden ist.

## Was ist das?

Ein Bausatz für Workshops mit Kindern, Jugendlichen und allen, die ein Radio wollen, das auch dann noch geht, wenn sonst nichts mehr geht. In 2 bis 3 Stunden zusammengelötet, mit einem Drehknopf abgestimmt, empfängt es UKW, Mittelwelle und Kurzwelle.

* **Empfänger:** DSP-Chip Si4732 von Silicon Labs (UKW, AM/MW, KW, LW, RDS). Langwelle wird in der Firmware ausgeblendet.
* **Steuerung:** ein kleines ESP32-Modul (Wemos S3 oder C3 Mini), aufgesteckt auf eine Trägerplatine. Das Modul bleibt wiederverwendbar.
* **Abstimmung:** Drehencoder mit Taster und ein kleines Display. Kein Drehkondensator.
* **Ton:** eingebauter Lautsprecher, 3.5-mm-Buchse für Kopfhörer oder Line-Out, optional Bluetooth zu einem Lautsprecher.
* **Antennen:** Teleskopantenne, Ferritstab für MW, BNC-Buchse für eine Drahtantenne.
* **Strom:** geschützter 18650-Akku oder flacher LiPo mit 2000 mAh, Laden über USB-C mit linearem Ladechip. Solar nur als getrenntes, externes Ladegerät.
* **Gehäuse:** 3D-gedruckt, gemacht für jeden FDM-Drucker im Club oder FabLab.
* **Robust:** Abnahmekriterium ist ein Falltest aus 1 m auf Holz oder Fliesen. Weich gelagert, das Gehäuse trägt die Lasten.

Es ist **kein SDR**. Der Si4732 ist ein DSP-Empfängerchip, der ESP32 steuert ihn nur. Einen echten SDR mit Wasserfall gibt es im [Wellenjäger](https://github.com/MaShaoDe/Wellenjaeger).

## Warum nicht nur UKW?

Die SRG hat ihre UKW-Sender Ende 2024 abgeschaltet und nimmt sie ab Mitte November 2026 wieder in Betrieb, nachdem das Parlament die Abschaltung aufgehoben hat. UKW bleibt politisch unsicher. Kurzwelle funktioniert unabhängig davon.

## Störarm gebaut

Solar-Laderegler und Schaltregler stören MW und KW. Das Design hält Laden, Stromversorgung und Ferritantenne auseinander, und der Workshop macht aus der Störungssuche eine Lektion. Details in [docs/konzept.md](docs/konzept.md).

## Plan

- [x] Konzept und Lizenzprüfung der Software-Basis
- [ ] Genaues ESP32-Modul bestätigen (Footprint, Pinbelegung, Flash/PSRAM)
- [ ] Blockschaltbild und Stückliste
- [ ] Trägerplatine in KiCad 9
- [ ] Firmware: Fork von [esp32-si4732/ats-mini](https://github.com/esp32-si4732/ats-mini) (MIT), angepasst an das neue Board
- [ ] Gehäuse in OpenSCAD oder FreeCAD, Testdruck im Club oder FabLab
- [ ] Prototyp, Störmessungen auf MW und KW
- [ ] Workshop-Unterlagen

## Offene Fragen

Siehe die Liste in [docs/konzept.md](docs/konzept.md), Abschnitt "Offene Punkte".

## Lizenz

Hardware CERN-OHL-P-2.0, Dokumentation CC-BY-4.0. Die Firmware folgt ihrem Upstream-Projekt. Siehe [LICENSE.md](LICENSE.md).

73 de Marcel (MaShaoDe)
