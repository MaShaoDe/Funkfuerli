# Funkfüürli: Projektdefinition (Stand 2026-11-19, Entwurf)

Die Nummern (F1, G3, T5, O7 ...) gelten in allen Dokumenten des Projekts.

Notfallradio mit UKW, MW und KW, Akku mit Ladeanschluss, 3D-gedrucktem Gehäuse und eigener Platine. Open Source. Grundsatz: offene Software forken und anpassen, Hardware (Platine, Gehäuse) ist ein eigenes Design.

## 1. Rahmen

* **Ziel:** Das Funkfüürli bringt die Technik des Radios und der Radiowellen näher. Es ist ein DIY-Projekt: Jede und jeder kann es selbst bauen und lernt dabei viel.
* **Bänder:** UKW, MW und KW zeigen drei Arten der Wellenausbreitung. UKW bleibt in der Schweiz in Betrieb: Das Parlament hat die Abschaltung am 9.12.2025 aufgehoben, die SRG sendet ab Mitte November 2026 wieder über erste UKW-Standorte. KW ist von der UKW-Frage unabhängig.
* **Empfänger:** Der Si4732 ist ein DSP-Empfängerchip (UKW, MW, LW, KW, RDS). Der ESP32 steuert ihn. Abstimmung digital per Drehencoder. Langwelle wird in der Firmware ausgeblendet.

### Begriffe

| Begriff | Bedeutung |
|---|---|
| Fork | Kopie eines offenen Software-Projekts, die wir für unsere Hardware anpassen (hier ats-mini) |
| DSP | Digitaler Signalprozessor. Der Si4732 verarbeitet das Funksignal intern digital und gibt fertigen Ton aus |
| RDS | Zusatzdaten im UKW-Signal, z.B. Sendername |
| LDO | Linearer Spannungsregler, schaltet nicht und stört daher kaum |
| THT | Durchsteckmontage, Bauteile mit Beinchen (im Gegensatz zu SMD) |
| OTA | Firmware-Update per Funk (WLAN) |
| BLE | Bluetooth Low Energy (Daten, kein Audio an Lautsprecher) |

## 2. Funktionen

Priorität: **M** = muss (erster Prototyp), **S** = soll, **K** = kann. Quelle: **Fork** = im ATS-Mini-Fork vorhanden, **neu** = muss ergänzt werden.

| Nr | Funktion | Prio | Quelle | Bemerkung |
|---|---|---|---|---|
| F1 | Empfang UKW, MW, KW | M | Fork | Langwelle ausgeblendet |
| F2 | Abstimmung per Drehencoder mit Fein- und Grobschritt je Band | M | Fork/neu | Richtwerte UKW 50 bis 100 kHz, MW 9 kHz, KW 5 kHz, feinerer Schritt per Klick, Werte prüfen. Optional Beschleunigung |
| F3 | Speicherplätze, Schweizer Sender als Voreinstellung | M | Fork/neu | |
| F4 | Grosse Frequenzanzeige | M | neu | Display 2.0" ST7789V, 240x320 |
| F5 | Akkuanzeige gross, mit Warnung | M | Fork/neu | |
| F6 | Auto-Aus und Sleep-Timer | M | neu | |
| F7 | Lautstärke mit Begrenzung (Kopfhörer) | M | neu | Poti am Modul oder Software, siehe O7 |
| F8 | Einfachmodus: 3 Bänder, wenige Tasten | S | neu | |
| F10 | WLAN nur zum Firmware-Update eingeschaltet, sonst aus. BLE aus | S | neu | Stör- und Stromgründe (T7) |
| F15 | Watchdog, Brown-out, Neustart mit letzter Frequenz | S | Fork? | prüfen, was der Fork mitbringt (O13) |

## 3. Anforderungen

### Gerät (G)

| Nr | Anforderung | Bemerkung |
|---|---|---|
| G1 | Wenig Stromverbrauch | Display abschaltbar, WLAN nur zum Update, Auto-Aus |
| G2 | Gute Empfangsqualität | UKW, MW, KW. Teleskop, Ferritstab, BNC |
| G3 | Störarm | Kein Schaltregler. Messen statt behaupten. Ziel: MW und KW im Test brauchbar |
| G4 | Einfache Handhabung | Symbole, ev. gelasert, grosse Anzeige |
| G5 | Lautstärkebegrenzung | vor allem Kopfhörer |
| G6 | Hauptschalter und Tiefentladeschutz | |
| G7 | Robust: Falltest aus 1 m | Abnahmekriterium, Protokoll (T10) |
| G8 | Spritzwasser und Staub, Ziel IP54 | offene Ausschnitte machen es schwierig, evtl. zu "spritzwassergeschützt" abschwächen (O17) |
| G9 | Akku aufladbar, gesichert | Variante offen (O5) |

