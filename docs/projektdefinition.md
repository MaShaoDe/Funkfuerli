# Funkfüürli: Projektdefinition (Stand 2026-11-19, Entwurf)

Dies ist das Hauptdokument. Alle anderen Dokumente (Pinplan, Stückliste, Breadboard, Firmware) verweisen mit den Nummern (F1, G3, T5, O7 ...) hierher und wiederholen nichts. Ersetzt `konzept.md` und `anforderungen.md`. Der Projektstand steht in `STATUS.md`, die Aufgabenliste in der README.

Notfallradio, Hardware und Software. UKW, MW und KW, Akku mit Ladeanschluss, 3D-gedrucktes Gehäuse, eigene Platine. Open Source. Grundsatz: offene Software forken und anpassen, Hardware (Platine, Gehäuse) ist ein eigenes Design.

## 1. Rahmen

* **UKW in der Schweiz:** Das Parlament hat die Abschaltung Ende 2026 am 9.12.2025 aufgehoben. Die SRG sendet laut Bakom-Konzession ab Mitte November 2026 wieder über erste UKW-Standorte (rund 80 % der Bevölkerung). Neue Privatradio-Konzessionen gelten von Januar 2027 bis Ende 2031. UKW bleibt politisch umstritten, KW ist davon unabhängig. Darum nicht nur UKW.
* **Kein SDR:** Der Si4732 ist ein DSP-Empfängerchip (UKW, MW, LW, KW, RDS) ohne I/Q-Daten. Der ESP32 steuert ihn nur. Abstimmung digital per Drehencoder. Langwelle wird in der Firmware ausgeblendet. Ein Wasserfall geht nur im Projekt Wellenjäger, hier nur ein langsamer Bandscope (RSSI-Durchlauf).
* **Abgrenzung:** Dieses Dokument beschreibt nur das Radio (Hardware und Software). Kurse, Workshops und Schulungsmaterial sind nicht Inhalt. Amateurfunk (SSB, Bandfilter, SDR, Wasserfall) steht im Projekt Wellenjäger (github.com/MaShaoDe/Wellenjaeger).

### Begriffe

| Begriff | Bedeutung |
|---|---|
| Fork | Kopie eines offenen Software-Projekts, die wir für unsere Hardware anpassen (hier ats-mini) |
| DSP | Digitaler Signalprozessor. Der Si4732 verarbeitet das Funksignal intern digital und gibt fertigen Ton aus |
| SDR | Software Defined Radio: Das Funksignal wird roh digitalisiert und per Software ausgewertet. Das Funkfüürli ist kein SDR (der Wellenjäger schon) |
| I/Q | Rohdaten eines SDR. Nur damit ist ein Wasserfall möglich |
| RDS | Zusatzdaten im UKW-Signal, z.B. Sendername |
| SSB | Einseitenband, Betriebsart der Funkamateure auf Kurzwelle. Hier nur optional (F12) |
| RFI | Funkstörung (Radio Frequency Interference). "RFI-Jagd" = Störquellen suchen |
| LDO | Linearer Spannungsregler, schaltet nicht und stört daher kaum |
| THT | Durchsteckmontage, Bauteile mit Beinchen (im Gegensatz zu SMD) |
| OTA | Firmware-Update per Funk (WLAN) |
| BLE | Bluetooth Low Energy (Daten, kein Audio an Lautsprecher) |
| A2DP | Bluetooth-Audio zu Lautsprecher oder Kopfhörer |

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
| F9 | S-Meter und Bandscan (RSSI-Durchlauf) | S | Fork/neu | |
| F10 | WLAN und BLE aus beim Hören | S | neu | Stör- und Stromgründe (T7) |
| F11 | Senderliste EIBI, WLAN-Webseite, OTA, BLE, 2 Layouts | K | Fork | vorhanden, nicht Priorität |
| F12 | SSB (Amateurfunk) | K | Fork | nur was der Fork mitbringt, Ausbau im Wellenjäger. Patch lädt der Nutzer selbst (L4) |
| F13 | Bluetooth-Audio zu Boombox | K | neu | siehe T6 |
| F14 | Notfall-Extras (Lampe, Alarm) | K | neu | offen, vorerst nur Radio |
| F15 | Watchdog, Brown-out, Neustart mit letzter Frequenz | S | Fork? | prüfen, was der Fork mitbringt (O13) |

## 3. Anforderungen

