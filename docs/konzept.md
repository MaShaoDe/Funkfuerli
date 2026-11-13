# Funkfüürli: Konzept (Stand 2026-11-13, Entwurf)

Notfallradio für Workshops mit Schülern und Kindern. UKW, MW und KW, Akku mit Ladeanschluss, 3D-gedrucktes Gehäuse, eigene Platine. Open Source.

Grundsatz: Bestehende offene Software forken und anpassen, nicht von Grund auf neu entwickeln. Die Hardware (Platine, Gehäuse) ist ein eigenes Design. Als Mikrocontroller dient ein ESP32-S3-Modul im Format ESP32-S3-DevKitC-1 (N16R8). Das Inventar steht in `docs/inventar.md`.

## 1. Rahmen: UKW in der Schweiz
* Das Parlament hat die Abschaltung Ende 2026 am 9.12.2025 aufgehoben.
* Die SRG sendet laut Bakom-Konzession ab Mitte November 2026 wieder über erste UKW-Standorte (rund 80 % der Bevölkerung).
* Neue UKW-Konzessionen für Privatradios gelten von Januar 2027 bis Ende 2031.
* UKW bleibt politisch umstritten. KW funktioniert unabhängig davon, deshalb nicht nur UKW.

## 2. Empfänger
**Das Funkfüürli ist kein SDR.** Der Si4732 ist ein DSP-Empfängerchip (UKW, MW, LW, KW, RDS) und liefert keine Rohdaten (I/Q). Der ESP32 steuert den Chip nur. Die Abstimmung erfolgt digital per Drehencoder, es gibt keinen Drehkondensator. Langwelle wird in der Firmware ausgeblendet.

Der Si4732 liefert kein I/Q. Ein echter Wasserfall ist nur im Projekt Wellenjäger möglich. Mit dem Si4732 geht nur ein langsamer Bandscope (RSSI-Durchlauf, einige Sekunden pro Sweep).

## 3. Software
* **Basis: esp32-si4732/ats-mini, Fork.** Lizenz im Repo: MIT (Copyright 2025 ESP32-SI4732 Radio, geprüft am 2026-11-12). Das Repo enthält bereits: Bluetooth (BLE UART, HID), WLAN mit Webseite, OTA-Update, Fernsteuerung, Senderliste (EIBI), Speicherplätze, Bandscan, SSB-Patches, Batterieanzeige und zwei Anzeige-Layouts.
* Das Original zielt auf einen ESP32-S3 mit eigenem Display (320x170). Vorgesehen ist ein 2.0"-TFT mit ST7789V (240x320, SPI). Anzupassen sind Pinbelegung, Display-Auflösung und Layout, Treiber und Verstärker-Enable (Aufwand klein bis mittel).
* Vorbehalte:
  * Hardware (Schaltplan, Board) des Original-Empfängers von Sunnygold steht unter CC BY-NC-SA 3.0, also nicht kommerziell. Das Funkfüürli zeichnet ein eigenes Board und kopiert diesen Schaltplan nicht.
  * Im Quelltext ist Sunnygold in der Autorenzeile genannt. Ob davon Code mit NC-Lizenz im MIT-Repo steckt, ist nicht abschliessend geklärt. Vor kostenpflichtiger Verbreitung beim Maintainer nachfragen (GitHub Discussions).
  * Die SSB-Patchdatei (`patch_init.h`) stammt nicht von den Maintainern (Quelle: Vadim Afonkin, über die PU2CLR-Bibliothek verteilt). Das Weitergaberecht ist ungeklärt. SSB ist deshalb im Kinder-Bausatz optional (Patch lädt der Teilnehmer selbst) und nicht vorinstalliert.
* Fallback ohne Fork: PU2CLR SI4735-Bibliothek (MIT), eigenes schlankes Sketch nach deren ESP32-Beispielen.

## 4. Mikrocontroller
Entscheidung: **ESP32-S3-DevKitC-1 (N16R8)** auf Buchsenleisten. Es ist dieselbe Basis wie beim Wellenjäger. Der ATS-Mini-Fork zielt auf den S3.