### Hardware und Platine (H)

| Nr | Anforderung | Bemerkung |
|---|---|---|
| H1 | Platinen in KiCad 9, Gerber im Repo | DRC vor jeder Bestellung. Siebdruck: Copyright und Repo-Link |
| H2 | Durchsteckmontage (THT), Chips als Module | Nachbau ohne Heissluft. Vorschlag, noch nicht entschieden |
| H3 | Empfängerchip als Modul auf Stiftleisten | Si4732 ist SMD, kommt vorbestückt (siehe T1) |
| H4 | ESP32 und Empfängermodul gesteckt, der Rest gelötet | weiche Sicherung (Schaum oder TPU), kein starrer Druck |
| H5 | Kein Schaltnetzteil | linearer Lader, LDO. Ausnahme PAM8403 (Messung, O7) |
| H6 | Alle Teile einzeln ersetzbar | Akku, Display, Schalter, Taster, Buchsen, Lautsprecher und Module hängen an Steckverbindern (Flachband, Kabelstecker, Stiftleisten), nichts ist fest verlötet oder verklebt. Das Mainboard lässt sich als Ganzes herausnehmen und ersetzen |

### Gehäuse (C)

| Nr | Anforderung | Bemerkung |
|---|---|---|
| C1 | 3D-Druck | Druckzeit höchstens 2 bis 3 Stunden |
| C2 | Beschriftung mit Symbolen | |
| C3 | Dichtungen an Öffnungen | siehe G8 |
| C4 | Montage mit Schrauben | Jedes Teil hat eigene Montagepunkte. Kleben nur wo es um Wasserdichtheit geht, sonst Schrauben oder Gummidichtungen |

### Notfall und Beschaffung (N, B)

| Nr | Anforderung | Bemerkung |
|---|---|---|
| N1 | Laden ohne Netz | Powerbank, externes Solar, Reservezelle. Eigenes Konzept, nicht begonnen |
| N2 | Lange Laufzeit | messen, nicht schätzen |
| B1 | Lieferkette prüfen | Ersatz, Mindestmengen, Lieferzeiten, Clones |
| B2 | CE und EMV vor einem Verkauf klären | WLAN sendet, reiner Empfang ist unkritisch |

## 4. Technik und Entscheide (T)

**T1 Empfänger.** Si4732 als Modul. Eigenes **RX-Board** im Repo `MaShaoDe/RX-Board-Si4732` (Quelle für alle Details). Rev A (44 x 30 mm) ist bei einem Hersteller in Shenzhen in Fertigung und wird voll bestückt geliefert. **Rev A kann UKW, MW und LW, aber noch kein KW**, die Kurzwelle kommt erst mit Rev B. Schnittstelle J1 (Buchsenleiste 1x9): AUDIO_L, AUDIO_R, GND, 3V3, SDA, SCL, RST, INT, GND. Die Hauptplatine muss dieser Reihenfolge folgen. Zusätzlich 1 Si4732-Modul bestellt (Vergleich und Breadboard). Der Si4732 gibt analoges Audio aus, ein I2S-Codec ist nicht nötig.

**T2 Mikrocontroller.** ESP32-S3-DevKitC-1 (N16R8) auf Buchsenleisten. Der Fork zielt auf den S3. Modul wird anhand des Inventars bestätigt (O1).

| Anforderung | Grund |
|---|---|
| Chip ESP32-S3 | Fork, WLAN, BLE |
| Flash mindestens 8 MB, besser 16 MB | Firmware des Fork |
| PSRAM vorhanden | Build-Varianten des Fork, Display-Puffer |
| mindestens 14 freie GPIOs | Bedarf ca. 15: I2C 2, Si4732-Reset 1, Display (SPI) 5 bis 6, Encoder 3, Verstärker ein/aus 1, Klinkenkontakt 1, Akku-ADC 1, Ladestatus 1 bis 2 |
| Stiftleisten 2 x 22 (44 Pins), Raster 2.54 mm | Steckplatz |
| Eigener 3.3-V-Regler, 5-V- oder VBAT-Eingang | Versorgung |
| Flashen | Vorschlag: erstes Flashen über USB vor dem Einstecken des ESP32 aufs Mainboard, danach Updates per OTA (WLAN), kein USB-Anschluss am Gehäuse. Rettung nach Fehlschlag: Gehäuse öffnen, ESP32 per USB flashen. Noch nicht entschieden, siehe O22 |