### Gerät (G)

| Nr | Anforderung | Bemerkung |
|---|---|---|
| G1 | Wenig Stromverbrauch | Display abschaltbar, WLAN und BT aus beim Hören, Auto-Aus |
| G2 | Gute Empfangsqualität | UKW, MW, KW. Teleskop, Ferritstab, BNC |
| G3 | Störarm | Kein Schaltregler. Messen statt behaupten. Ziel: MW und KW im Test brauchbar, nicht "alles entstört" |
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
| H6 | Reparierbar | gesteckte Module sind tauschbar |

### Gehäuse (C)

| Nr | Anforderung | Bemerkung |
|---|---|---|
| C1 | 3D-Druck | Druckzeit höchstens 2 bis 3 Stunden |
| C2 | Beschriftung mit Symbolen | kein Rufzeichen, keine privaten Angaben |
| C3 | Dichtungen an Öffnungen | siehe G8 |

### Notfall und Beschaffung (N, B)

| Nr | Anforderung | Bemerkung |
|---|---|---|
| N1 | Laden ohne Netz | Powerbank, externes Solar, Reservezelle. Eigenes Konzept, nicht begonnen |
| N2 | Lange Laufzeit | messen, nicht schätzen |
| B1 | Lieferkette prüfen | Ersatz, Mindestmengen, Lieferzeiten, Clones |
| B2 | CE und EMV vor einem Verkauf klären | BT und WLAN senden, reiner Empfang ist unkritisch |

## 4. Technik und Entscheide (T)

**T1 Empfänger.** Si4732 als Modul. Eigenes **RX-Board** im Repo `MaShaoDe/RX-Board-Si4732` (Quelle für alle Details). Rev A (44 x 30 mm) ist bei einem Hersteller in Shenzhen in Fertigung und wird voll bestückt geliefert. **Rev A kann UKW, MW und LW, aber noch kein KW**, die Kurzwelle kommt erst mit Rev B. Schnittstelle J1 (Buchsenleiste 1x9): AUDIO_L, AUDIO_R, GND, 3V3, SDA, SCL, RST, INT, GND. Die Hauptplatine muss dieser Reihenfolge folgen. Zusätzlich 1 Si4732-Modul bestellt (Vergleich und Breadboard). Der Si4732 gibt analoges Audio aus, ein I2S-Codec ist nicht nötig.

**T2 Mikrocontroller.** ESP32-S3-DevKitC-1 (N16R8) auf Buchsenleisten, wie beim Wellenjäger. Der Fork zielt auf den S3. Modul wird anhand des Inventars bestätigt (O1).

| Anforderung | Grund |
|---|---|
| Chip ESP32-S3 | Fork, SSB, WLAN, BLE |
| Flash mindestens 8 MB, besser 16 MB | Firmware mit OTA, Senderliste, Webseite |
| PSRAM vorhanden | Build-Varianten des Fork, Display-Puffer |
| mindestens 14 freie GPIOs | Bedarf ca. 17: I2C 2, Si4732-Reset 1, Display (SPI) 5 bis 6, Encoder 3, Verstärker ein/aus 1, Klinkenkontakt 1, BT 2, Akku-ADC 1, Ladestatus 1 bis 2 |
| Stiftleisten 2 x 22, Raster 2.54 mm | Steckplatz |
| Eigener 3.3-V-Regler, 5-V- oder VBAT-Eingang | Versorgung |
| USB zum Flashen | Nutzer flasht selbst |

Beim N16R8 meiden (gegen Datenblatt prüfen): GPIO 0, 3, 45, 46 (Strapping), 19, 20 (USB), 26 bis 32 (Flash), 33 bis 37 (Octal-PSRAM). Ein klassischer ESP32 hat A2DP, aber der Fork läuft nicht darauf. C3, C6, C2 sind nicht vorgesehen. Stromwerte (S3 ca. 40 bis 60 mA) sind Grössenordnungen, messen.

**T3 Software.** Basis: Fork von esp32-si4732/ats-mini (MIT). Anzupassen: Pinbelegung, Displayauflösung (Original 320x170) und Layout, Treiber, Verstärker-Enable (Aufwand klein bis mittel). Fallback: PU2CLR SI4735-Bibliothek (MIT) mit eigenem schlanken Sketch.