Anforderungen an das Modul:

| Anforderung | Grund |
|---|---|
| Chip ESP32-S3 | Basis des Forks, SSB, WLAN, BLE |
| Flash mindestens 8 MB, besser 16 MB | Firmware mit OTA, Senderliste, Webseite |
| PSRAM vorhanden (N16R8: 16 MB Flash, 8 MB PSRAM) | Build-Varianten des Forks, Display-Puffer |
| Mindestens 14 frei nutzbare GPIOs | Pinbedarf siehe unten |
| Stiftleisten 2 x 22 Pins, Raster 2.54 mm | Steckplatz auf der Trägerplatine |
| Eigener 3.3-V-Regler, 5-V- oder VBAT-Eingang | Versorgung (Abschnitt 6) |
| USB zum Flashen | Teilnehmer flashen selbst |

Pinbedarf (Schätzung, etwa 17 Pins):
* I2C zum Si4732: 2 (SDA, SCL), Si4732 Reset: 1
* Display (SPI): 5 bis 6 (SCLK, MOSI, CS, DC, RST, Backlight ein/aus)
* Drehencoder: 3 (A, B, Taster)
* Verstärker-Versorgung ein/aus: 1, Klinken-Schaltkontakt: 1
* Bluetooth-Taster und Enable Sendemodul: 2
* Akkuspannung (ADC): 1, Ladestatus oder USB erkannt: 1 bis 2

Der Si4732 gibt analoges Audio aus, ein I2S-Codec ist nicht nötig.

Zu vermeiden beim N16R8 (vor dem Layout gegen Datenblatt und Schaltplan des Moduls prüfen): GPIO 0, 3, 45 und 46 (Strapping), 19 und 20 (USB), 26 bis 32 (Flash), 35 bis 37 (Octal-PSRAM, 33 und 34 nach Datenblatt ebenfalls meiden). Der Pinplan wird auf den N16R8 ausgelegt, die strengste Variante.

| Option | Strom (ca.) | SSB | WLAN | BLE | Bluetooth Classic (A2DP) | Bemerkung |
|---|---|---|---|---|---|---|
| ESP32-S3 | 40 bis 60 mA | ja | ja | ja | nein | Basis, Fork |
| ESP32 klassisch (WROOM-32) | 40 bis 70 mA | ja | ja | ja | ja | Nur für den A2DP-Versuch. Der Fork läuft nicht, 4 MB Flash meist zu klein |
| ESP32-C3, C6, C2 | 20 bis 40 mA | ja | ja | ja | nein | Fork braucht den S3, nicht vorgesehen |

Stromwerte sind Grössenordnungen aus der Erfahrung, vor der Festlegung messen. Die Angabe, dass S3 und C3 nur BLE und kein Bluetooth Classic haben, vor der Bestellung im Datenblatt von Espressif prüfen.

## 5. Antennen
* Teleskopantenne für UKW und KW. KW-Empfang damit ist schwach, eine Drahtantenne von 5 bis 10 m an der BNC-Buchse wirkt deutlich besser.
* Ferritstab für MW (Anschluss am Chip laut Datenblatt prüfen, im Prototyp testen).
* Externe Antennenbuchse (BNC) für eine Drahtantenne oder eine andere Antenne.
* UKW und AM haben beim Si4732 getrennte Eingänge, daher Umschaltung (Software, evtl. Schalter) oder zwei Anschlüsse. Welche Antenne an welchen Eingang gehört, ist im Datenblatt zu klären.
* Eingangsschutz gegen statische Aufladung (Schutzdioden). Eine Aussenantenne bei Gewitter immer trennen.
* Ferritstab auf Abstand zu Stahlzelle, Lautsprechermagnet, Metallteilen und Abschirmfolie. Nähe dämpft und verstimmt die MW-Antenne.