Beim N16R8 meiden (gegen Datenblatt prüfen): GPIO 0, 3, 45, 46 (Strapping), 19, 20 (USB), 26 bis 32 (Flash), 33 bis 37 (Octal-PSRAM). Stromwerte (S3 ca. 40 bis 60 mA) sind Grössenordnungen, messen.

**T3 Software.** Basis: Fork von esp32-si4732/ats-mini (MIT). Anzupassen: Pinbelegung, Displayauflösung (Original 320x170) und Layout, Treiber, Verstärker-Enable (Aufwand klein bis mittel). Fallback: PU2CLR SI4735-Bibliothek (MIT) mit eigenem schlanken Sketch.

**T4 Antennen.** Teleskopantenne an einer BNC-Buchse am Gehäuse für UKW und KW (Typ und Länge offen). Kabel zum RX-Board: dünnes 50-Ohm-Koax (3 bis 4 mm), Länge nach Layout (Vorschlag 10 bis 15 cm). Rev A: an die Lötpads gelötet. Ab Rev B bekommt das RX-Board je Antenneneingang eine U.FL-Buchse (IPEX), das Kabel wird steckbar. Ferritstab für MW. Zusätzlich ein Anschluss für eine Drahtantenne für MW und eventuell KW (KW schwach, besser 5 bis 10 m Draht), als Polklemme mit Querbohrung und Bananenbuchse. UKW und AM haben getrennte Eingänge, Umschaltung klären. Schutzdioden gegen statische Aufladung, Aussenantenne bei Gewitter trennen. Ferritstab auf Abstand zu Stahlzelle, Lautsprechermagnet, Metall und Abschirmfolie.

**T5 Strom.** Entscheide (2026-11-15): ESP32 über LDO am 3V3-Pin des DevKits (kein Boost, kein Schaltregler). Pads für 14650-Halter und JST für LiPo 103665, nur einer bestückt. TP4056 und PAM8403 als Module auf Stiftleisten. Elektronik für 1 Zelle (3.0 bis 4.2 V).

| | LiPo 103665 | NCR18650B im Halter |
|---|---|---|
| Kapazität | 3000 mAh (Aufdruck) | ca. 3400 mAh laut Typ, messen |
| Schutzschaltung | auf Zelle, Aufdrucke lesen | keine, Schutz auf Platine |
| Robustheit | Folie, empfindlich | Stahlhülle |

* 14500 (800 mAh, 3.7 V) nur als Notfall- oder Reservezelle, Verwechslungsgefahr mit AA, deutlich kennzeichnen. 14650: Daten ungeprüft (O5).
* Schutz: ungeschützte Zellen bekommen Schutz-IC mit Doppel-MOSFET. Verpolschutz mit Schottky-Diode (z.B. 1N5819) in der Lastleitung nach dem Akku (verliert ca. 0.3 V, messen). Pufferkondensator gegen Kontaktunterbrüche.
* Laden über eine DC-Hohlsteckerbuchse, Aussendurchmesser 5.5 mm (Innendurchmesser offen), nur 5 V und 1 A, auf dem Gehäuse beschriftet. Am Eingang vor dem Lader: Überspannungsschutz, Filter und Glättung (Werte offen). Linearer Lader (TP4056-Typ mit Schutz). Laden und Hören nicht gleichzeitig, die Last wird beim Anstecken getrennt. Keine Schaltlader im Gerät. Solar und Autoadapter nur extern mit 5-V-Ausgang. Beim Flashen über USB (offen gehaltenes Gehäuse) kann das ESP32-Modul mit dem DC-Eingang gleichzeitig verbunden sein: Die Schaltung soll Rückspeisung in den LDO und in den Regler des ESP32-Moduls verhindern (Lösung offen, O22).
* Versorgung: Akku, Ferrit und Kondensator, dann LDO 3.3 V. Vorschlag: **AP2112K-3.3** (Datenblatt Diodes: 600 mA, Dropout typisch 250 mV bei 600 mA, 55 µA Ruhestrom, 50 µV Rauschen, 65 dB Unterdrückung). Der ESP32-S3 braucht 3.0 bis 3.6 V und mindestens 500 mA Quelle (Espressif), der Si4732 2.7 bis 3.6 V. Der LDO regelt gerechnet bis Akku etwa 3.7 bis 3.9 V, darunter folgt der Ausgang dem Akku, der ESP32 hält bis Akku etwa 3.5 bis 3.6 V. Abschaltschwelle in der Firmware um 3.5 V, nach Breadboard-Test 7d festlegen. LF33CV (400 mV Dropout, 500 µA Ruhestrom) nur Notlösung.
* Laufzeit grob 10 bis 25 Stunden (ca. 100 mA ohne Verstärker plus 50 bis 150 mA Verstärker, Schätzung, messen).
* Solar nur extern oder als getrennter Ladevorgang.