**T4 Antennen.** Teleskop für UKW und KW (KW schwach, besser 5 bis 10 m Draht an BNC). Ferritstab für MW. BNC-Buchse extern. UKW und AM haben getrennte Eingänge, Umschaltung klären. Schutzdioden gegen statische Aufladung, Aussenantenne bei Gewitter trennen. Ferritstab auf Abstand zu Stahlzelle, Lautsprechermagnet, Metall und Abschirmfolie.

**T5 Strom.** Entscheide (2026-11-15): ESP32 über LDO am 3V3-Pin des DevKits (kein Boost, kein Schaltregler). Pads für 14650-Halter und JST für LiPo 103665, nur einer bestückt. TP4056 und PAM8403 als Module auf Stiftleisten. Elektronik für 1 Zelle (3.0 bis 4.2 V).

| | LiPo 103665 | NCR18650B im Halter |
|---|---|---|
| Kapazität | 3000 mAh (Aufdruck) | ca. 3400 mAh laut Typ, messen |
| Schutzschaltung | auf Zelle, Aufdrucke lesen | keine, Schutz auf Platine |
| Robustheit | Folie, empfindlich | Stahlhülle |

* 14500 (800 mAh, 3.7 V) nur als Notfall- oder Reservezelle, Verwechslungsgefahr mit AA, deutlich kennzeichnen. 14650 neu aufgenommen, Daten ungeprüft (O5).
* Schutz: ungeschützte Zellen bekommen Schutz-IC mit Doppel-MOSFET. Verpolschutz mit Schottky-Diode (z.B. 1N5819) in der Lastleitung nach dem Akku (verliert ca. 0.3 V, messen). Pufferkondensator gegen Kontaktunterbrüche.
* Laden über USB-C mit linearem Lader (TP4056-Typ mit Schutz). Laden und Hören nicht gleichzeitig, die Last wird beim Anstecken getrennt. Keine Schaltlader im Gerät.
* Versorgung: Akku, Ferrit und Kondensator, dann LDO 3.3 V (Kandidat LF33CV, mind. 500 mA, zu prüfen).
* Laufzeit grob 10 bis 25 Stunden (ca. 100 mA ohne Verstärker plus 50 bis 150 mA Verstärker, Schätzung, messen).
* Keine 9-V-Blockbatterie. Solar nur extern oder als getrennter Ladevorgang.

**T6 Audio.**
1. Interner Lautsprecher Visaton K 50 (8 Ω, 2 W, 50 x 17 mm) in geschlossenem Resonanzraum im Gehäuse, am Gehäuse befestigt.
2. 3.5-mm-Klinke (Kopfhörer, Line-Out), stereo direkt vom Si4732. Schaltkontakt trennt den Lautsprecher. Audio-Übertrager 1:1 gegen Brummschleifen als Option testen.
3. Bluetooth (Option F13): Der S3 hat nur BLE, kein A2DP. Empfehlung: externes Sendemodul auf Steckplatz, per Taster ein/aus. Latenz 100 bis 200 ms, Zusatzstrom 30 bis 50 mA, kann in MW/KW stören (messen).

Verstärker PAM8403 (HW-012, 20 Stück vorhanden), Class D, Betrieb ab ca. 2.5 V. Ausgänge BTL, Lautsprecher-Minus nie an Masse. Standby vermutlich nicht herausgeführt, dann Versorgung schalten. Mono ist Standard: zwei gleiche Widerstände mischen L und R, 3-poliger Jumper wählt Radio-L oder Mischer. Ausweichlösung bei MW-Störungen: LM386.

**T7 Störarmes Design.** Erfahrung: Solarregler (MPPT) am gleichen Akku im gleichen Gehäuse verschlechterte den Empfang deutlich, Oberwellen der Schaltwandler fallen in MW und KW. Regeln:
1. Laden oder hören, nicht beides. Linearer Lader statt Schaltregler.
2. Empfängerversorgung über Ferrit, Kondensator, LDO.
3. Ferritantenne weit weg von MCU, Display, Lader, BT-Modul und Verstärker.
4. Display ohne PWM-Dimmung, WLAN und BT aus beim Hören.
5. Kurze Leitungen, kurze Lautsprecherleitungen, Ferrit und Filter am PAM8403.
6. Abschirmung nur um Störquellen (ESP32, Display, Lader), an einem Punkt geerdet, nie nahe am Ferritstab, nie Kontakt zu Zelle oder Federkontakten. Erst ohne Folie messen, dann mit.
7. Messen: Radio auf leeren MW-Kanal, Störquellen einzeln zuschalten (ESP32-Modul, Lader, Verstärker, BT-Modul). 