## 6. Strom
Die Akkufrage bleibt offen. Die Varianten liegen vor und werden im Prototyp verglichen. Die Elektronik ist für beide gleich (1 Zelle, 3.0 bis 4.2 V), nur die Akkukammer im Gehäuse unterscheidet sich.

| | Flacher LiPo 103665 | NCR18650B im Halter |
|---|---|---|
| Kapazität | 3000 mAh (Aufdruck) | ca. 3400 mAh laut Typ, ungeprüft, messen |
| Bauform | flach, ca. 66 x 37 x 11 mm | Zylinder 18 x 65 mm, Halter ca. 70 x 21 mm |
| Schutzschaltung | Schutzplatine vorhanden (auf Foto, Aufdrucke noch lesen) | keine, Schutz auf unserer Platine nötig |
| Robustheit | Folie, empfindlich gegen Druck und Durchstich, quillt im Alter | Stahlhülle, robuster |
| Fixierung | Fach mit Polster, JST-Stecker | Halter plus Abdeckung von oben |
| Beschaffung | nachbestellbar, nur mit ausdrücklicher Schutzschaltung | breit erhältlich, Kapazitätsangaben schwanken |

* **Dritte Variante, 14500 (AA-Format, 14 x 50 mm), 800 mAh (Aufdruck), 3.7 V, vermutlich ohne Schutzschaltung:** Sehr kompakt und im Feld mitführbar, aber die Kapazität ist klein. Bei etwa 125 bis 250 mA Gesamtverbrauch reicht das nur für etwa 3 bis 6 Stunden (Schätzung, messen). Als Notfall- oder Reserve-Zelle denkbar, nicht als Standard. Verwechslungsgefahr: Gleiche Grösse wie eine AA-Zelle mit 1.5 V. Ein Halter für 14500 muss deutlich gekennzeichnet sein, Schutz und Verpolschutz wie bei der 18650.
* Auf der Platine sind Lötpads für den Halter und ein JST-Anschluss für den LiPo vorgesehen, je nach Variante bestückt.
* Der Halter ist direkt auf die Platine gelötet, wird aber zusätzlich vom Gehäuse gehalten. Die Zelle wird mit Klettband oder wiederlösbarem Kabelbinder durch die Kerbe im Halter gesichert, dazu kommt die Abdeckung im Gehäuse.
* Akku in eigener Kammer mit Trennwand (Abschnitt 10).
* Schutz: ungeschützte Zellen bekommen eine Schutzschaltung auf der Platine (Schutz-IC mit Doppel-MOSFET). Für den LiPo nur Zellen mit Schutzschaltung beschaffen. Verpolschutz (P-FET) am Akkueingang, Pufferkondensator gegen kurze Kontaktunterbrüche.
* Laden über USB-C mit linearem Ladechip (TP4056-Typ mit Schutz, im Prototyp Micro-USB-Modul). Laden und Hören nicht gleichzeitig: Die Last wird beim Anstecken von USB getrennt.
* Schaltladegeräte (z.B. I2C-Lader mit Induktivität) gehören nicht ins Gerät.
* Versorgung: Akku, Ferrit und Kondensator, dann LDO 3.3 V für den Si4732. Für das ESP32-Modul zwei Wege: 3.3 V direkt auf den 3V3-Pin (Regler des Moduls umgehen, Diode oder Jumper gegen Rückspeisung über USB) oder 5 V. Empfehlung ist 3.3 V ohne Schaltregler, Entscheidung nach Prototyp.
* Laufzeit: Verbrauch ohne Verstärker etwa 100 mA, dazu bei Zimmerlautstärke etwa 50 bis 150 mA für den Verstärker (Schätzung). Ergibt grob 10 bis 25 Stunden je nach Zelle, vor der Festlegung messen.
* Keine 9-V-Blockbatterie (geringe Kapazität, Verluste beim Herunterregeln).
* Solar nur extern oder als getrennter Ladevorgang.

## 7. Audio
Der Ton soll auf drei Wegen hörbar sein:

