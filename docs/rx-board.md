# RX-Board: Empfänger-Baugruppe (Stand 2026-11-15, Entwurf)

Das RX-Board ist die Empfänger-Baugruppe des Funkfüürli. Es steckt auf der Hauptplatine und enthält den Empfängerchip Si4732 mit seiner Beschaltung. Die Kinder löten nur die Stiftleisten, das Board kommt bestückt aus der Fertigung.

Einordnung im Gerät: [blockschaltbild.md](blockschaltbild.md). Pins der Hauptplatine: [pinplan.md](pinplan.md).

## 1. Aufgabe

Das RX-Board nimmt das Antennensignal auf, wählt einen Sender (Abstimmung), demoduliert ihn (UKW, MW, KW) und gibt das Tonsignal links und rechts aus. Der Si4732 macht Tuner, Demodulator und Stereodecoder in einem Chip. Er ist kein SDR und liefert keine Rohdaten (siehe [konzept.md](konzept.md)).

```
Antenne  ->  RX-Board  ->  Ton (L, R)  ->  Verstärker / Klinke
                ^
        Steuerung (ESP32) über I2C
```

## 2. Entscheid

* Eigenes Board statt fertigem Mikroe AM/FM 2 Click (2026-11-15). Der Click kostet mit Versand und Zoll etwa 30 bis 40 CHF und passt nicht zu unserem Pinplan.
* Kinder löten kein SMD. Das RX-Board wird komplett bestückt bestellt (PCBA bei JLCPCB), die Kinder löten nur Stiftleisten.
* Der Chip, der Quarz und die Kondensatoren müssen deshalb in der Fertigungsbibliothek des Herstellers lieferbar sein. Das wird beim Entwurf je Bauteil geprüft.
* Vorlage für die Beschaltung: offene Schaltpläne der PU2CLR-Bibliothek (MIT) und das Datenblatt des Si4732-A10. Nichts von Sunnygold (CC BY-NC-SA) und nichts von den Umbaumodulen für UV-K5/K6.

## 3. Schnittstelle zur Hauptplatine

Die Belegung der Stiftleiste wird nach der Prüfung des vollständigen Datenblatts festgelegt (Abschnitt 7). Geplant sind diese Signale:

| Signal | Richtung | Bemerkung |
|---|---|---|
| 3.3 V | Eingang | Versorgung, Chip arbeitet laut Datenblatt mit 2.7 bis 3.6 V. Aus dem LDO, nie direkt vom Akku |
| GND | | Masse, mehrere Pins |
| SDA, SCL | Ein/Aus | I2C zur Steuerung (Pinplan: GPIO 8 und 9) |
| RST | Eingang | Reset (Pinplan: GPIO 7) |
| Audio L, Audio R | Ausgang | Analoges Tonsignal, weiter an Verstärker und Klinke |
| Antenne FM/SW | Eingang | Teleskopantenne oder BNC |
| Antenne AM/LW | Eingang | Ferritstab |
| Interrupt (optional) | Ausgang | Nur wenn die Firmware ihn braucht |

Welche Antenne an welchen Eingang gehört: Laut Blockschaltbild des Datenblatts gibt es einen Eingang "AM / LW ANT" und einen Eingang "FM / SW ANT". Das Teleskop kommt an FM/SW, der Ferritstab an AM/LW.

## 4. Anforderungen

Qualität und Haltbarkeit haben Vorrang vor Grösse. Wenn eine enge Bestückung nicht sicher ist, wird grosszügiger gebaut.

**Grundlagen** (aus [anforderungen.md](anforderungen.md)): wenig Strom, gute Empfangsqualität, einfache Handhabung, robust, günstig.

**Mechanik und Robustheit**
* Passive Bauteile in Grösse 0805, keine kleineren. Grosszügige Abstände zwischen den Teilen, mehr als das Minimum des Herstellers. Der Chip im SOIC-16-Gehäuse bleibt, das ist gross genug.
* Stiftleisten im Raster 2.54 mm, steckbar und tauschbar.
* 2 Befestigungslöcher. Das Board wird im Gehäuse gehalten, die Stiftleiste trägt nur die Elektrik (Konzept Abschnitt 11, Falltest aus 1 m).
* Kleiner als der Mikroe-Click (57.15 x 25.4 mm), genaue Masse nach dem Layout.

**Schutz vor Fehlern**
* Pin 1 deutlich markiert, die Stiftleiste so gelegt, dass das Board nur in einer Richtung passt (Kodierung).
* Der Chip arbeitet laut Datenblatt mit 2.7 bis 3.6 V. Die Versorgung kommt nur aus dem LDO, nie direkt vom Akku oder aus 5 V. Absolute Maximalwerte im Datenblatt nachsehen.
* Schutz der Antenneneingänge gegen statische Aufladung (SMD, auf dem Board).

**Platine und Lack**
* 1.6 mm FR4, 2 Lagen, Oberfläche ENIG (flach, korrosionsfest, gut für feine Lötpads).
* Lötstopplack matt, dunkel. Weisser Siebdruck darauf. Zusätzlicher Schutzlack ist optional und kommt erst nach dem Test, weil er Antenneneingänge und Quarz leicht verstimmen kann. Stiftleisten und Pads bleiben frei.