**T6 Audio.**
1. Interner Lautsprecher Visaton K 50 (8 Ω, 2 W, 50 x 17 mm) in geschlossenem Resonanzraum im Gehäuse, am Gehäuse befestigt.
2. 3.5-mm-Klinke (Kopfhörer, Line-Out). **Korrektur:** Der Si4732 liefert nur Line-Pegel (Datenblatt Si473x-B20: 80 mV eff typisch, Last mindestens 10 kΩ, höchstens 50 pF). Das Si4732-A10-Datenblatt in unseren Unterlagen nennt diese Werte nicht, sie sind zu messen. Kopfhörer direkt am Chip geht nicht (das Mikroe-Click nutzt deshalb einen LM4910). Entscheid (Vorschlag): Kopfhörerverstärker **TPA6132A2** auf dem Basisboard (Datenblatt TI: 2.3 bis 5.5 V, 2.1 mA, 25 mW an 16 Ω, ohne Ausgangskondensatoren, Verstärkung -6 / 0 / 3 / 6 dB, feste Maximalleistung unabhängig von der Versorgung, Gehäuse WQFN 3x3 mm, bei JLCPCB bestückbar). Der Schaltkontakt der Buchse geht an GPIO 6, die Firmware schaltet dann die PAM8403-Versorgung (GPIO 5) ab. Audio-Übertrager 1:1 gegen Brummschleifen als Option testen. Alternative TPA6139A2 (TSSOP-14) wurde verworfen: 25 mA Ruhestrom.

Verstärker PAM8403 (HW-012, 20 Stück vorhanden), Class D, Vorschlag für den Lautsprecher. Datenblatt Diodes: 2.5 bis 5.5 V, 24 dB, an 8 Ω bei 1 % Klirr 0.72 W (3.6 V) und 0.45 W (3.2 V), Ruhestrom 10 mA bei 3.6 V. Ausgänge BTL, Lautsprecher-Minus nie an Masse. Der Chip hat einen Shutdown-Pin, am Modul ist er vermutlich nicht herausgeführt, darum wird die Versorgung geschaltet (GPIO 5). Der PAM8403 treibt keine Kopfhörer (BTL, kein Massebezug). Pegel: 80 mV Chip nach Mischer etwa 38 mV, nach Verstärker etwa 0.045 W am K 50 (Annahme Eingang 10 kΩ, messen). Mono ist Standard: zwei gleiche Widerstände (22 kΩ, damit die Chip-Last über 10 kΩ bleibt) mischen L und R, 3-poliger Jumper wählt Radio-L oder Mischer. Offen bleibt die Störung: Class D schaltet im Bereich der LW/MW-Oberwellen, Breadboard-Test 5e entscheidet. Ausweichlösung bei MW-Störungen: LM386 oder Linearverstärker.

**T7 Störarmes Design.** Erfahrung: Solarregler (MPPT) am gleichen Akku im gleichen Gehäuse verschlechterte den Empfang deutlich, Oberwellen der Schaltwandler fallen in MW und KW. Regeln:
1. Laden oder hören, nicht beides. Linearer Lader statt Schaltregler.
2. Empfängerversorgung über Ferrit, Kondensator, LDO.
3. Ferritantenne weit weg von MCU, Display, Lader und Verstärker.
4. Display ohne PWM-Dimmung, WLAN nur zum Update.
5. Kurze Leitungen, kurze Lautsprecherleitungen, Ferrit und Filter am PAM8403.
6. Abschirmung nur um Störquellen (ESP32, Display, Lader), an einem Punkt geerdet, nie nahe am Ferritstab, nie Kontakt zu Zelle oder Federkontakten. Erst ohne Folie messen, dann mit.
7. Messen: Radio auf leeren MW-Kanal, Störquellen einzeln zuschalten (ESP32-Modul, Lader, Verstärker). 