**T8 Platine.** Vorschlag (O22): Die Hauptplatine mit ESP32-Steckplatz, Display, Encoder, Strom und Audio wird so ausgelegt, dass sie auch für den Wellenjäger taugt. Das Funkmodul steckt auf (Funkfüürli: RX-Board mit Si4732 über J1, Wellenjäger: SDR-Teil). Das RX-Board selbst taugt nicht als SDR-Modul (kein I/Q, J1 ohne I2S). Trägerplatine in KiCad 9 mit Buchsenleisten für ESP32-S3 und RX-Board. Fertigung bei JLCPCB oder PCBWay. Pinbelegung auf den N16R8 (strengste Variante) auslegen. Auf der Platine: Encoder, Display, LDO, Audioteil, Steckplatz BT-Modul, Akkupads und JST, Schutz, Jumper Mono/Stereo, Anschlüsse Antenne und Lader. Layout: Trennung Lader, MCU, Audio/BT und Empfang, durchgehende Massefläche, Ferritstab am Rand. Nur THT und Module.

**T9 Gehäuse.** Maximal ca. 180 x 120 mm, ohne Stützmaterial druckbar (Überhang höchstens 45 Grad), PETG (PLA nur innen), keine Metall- oder Kohlefaser-Filamente. 0.2 mm Spiel, M3-Schrauben mit Gewindeeinsätzen. Zweiteilig, 4 Schrauben, Batteriefach getrennt zugänglich. Wandstärke ca. 2 bis 2.4 mm, Kanten gerundet. Kunststoff schirmt nicht, der Empfang wird über Abstand und Layout geschützt. Öffnungen: Display, Encoder, Poti (Variante), Lautsprecher, BNC, Teleskop, Klinke, USB-C, BT-Taster. Akku in eigener Kammer mit Trennwand. CAD parametrisch (OpenSCAD oder FreeCAD) plus STEP und STL im Repo.

**T10 Robustheit.** Abnahme: Falltest aus 1 m auf Holz oder Fliesen (flach vorne und hinten, Kante, Ecke, mit ausgefahrener Antenne). Danach: kein Riss, nichts lose, Radio startet, Abstimmung, Display, Ton und Laden funktionieren. Protokoll mit Datum, Gehäuse-Version, Material, Befund. Prinzipien:
1. Last nie über die Platine. Tragend sind Gehäusewände und Stützsäulen, keine starren Rippen auf Modul oder Platine.
2. Weich halten: TPU-Pads oder Schaumstoff, nur leicht andrücken.
3. Modul mit Seitenführung, gedrehte Präzisionskontakte statt einfacher Leisten.
4. Platine auf 4 M3-Abstandsbolzen, bei Bedarf Gummitüllen.
5. Akku (schwerstes Teil): eigene Kammer, seitlich geführt, gepolstert, von oben gesichert. Halter gelötet, aber zusätzlich vom Gehäuse gehalten, Zelle mit Klettband oder lösbarem Kabelbinder.
6. Mechanische Lasten trägt das Gehäuse: USB-C abgestützt, BNC und Klinke mit Mutter verschraubt, Teleskop am Gehäuse verankert.
7. Steckverbinder mit Zugentlastung, keine frei hängenden Kabel.
8. Grosse Bauteile mit Tropfen Kleber sichern. Kleber offen (O14): Niedertemperatur-Heissleim, neutral vernetzendes Silikon (nie essigsäurehaltig) oder Epoxid.
9. Firmware: Watchdog und Brown-out aktivieren, bei Hänger neu starten (F15).

## 5. Lizenzen (L)

| Nr | Punkt | Stand |
|---|---|---|
| L1 | Hardware CERN-OHL-P-2.0, Doku CC-BY-4.0, Firmware folgt dem Fork (ATS Mini: MIT) | festgelegt |
| L2 | Hardware des Original-Empfängers von Sunnygold ist CC BY-NC-SA 3.0. Das Funkfüürli zeichnet ein eigenes Board und kopiert den Schaltplan nicht | geklärt |
| L3 | Quelltext nennt Sunnygold als Autor. Ob NC-lizenzierter Code im MIT-Repo steckt, ist nicht geklärt. Vor kostenpflichtiger Verbreitung beim Maintainer nachfragen (GitHub Discussions) | **offen (O12)** |
| L4 | SSB-Patchdatei `patch_init.h` (Vadim Afonkin, über PU2CLR) hat ungeklärtes Weitergaberecht. SSB bleibt optional, der Nutzer lädt den Patch selbst, nicht vorinstalliert | **offen (O12)**, Workaround gilt |
| L5 | ESP32-SDR und ESP32-A1S-Tayloe haben keine Lizenzdatei | nicht verwenden |