1. **Interner Lautsprecher** (Standard): Visaton K 50 (Art. 2901), 8 Ω, 2 W, 250 bis 10000 Hz, 50 x 17 mm, Schallwandöffnung 45 mm (laut Datenblatt). Für Sprache und Radio ausreichend und günstig. Er sitzt in einem geschlossenen, abgedichteten Resonanzraum im 3D-gedruckten Gehäuse und ist am Gehäuse befestigt, nicht über die Platine. Variante: Lautsprecher mit eigenem Gehäuse (mehr Bass, grösser), an den 4 Befestigungsohren am Gehäuse verschraubt, Bassreflex-Öffnung nicht abdecken. Impedanz und Leistung dieser Variante sind noch zu klären.
2. **3.5-mm-Buchse für Kopfhörer und Line-Out**: Beim Einstecken schaltet der Schaltkontakt den internen Lautsprecher ab (der Minuspol des Lautsprechers darf dabei nicht an Masse, siehe Verstärker). Immer stereo, direkt vom Si4732. Damit lassen sich auch Stereoanlage oder aktiver Lautsprecher per Kabel anschliessen. Für den Line-Out ist ein Audio-Übertrager (1:1) gegen Brummschleifen als Option zu testen.
3. **Bluetooth zu Boombox oder externem Lautsprecher** (Option):
   * Bluetooth-Audio (A2DP) braucht Bluetooth Classic. Der S3 hat nur BLE und kann daher nicht direkt an einen Bluetooth-Lautsprecher senden (im Datenblatt prüfen).
   * Variante 1: kleines externes Bluetooth-Sendemodul (Audio-In vom Radio). Unabhängig vom Mikrocontroller. Auf der Platine als Steckplatz oder Pfostenleiste vorsehen, per Taster ein/aus.
   * Variante 2: klassischer ESP32 mit A2DP in der Firmware.
   * Latenz ca. 100 bis 200 ms, für Rundfunk unkritisch, beim Abstimmen spürbar. Kabel bleibt die Referenz.
   * Zusatzstrom ca. 30 bis 50 mA bei laufender Verbindung. Bluetooth nur bei Bedarf einschalten.
   * Das Bluetooth-Modul kann breitbandig rauschen, im Prototyp auf MW/KW messen.

Umschalten per Taste im Menü oder automatisch beim Einstecken des Klinkensteckers.

**Verstärker:** PAM8403-Modul (HW-012 mit Lautstärkepoti, 20 Stück vorhanden), Stereo, Class D.
* Versorgung ab etwa 2.5 V laut Datenblatt, also direkt vom Akku. Die Leistung ist bei Akkuspannung geringer als bei 5 V (prüfen). Der Elko auf dem Modul ist für 6.3 V ausgelegt.
* Die Ausgänge sind BTL. Der Minuspol des Lautsprechers darf nicht an Masse.
* Ein Standby-Pin ist auf dem Modul vermutlich nicht herausgeführt. Dann wird die Versorgung geschaltet, sonst läuft der Ruhestrom mit (messen).
* **Mono oder Stereo:** Standard ist Mono mit einem Lautsprecher. Zwei gleiche Widerstände mischen L und R zu einem Monosignal (sonst fehlt bei FM-Stereo die Hälfte des Signals), Wert vor dem Layout prüfen. Die Wahl "Eingang vom Radio-L oder vom Mischer" trifft ein 3-poliger Stiftleisten-Jumper (durchsteckbar). Eine Stereo-Variante mit zwei Lautsprechern bleibt Option.
* **Lautstärke:** Variante A mit Poti am Modul (Drehknopf für Abstimmung, Drehknopf für Lautstärke, Befestigung mit Mutter an der Frontplatte). Variante B mit Poti auf Maximum und Lautstärke per Software, Encoder-Klick wechselt zwischen Abstimmung und Lautstärke. Entscheidung offen.
* Pegel, Eingangsimpedanz des Moduls und Ausgangspegel des Si4732 vor dem Schaltplan im Datenblatt prüfen.
* Ausweichlösung bei Störungen im MW: Class-AB-Verstärker (z.B. LM386).