**T8 Platine.** Die Hauptplatine trägt ESP32-Steckplatz, Display, Encoder, Strom und Audio. Das RX-Board steckt über J1 auf. Trägerplatine in KiCad 9 mit Buchsenleisten für ESP32-S3 und RX-Board. Fertigung bei JLCPCB oder PCBWay. Pinbelegung auf den N16R8 (strengste Variante) auslegen. Auf der Platine: Encoder, Display, LDO, Audioteil, Akkupads und JST, Schutz, Jumper Mono/Stereo, Anschlüsse Antenne und Lader. Layout: Trennung Lader, MCU, Audio und Empfang, durchgehende Massefläche, Ferritstab am Rand. Nur THT und Module.

**T9 Gehäuse.** Maximal ca. 180 x 120 mm, Höhe offen (hängt von Akkufach und Lautsprecher ab), ohne Stützmaterial druckbar (Überhang höchstens 45 Grad), PETG (PLA nur innen), keine Metall- oder Kohlefaser-Filamente. 0.2 mm Spiel, M3-Schrauben mit Gewindeeinsätzen. Zweiteilig, 4 Schrauben, Batteriefach getrennt zugänglich. Wandstärke ca. 2 bis 2.4 mm, Kanten gerundet. Kunststoff schirmt nicht, der Empfang wird über Abstand und Layout geschützt. Öffnungen: Display, Encoder, Poti (Variante), Lautsprecher, BNC, Teleskop, Klinke, DC-Buchse. Akku in eigener Kammer mit Trennwand. CAD parametrisch (OpenSCAD oder FreeCAD) plus STEP und STL im Repo.

**T10 Robustheit.** Abnahme: Falltest aus 1 m auf Holz oder Fliesen (flach vorne und hinten, Kante, Ecke, mit ausgefahrener Antenne). Danach: kein Riss, nichts lose, Radio startet, Abstimmung, Display, Ton und Laden funktionieren. Protokoll mit Datum, Gehäuse-Version, Material, Befund. Prinzipien:
1. Last nie über die Platine. Tragend sind Gehäusewände und Stützsäulen, keine starren Rippen auf Modul oder Platine.
2. Weich halten: TPU-Pads oder Schaumstoff, nur leicht andrücken.
3. Modul mit Seitenführung, gedrehte Präzisionskontakte statt einfacher Leisten.
4. Platine auf 4 M3-Abstandsbolzen, bei Bedarf Gummitüllen.
5. Akku (schwerstes Teil): eigene Kammer, seitlich geführt, gepolstert, von oben gesichert. Halter gelötet, aber zusätzlich vom Gehäuse gehalten, Zelle mit Klettband oder lösbarem Kabelbinder.
6. Mechanische Lasten trägt das Gehäuse: DC-Buchse, BNC und Klinke mit Mutter verschraubt, Teleskop am Gehäuse verankert.
7. Steckverbinder mit Zugentlastung, keine frei hängenden Kabel.
8. Grosse Bauteile mit Tropfen Kleber sichern. Kleber offen (O14): Niedertemperatur-Heissleim, neutral vernetzendes Silikon (nie essigsäurehaltig) oder Epoxid.
9. Firmware: Watchdog und Brown-out aktivieren, bei Hänger neu starten (F15).

## 5. Lizenzen (L)

| Nr | Punkt | Stand |
|---|---|---|
| L1 | Hardware CERN-OHL-P-2.0, Doku CC-BY-4.0, Firmware folgt dem Fork (ATS Mini: MIT) | festgelegt |
| L2 | Quelltext nennt Sunnygold als Autor. Ob NC-lizenzierter Code im MIT-Repo steckt, ist nicht geklärt. Vor kostenpflichtiger Verbreitung beim Maintainer nachfragen (GitHub Discussions) | **offen (O12)** |

Autor und Copyright: `FerienBSD aka Marcel Sauder`.

## 6. Offene Punkte (O)