**Beschriftung** (alles auf dem Board beschriftet)
* Bauteilnamen (R1, C1, U1, X1) und Pin-Namen an den Stiftleisten.
* Antennenanschlüsse (FM/SW, AM/LW), "RX", Version (Rev A) und Jahr, Feld für die Seriennummer.
* Beschriftete Testpunkte für 3.3 V, GND, SDA, SCL, Audio links und rechts, Reset.
* `Copyright 2026 FerienBSD aka Marcel Sauder`, Link `github.com/MaShaoDe/Funkfuerli` und `CERN-OHL-P-2.0`.
* Rufzeichen auf dem Board: Entscheidung offen (siehe Abschnitt 7).
* Mindestgrösse von Schrift und Linien beim Hersteller vor der Bestellung prüfen.

**Elektrik und Störungen**
* Kein Schaltregler auf dem Board, Versorgung nur über Kondensatoren (Entkopplung).
* Kurze Leitungen zu den Antenneneingängen, durchgehende Massefläche, Quarz nahe am Chip, Abstand zu ESP32, Display und Verstärker.

**Qualitätssicherung**
* Jedes Board wird vor dem Kurs geprüft: Ein kleines Testprogramm liest den Chip aus und stimmt einen Sender ab.
* Mehr Boards bestellen, als der Kurs braucht (Mindestmenge meist 5), als Reserve.
* Zwei Revisionen einplanen: Rev A zum Testen, Rev B mit den Korrekturen für den Kurs.
* DRC in KiCad und die Herstellerprüfung der Bestückungsdaten (Drehung der Bauteile) vor der Bestellung.

## 5. Bestückung

* Chip: Si4732-A10-GS im 16-poligen SOIC-Gehäuse.
* Quarz: 32.768 kHz (Wert aus der PU2CLR-Vorlage, im Datenblatt zu bestätigen).
* Entkopplung und Lastkondensatoren: Werte aus Datenblatt und Vorlage, nicht aus der Erinnerung.
* Alles SMD, bestückt vom Hersteller. Von Hand gelötet werden nur die Stiftleisten.
* Mindestmenge: Platinen meist 5 Stück, bei der Bestückung vor der Bestellung im Angebot prüfen.

## 6. Test

* Vergleich: Empfang UKW, MW, KW mit Teleskop und Drahtantenne.
* Stromaufnahme im Betrieb messen.
* Störtest nach Konzept Abschnitt 8.
* Zuerst auf dem Breadboard mit Kabeln (Stufe 1 in [prototyp.md](prototyp.md)).

## 7. Offene Punkte

1. Vollständiges Datenblatt des Si4732-A10 lesen: Pinout, Applikationsschaltung, Layout-Hinweise, I2C-Adresse. Die Pinbelegung aus der PU2CLR-Vorlage und ein Kurz-Datenblatt widersprechen sich, bis zur Prüfung wird nichts ins Layout übernommen.
2. Schaltplan des Mikroe-Clicks zum Gegenlesen (Download bei Mikroe).
3. Antennenanschluss des Ferritstabs: Anzapfung und Induktivität nach Datenblatt.
4. Schutz der Antenneneingänge gegen statische Aufladung (SMD, auf dem Board).
5. Verfügbarkeit von Chip, Quarz und Kondensatoren beim Hersteller, Angebot einholen.
6. Lizenzdatei der PU2CLR-Bibliothek einsehen, Autor in der Doku nennen.
7. Ordner im Repo: `hardware/rx-board/`. Eigenes Repo später, wenn nötig.
8. Rufzeichen auf dem Board: ja oder nein. Das Konzept sagt bisher "kein Rufzeichen und keine privaten Angaben im Gehäuse". Ohne ausdrückliche Freigabe steht keines in den Dateien.

## 8. Erklärt für Laien

**Das Ohr des Radios.**

Stell dir den Himmel voller Radiowellen vor, wie ein Meer voller Wellen. Alle Sender funken gleichzeitig, durcheinander. Die Antenne ist wie ein Netz: Sie fängt alles auf einmal. Aber ein Netz voller Wellen gibt noch keinen Ton.

Dafür gibt es das RX-Board. Es ist der Sortierer. Du drehst am Knopf, und das RX-Board pickt genau den einen Sender heraus, den du willst. Alle anderen lässt es draussen. Dann übersetzt es die Welle in Töne, die der Lautsprecher abspielen kann.

Im Herzen des Boards sitzt ein kleiner Chip, kleiner als ein Fingernagel. Er rechnet sehr schnell und macht dabei alles, was früher ein ganzer Schrank voller Bauteile gebraucht hat. Weil er so winzig ist, bestücken wir ihn nicht von Hand. Das macht eine Maschine. Du lötest nur die Stifte an, mit denen das Board in das Radio gesteckt wird.

Das RX-Board ist also: das Ohr, das alles hört, und der Kopf, der den richtigen Sender findet.

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