## 8. Störarmes Design
Erfahrung: Solarpanel mit Laderegler am gleichen Akku im gleichen Gehäuse wie ein ESP32 mit LoRa (Meshtastic) verschlechterte den Empfang deutlich. Ohne Regler und Panel ging der Empfang bedeutend besser. Ursache: Schaltwandler und MPPT-Regler schalten bei 100 kHz bis 2 MHz, die Oberwellen fallen in MW und KW.

Regeln:
1. Laden oder hören, nicht beides. Solar nur über Ladeanschluss oder Schalter, der den Lader im Radiobetrieb trennt. Ein externes Solar-Ladegerät ist am saubersten.
2. Linearer Lader (z.B. TP4056-Modul) statt MPPT-Schaltregler. Weniger effizient, aber ruhiger.
3. Versorgung des Empfängers: Akku, Ferrit und Kondensator, dann LDO für den Si4732. Schaltregler nur wo nötig, dann mit LC-Filter.
4. Ferritantenne weit weg von MCU, Display, Lader und Bluetooth-Modul. Abstand und Orientierung im Layout festlegen.
5. Display ohne PWM-Dimmung, WLAN und BT aus, solange gehört wird.
6. Kurze Leitungen, ein Panelkabel wirkt sonst als Antenne.
7. ESP32-Entwicklermodule haben eigene Regler und USB-Chips. Im ersten Prototyp den Einfluss auf MW/KW messen (Radio auf leeren Kanal, Modul zuschalten, mit und ohne Bluetooth-Sendemodul).
8. Prüfung: Radio auf leeren MW-Kanal stellen, Lader zuschalten, Störung hörbar. Das ist zugleich ein Lernmodul im Workshop (RFI-Jagd).
9. Class-D-Verstärker (PAM8403) schalten bei einigen 100 kHz (Datenblatt prüfen), Oberwellen können in MW fallen. Kurze Lautsprecherleitungen, Ferrit, Filter, im Prototyp messen.
10. Abschirmung: selbstklebende Kupferfolie, an einem Punkt geerdet, um Störquellen (ESP32, Display, Lader), nicht um den Akku und nie in der Nähe des Ferritstabs. Kein Kontakt zu Zelle, Federkontakten und Lötfahnen. Zuerst ohne Folie messen, dann mit Folie. Das ist ebenfalls ein Lernmodul.
11. Stahlzelle und Lautsprechermagnet auf Abstand zum Ferritstab.

## 9. Eigene Platine
* Design in KiCad 9 (wie bei den Riserboards), Gerber im Repo, Fertigung bei JLCPCB oder PCBWay.
* **Trägerplatine mit Buchsenleisten für das ESP32-S3-Modul** statt aufgelötetem ESP32. Teilnehmer stecken das Modul auf, es bleibt wiederverwendbar.
  * Modultyp: ESP32-S3-DevKitC-1 (N16R8), siehe Abschnitt 4. Masse und Reihenabstand der Stiftleisten am vorhandenen Modul prüfen (Clones unterscheiden sich).
  * Pinbelegung auf das Modul mit der strengsten Einschränkung auslegen und vor dem Layout gegen das Datenblatt prüfen.
* Das Modul wird mechanisch gehalten (Abschnitt 11).
* Auf der Platine: Encoder, Display, Spannungsversorgung mit LDO, Audioteil (Verstärker, Klinkenbuchse mit Schaltkontakt, Steckplatz für Bluetooth-Sendemodul), Akkuhalter (Lötpads) und JST-Anschluss, Schutz und Verpolschutz, Mono/Stereo-Jumper, Anschlüsse für Antenne und Lader.
* Bestückung: nur durchsteckbare Teile und fertige Module, alles von den Kindern gelötet. Ein Prüfstück komplett vorbestückt für den Kursleiter.
* Layout: Trennung von Lader, MCU, Audio/Bluetooth und Empfangsteil, durchgehende Massefläche, Ferritantenne am Rand.