| Nr | Punkt | Stand |
|---|---|---|
| O1 | ESP32-S3-DevKitC-1: vorhandene Module durchgehen (Stückzahl, Masse, Reihenabstand, Aufdruck N16R8 oder anderes), Modul wählen | offen |
| O2 | Si4732-Modul: 1 Stück bestellt. Datenblatt prüfen (getrennte FM/AM-Eingänge, Audio L/R, Quarz, Raster) | bestellt, Lieferung offen |
| O3 | RX-Board Rev A: Lieferung abwarten. Rev A hat kein KW, Rev B (mit KW über AMI, Umschalter) nötig. KW-Test erst mit Rev B | in Fertigung |
| O4 | Display 2.0" ST7789V: Pins, Stiftleiste, Anpassung von Auflösung und Layout im Fork | offen |
| O5 | Akku: Kapazität 18650 und 14500 messen, Aufdrucke LiPo-Schutz lesen, 14650 aufnehmen oder streichen, JST und Verpolschutz, Vergleich im Prototyp | offen |
| O6 | LDO: AP2112K-3.3 vorgeschlagen. Offen: Dropout-Kurve und Abschaltschwelle im Breadboard-Test 7d, ESP32-Einspeisung am 3V3-Pin bestätigen | Vorschlag, Messung offen |
| O7 | Verstärker: PAM8403 als Vorschlag. Offen: Eingangswiderstand HW-012 messen, MW-Störung (Test 5e), Resonanzraum K 50, Lautsprecher-Box (Ohm, Watt, Masse), Lautstärke per Poti (A) oder Software (B). Lautstärkebegrenzung für Kopfhörer: TPA6132A2 hat feste Maximalleistung, Verstärkung wählen | offen |
| O9 | Ferritstab: SL8X50MW70T (8 x 50 mm, AN383) oder Stab aus dem Sortiment mit 180 bis 450 µH, Induktivität messen. FM an FMI, MW/LW an AMI. KW-Eingang (FMI oder AMI) offen bis Rev-A-Test P4 und P5, danach KW-Umschalter in Rev B | Vorschlag, KW offen |
| O10 | Stückliste (BOM), Blockschaltbild und Verdrahtungsplan für den Breadboard-Test | erledigt (docs/cookbook-prototyp.md) |
| O12 | Lizenzfrage L2 beim Maintainer klären | offen |
| O13 | Was bringt der Fork an Watchdog und Neustart mit (F15) | offen |
| O14 | Kleber festlegen (T10) | offen |
| O15 | Falltest: Protokollvorlage und Testplan | offen |
| O16 | Störtest: Quellen einzeln zuschalten, Abschirmung mit und ohne Folie | offen |
| O17 | IP54: lösen oder Ziel abschwächen (G8) | offen |
| O18 | Notfall-Laden (N1) als eigenes Konzept | offen |
| O20 | Drucker und Bauraum im Club und FabLab, CAD-Werkzeug | offen |
| O21 | Namensprüfung (Swissreg/IGE und GitHub) vor Veröffentlichung | offen |
| O22 | OTA statt USB-Anschluss am Gehäuse prüfen (Vorschlag): Der ATS-Mini-Fork kann OTA laut Doku (Menü Settings, Update FW, oder Web-Interface, manueller Upload ohne Internet möglich, WLAN standardmässig aus). Offen: Speicherbedarf für 2 Firmware-Abbilder (Partitionstabelle des Fork prüfen, 8 Zeilen, Grössen nicht gelesen), WLAN nur zum Update einschalten (F10), Vorschlag: per Menüeintrag Update mit dem Encoder, Sicherheit des Updates. Bei einem Fehlschlag verlangt der Fork teils USB. Wenn OTA nicht geht: USB-Weg (Gehäuseöffnung mit Stopfen oder Einbaubuchse nur mit D+, D- und GND). Rückspeisung bei USB und DC-Eingang gleichzeitig: Lösung offen (z.B. Schottky-Diode hinter dem LDO, Spannungsabfall ca. 0.3 V, LDO-Typ auf Rückstrom prüfen) | offen |
| O23 | Kopfhörerverstärker TPA6132A2: Testmodul oder Mini-Platine für den Lochraster-Test beschaffen (Chip nur WQFN 3x3, ohne Heissluft nicht von Hand lötbar, Fab Lab oder Funkclub). Datenblatt-Details (Beschaltung, Verstärkung) vor dem Layout im Basisboard prüfen | offen |

## 7. Quellen

* Parlament.ch, Ständerat 9.12.2025 (UKW-Abschaltung aufgehoben)
* cash.ch/AWP und PCtipp (SRG zurück auf UKW ab Mitte November 2026)
* turi2 (UKW-Konzessionen 2027 bis 2031)
* ATS Mini: github.com/esp32-si4732/ats-mini (MIT), Doku esp32-si4732.github.io/ats-mini
* PU2CLR SI4735: pu2clr.github.io/SI4735 (MIT)
* Visaton K 50 (Art. 2901), Datenblatt von Visaton

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