Autor und Copyright: `FerienBSD aka Marcel Sauder`.

## 6. Offene Punkte (O)

| Nr | Punkt | Stand |
|---|---|---|
| O1 | ESP32-S3-DevKitC-1: vorhandene Module durchgehen (Stückzahl, Masse, Reihenabstand, Aufdruck N16R8 oder anderes), Modul wählen | offen |
| O2 | Si4732-Modul: 1 Stück bestellt. Datenblatt prüfen (getrennte FM/AM-Eingänge, Audio L/R, Quarz, Raster) | bestellt, Lieferung offen |
| O3 | RX-Board Rev A: Lieferung abwarten. Rev A hat kein KW, Rev B (mit KW über AMI, Umschalter) nötig. KW-Test erst mit Rev B | in Fertigung |
| O4 | Display 2.0" ST7789V: Pins, Stiftleiste, Anpassung von Auflösung und Layout im Fork | offen |
| O5 | Akku: Kapazität 18650 und 14500 messen, Aufdrucke LiPo-Schutz lesen, 14650 aufnehmen oder streichen, JST und Verpolschutz, Vergleich im Prototyp | offen |
| O6 | LDO-Typ prüfen (LF33CV, mind. 500 mA), ESP32-Einspeisung 3.3 V bestätigen | offen |
| O7 | Verstärker: Pegel, Eingangsimpedanz, Standby. Resonanzraum K 50. Lautsprecher-Box (Ohm, Watt, Masse). Lautstärke per Poti (A) oder Software (B) | offen |
| O8 | Bluetooth-Audio: externes Sendemodul oder klassischer ESP32. BT-Classic-Angabe im Datenblatt bestätigen | offen |
| O9 | Ferritstab und FM/AM-Anschluss: auf dem RX-Board gelöst (FM: Teleskop an FMI, MW/LW: Ferritstab an AMI). Offen nur: KW-Umschalter in Rev B | weitgehend erledigt |
| O10 | Stückliste (BOM) vervollständigen, Blockschaltbild aktualisieren, Verdrahtungsplan für den Breadboard-Test erstellen | offen, vor Breadboard-Test |
| O11 | (frei, nicht belegt) | |
| O12 | Lizenzfragen L3 und L4 beim Maintainer klären | offen |
| O13 | Was bringt der Fork an Watchdog und Neustart mit (F15) | offen |
| O14 | Kleber festlegen (T10) | offen |
| O15 | Falltest: Protokollvorlage und Testplan | offen |
| O16 | Störtest: Quellen einzeln zuschalten, Abschirmung mit und ohne Folie | offen |
| O17 | IP54: lösen oder Ziel abschwächen (G8) | offen |
| O18 | Notfall-Laden (N1) als eigenes Konzept, Notfall-Extras (F14) ja oder nein | offen |
| O20 | Drucker und Bauraum im Club und FabLab, CAD-Werkzeug | offen |
| O21 | Namensprüfung (Swissreg/IGE und GitHub) vor Veröffentlichung | offen |
| O22 | Gemeinsame Hauptplatine für Funkfüürli und Wellenjäger (T8): Vorschlag, noch nicht beschlossen. Prüfen: Pinplan mit I2S und Si5351 für den Wellenjäger, Stecker J1 für das Funkmodul, Störungen im HF-Teil | offen, Entscheid vor KiCad |

## 7. Quellen

* Parlament.ch, Ständerat 9.12.2025 (UKW-Abschaltung aufgehoben)
* cash.ch/AWP und PCtipp (SRG zurück auf UKW ab Mitte November 2026)
* turi2 (UKW-Konzessionen 2027 bis 2031)
* ATS Mini: github.com/esp32-si4732/ats-mini (MIT), Doku esp32-si4732.github.io/ats-mini
* PU2CLR SI4735: pu2clr.github.io/SI4735 (MIT)
* Visaton K 50 (Art. 2901), Datenblatt von Visaton

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