## 10. Gehäuse (3D-Druck im Funkamateur-Club oder FabLab)
* Bauraum klein halten: maximal ca. 180 x 120 mm Grundfläche, damit auch kleine Drucker reichen.
* Druckbar ohne Stützmaterial: Teile liegen flach, Überhänge höchstens 45 Grad.
* Material: PETG als Standard, PLA nur für Innenräume. Keine Filamente mit Metall- oder Kohlefaseranteil.
* Toleranzen: 0.2 mm Spiel an Steckverbindungen, Passprobe vor dem Kurs.
* Befestigung: M3-Schrauben in Gewindeeinsätzen (Heat-Set) oder mit Vorbohrung, kein Kleben.
* Kunststoff schirmt nicht. Der Empfang wird über Abstand und Layout geschützt, nicht über das Gehäuse.
* Robustheit, Last und Falltest: siehe Abschnitt 11. Keine starren Rippen von oben auf Modul oder Platine.
* Zweiteilig (Boden und Deckel), 4 Schrauben, Batteriefach getrennt zugänglich.
* Öffnungen: Display-Fenster, Encoder-Knopf, Lautstärke-Poti (Variante), Lautsprecher-Gitter, BNC-Buchse, Teleskopantenne, 3.5-mm-Klinke, USB-C, Taster für Bluetooth.
* Ferritstab ausserhalb der Platine am Gehäuserand, mit definierter Ausrichtung, weit weg von Akku und Lautsprecher.
* Akku in eigener Kammer mit Trennwand. Die Wand trägt die Last der Zelle, nicht die Platine.
* Lautsprecher K 50 in geschlossenem Resonanzraum, am Gehäuse befestigt. Variante mit Lautsprecher-Box: an den 4 Ohren verschraubt, Bassreflex-Öffnung frei.
* Robust: abgerundete Kanten, Wandstärke ca. 2 bis 2.4 mm.
* Quelldaten im Repo: parametrisches CAD (OpenSCAD oder FreeCAD), dazu STEP und STL. Druckzeit höchstens ca. 2 bis 3 Stunden pro Gehäuse.
* Kurssatz: 10 bis 20 Gehäuse vorab im Club oder FabLab drucken, ein Mustergehäuse in Endfarbe.
* Kein Rufzeichen und keine privaten Angaben im Gehäuse.

## 11. Robustheit
Das Funkfüürli soll Kinderhände, Stürze und Alltag aushalten, auch im Rucksack als Notfallradio.

Abnahmekriterium: **Falltest aus 1 m auf Holz oder Fliesen.** Mehrere Stürze (flach auf Vorder- und Rückseite, auf eine Kante, auf eine Ecke, mit ausgefahrener Antenne). Danach muss gelten: Gehäuse ohne Riss, nichts lose, Radio startet, Abstimmung, Display und Ton funktionieren, Akku sitzt fest, Laden geht. Das Ergebnis kommt in ein Protokoll (Datum, Gehäuse-Version, Material, Befund). Der Falltest ist zugleich ein Programmpunkt im Workshop.

Prinzipien:
1. **Last nie über die Platine.** Wenn jemand auf das Gerät sitzt oder steht, darf nichts auf Modul, Display oder Platine drücken. Keine starren Rippen oder Stege vom Deckel auf Modul oder Platine. Die tragende Struktur sind Gehäusewände und Stützsäulen neben der Platine.
2. **Weich halten statt hart klemmen.** Modul, Display und Akku werden mit flexiblem Kunststoff (TPU-Pads aus dem 3D-Drucker) oder Schaumstoff (Moosgummi, PU-Schaum) gepolstert und nur leicht angedrückt. Kein Dauerdruck auf Steckverbindungen.
3. **Modul:** Aufnahme mit Seitenführung im Gehäuse, von oben ein weiches Pad. Buchsenleisten mit gedrehten Präzisionskontakten statt billiger Streifen. Für eine Endversion alternativ die Stiftleiste direkt einlöten.
4. **Platine:** 4 M3-Schrauben auf Abstandsbolzen, bei Bedarf mit Gummitüllen als Dämpfung.
5. **Gehäuse:** PETG, Wandstärke ca. 2.4 mm, abgerundete Ecken, Rippen nur an den Wänden, Stossecken (Bumper) aus TPU.
6. **Akku (schwerstes Teil):** eigene Kammer mit Trennwand, Zelle seitlich geführt, gepolstert und von oben gesichert (Abdeckung). Der Halter ist auf die Platine gelötet, wird aber zusätzlich vom Gehäuse gehalten, die Lötstellen tragen nur die Elektrik. Zelle im Halter mit Klettband oder wiederlösbarem Kabelbinder gesichert. Nur geschützte Zellen oder Schutz auf der Platine (Abschnitt 6). Beim Stoss kann der Kontakt kurz abheben: Pufferkondensator und Watchdog (Punkt 10). Das Gehäuse schützt die Zelle vor Quetschung.
7. **Das Gehäuse trägt die mechanischen Lasten, nicht die Lötstellen:** USB-C-Buchse mit enger Aussparung im Gehäuse abgestützt, BNC-Buchse mit Mutter durch die Gehäusewand verschraubt, Teleskopantenne am Gehäuse verankert, Encoder und Klinkenbuchse mit Mutter an der Frontplatte. Die Lötstellen tragen nur die Elektrik.
8. **Verkabelung:** Steckverbinder mit Zugentlastung, kurze Leitungen, keine frei hängenden Kabel.
9. **Bauteile mit Kleber sichern:** grosse Bauteile (Elkos, Spulen, Ferritstab, Steckverbinder) bekommen einen kleinen Tropfen Kleber. Welcher Kleber, ist offen:
   * Heissleim (einfach, am besten Niedertemperatur-Sorte, weicht aber bei ca. 60 bis 80 Grad auf, z.B. im Auto in der Sonne)
   * neutral vernetzendes Silikon (flexibel, reparierbar). Essigsäure-vernetzendes Silikon nicht verwenden, es korrodiert Elektronik.
   * Epoxidharz (hart, schwer zu reparieren)
   Kriterien: reparierbar, temperaturfest, nicht leitend, kindgerecht zu verarbeiten. Entscheidung nach Test.
10. **Firmware:** Der ESP32 hat eingebaute Hardware-Watchdogs. Watchdog und Brown-out-Erkennung aktivieren, bei Hänger von Prozessor oder I2C-Bus zum Si4732 automatisch neu starten, danach letzte Frequenz und Einstellungen wiederherstellen. Prüfen, was der ATS-Mini-Fork davon schon mitbringt.

## 12. Lizenzen
* Hardware CERN-OHL-P-2.0, Dokumentation CC-BY-4.0 (wie bei den Riserboards).
* Firmware: richtet sich nach dem Fork (ATS Mini: MIT).

## 13. Funktionen
Vom Fork vorhanden: Senderliste (EIBI), Speicherplätze, Bandscan, Batterieanzeige, WLAN mit Webseite, OTA, BLE, zwei Anzeige-Layouts.

Zusätzlich vorgesehen:
* **Abstimmung:** Drehencoder mit Fein- und Grobschritt je Band (Richtwerte UKW 50 bis 100 kHz, MW 9 kHz, KW 5 kHz, jeweils feinerer Schritt per Klick, Werte prüfen), optional Beschleunigung bei schnellem Drehen, dazu Speicherplätze. Hintergrund: Bei einem getesteten analogen Bausatz mit Poti-Abstimmung ist die Feinabstimmung kaum möglich.
* **Kindermodus:** nur 3 Bänder, grosse Frequenzanzeige, wenige Tasten, Schweizer Sender als Voreinstellung (Speicherplätze).
* **Auto-Aus und Sleep-Timer**, damit der Akku nicht leer läuft.
* **Akkuanzeige** gross, mit Warnung.
* **Lern-Modus:** S-Meter, Bandscan, RFI-Jagd, Abschirmungstest.
* **WLAN und BLE aus beim Hören** (Abschnitt 8).
* **SSB** nur optional, der Patch wird vom Teilnehmer selbst geladen.
* Notfall-Extras (Taschenlampe, Alarm): offen, vorerst nur Radio.

## Offene Punkte
1. ESP32-S3-DevKitC-1: Stückzahl, Länge, Breite und Reihenabstand der Stiftleisten am vorhandenen Modul, Aufdruck des Moduls (N16R8 oder andere Variante).
2. Si4732-Modul beschaffen: Variante im Datenblatt von Silicon Labs und gegen die Firmware prüfen. Getrennte FM- und AM-Eingänge, Audio links und rechts, Quarz, Raster 2.54 mm.
3. Display 2.0" ST7789V (240x320): Pins, Stiftleiste, Anpassung von Auflösung und Layout im Fork (Original 320x170).
4. Akku offen: Kapazität der NCR18650B und der 14500 messen, Aufdrucke der Schutzplatine des LiPo lesen, Stecker (JST) und Verpolschutz, Vergleich im Prototyp (Falltest, Laufzeit, Aufwand beim Zusammenbau, Preis).
5. Spannungsregler: Typ klären. Einspeisung des ESP32-Moduls mit 3.3 V oder 5 V entscheiden.
6. Verstärker HW-012 (PAM8403): Pegel, Eingangsimpedanz, Standby. Lautsprecher K 50: Resonanzraum auslegen. Lautsprecher-Box (Variante): Ohm, Watt, Masse. Lautstärke per Poti oder Software.
7. Bluetooth-Audio: externes Sendemodul oder klassischer ESP32 mit A2DP? Bluetooth-Classic-Angabe im Datenblatt bestätigen.
8. ATS Mini: Maintainer fragen wegen Sunnygold-Code und SSB-Patch-Weitergabe, bevor kostenpflichtige Kurse laufen. ESP32-SDR und ESP32-A1S-Tayloe haben keine Lizenzdatei.
9. Anschluss des Ferritstabs am Si4732 und Umschaltung FM/AM klären (Datenblatt).
10. Kursgrösse, Dauer, Materialkosten pro Teilnehmer. Ein Kostenziel wird noch nicht festgelegt, erst nach der Stückliste. Zum Vergleich: Ein kommerzieller analoger Radio-Bausatz kostet etwa 50 CHF.
11. Welcher Drucker und welcher Bauraum im Club und im FabLab? CAD-Werkzeug festlegen.
12. Namensprüfung (Swissreg/IGE und GitHub) vor der Veröffentlichung.
13. Kleber für Bauteile festlegen (Heissleim, neutral vernetzendes Silikon, Epoxid).
14. Watchdog und Neustart in der Firmware: Was bringt der ATS-Mini-Fork schon mit?
15. Falltest aus 1 m: Protokollvorlage und Testplan schreiben.
16. Störtest: Modul, Lader, Verstärker und Bluetooth-Sendemodul einzeln zuschalten, MW und KW messen. Abschirmung mit und ohne Kupferfolie vergleichen.
17. Notfall-Extras (Lampe, Alarm) ja oder nein.
18. Blockschaltbild und Stückliste.

## Quellen
* Parlament.ch, Ständerat 9.12.2025 (UKW-Abschaltung aufgehoben)
* cash.ch/AWP und PCtipp (SRG zurück auf UKW ab Mitte November 2026)
* turi2 (UKW-Konzessionen 2027 bis 2031)
* ATS Mini: github.com/esp32-si4732/ats-mini (LICENSE: MIT) und Doku esp32-si4732.github.io/ats-mini
* PU2CLR SI4735: pu2clr.github.io/SI4735 (MIT)
* Visaton K 50 (Art. 2901): Datenblatt von Visaton, z.B. bei ELV (media.elv.com, Datei 107174_k50_data.pdf)
