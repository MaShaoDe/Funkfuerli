<!-- SPDX-License-Identifier: CC-BY-4.0 -->
<!-- Copyright 2026 FerienBSD aka Marcel Sauder -->

# Funkfüürli: Festlegungen

Stand: 25.11.2026 | Festlegungen | Version: v1.0-1

Was Marcel beschlossen hat. **Nicht neu fragen.** Änderung nur auf seine ausdrückliche Anweisung. Alles, was hier fehlt, ist offen oder Vorschlag und steht mit Nummer in der [Projektdefinition](projektdefinition.md) (O1 ff.). Details und Gründe stehen dort und im [Cookbook Prototyp](cookbook-prototyp.md).

## Festgelegt

| Bereich | Festlegung | Seit |
|---|---|---|
| Rahmen | Nur das Funkfüürli selbst (Hardware und Software). Nichts zu Kursen, Workshops oder anderen Projekten in den Dokumenten | 2026-11 |
| Plattform | ESP32-S3-DevKitC-1 N16R8 auf Buchsenleisten, Display 2.0" ST7789V 240x320 | 2026-11-15 |
| Software | Fork von esp32-si4732/ats-mini (MIT), Abstimmung per Drehencoder mit Fein- und Grobschritt | 2026-11-15 |
| Empfänger | Eigenes RX-Board (Si4732), komplett bestückt, Rev A ohne KW, KW ab Rev B. Das Repo RX-Board-Si4732 ist die Wahrheit, hier steht nur Rolle und Verdrahtung | 2026-11-15 |
| Verstärker | PAM8403 Modul HW-012, Mono mit Mischer 22 kΩ und Jumper, Kopfhörer und Line-Out stereo | 2026-11-15 |
| Kopfhörer | Eigener Verstärker TPA6132A2 (der Chip kann keine Kopfhörer treiben) | 2026-11 |
| Spannungsregler | LDO AP2112K-3.3, Schottky-Diode als Verpolschutz in der Lastleitung | 2026-11 |
| Ferritstab | SL8X50MW70T (8 x 50 mm) oder Stab aus dem Sortiment mit 180 bis 450 µH | 2026-11 |
| Akku im Prototyp | LiPo 103665 mit Schutzplatine | 2026-11-25 |
| Strom | 1 Zelle, linearer Lader (TP4056-Typ mit Schutz), kein Schaltlader im Gerät, Laden und Hören nicht gleichzeitig | 2026-11-15 |
| Laden | DC-Hohlsteckerbuchse 5.5 mm Aussendurchmesser, nur 5 V und 1 A, beschriftet, mit Überspannungsschutz, Filter und Glättung. Kein USB-C zum Laden | 2026-11 |
| Antennen | Teleskop an BNC-Buchse am Gehäuse (UKW und KW), dünnes 50-Ohm-Koax zum RX-Board, ab Rev B U.FL steckbar, Drahtantenne an Polklemme (Querbohrung und Bananenbuchse), Ferritstab für MW | 2026-11 |
| Reparierbarkeit | Alle Teile einzeln ersetzbar, steckbar (Flachband, Kabelstecker, Stiftleisten), Montage mit Schrauben, Kleben nur für Wasserdichtheit (H6, C4) | 2026-11 |
| Bluetooth | Entfällt. WLAN nur zum Firmware-Update, sonst aus | 2026-11 |
| Sendersuche | UKW: Suchlauf mit Senderliste. MW und KW: nur Sender mit Pegel und Signalqualität, freier Suchlauf als Option (F16 bis F18) | 2026-11-25 |
| Robust | Falltest aus 1 m als Abnahme, Watchdog in der Firmware, Akku in eigener Kammer | 2026-11-15 |
| Prototyp | Stufe 1 Breadboard mit RX-Board Rev A, Stufe 2 Lochraster, Stufe 3 eigene Platine erst nach dem letzten erfolgreichen Gesamttest. KiCad-Entwurf der Hauptplatine erst, wenn alle Bauteile identifiziert sind und der Breadboard-Test bestanden ist | 2026-11-15 |
| Dokumente | Deutsch zuerst, Copyright FerienBSD aka Marcel Sauder, Lizenzen: Hardware CERN-OHL-P-2.0, Doku CC-BY-4.0, Firmware folgt dem Fork. Kein Rufzeichen auf dem Siebdruck | 2026-11-15 |

## Vorschlag, noch nicht entschieden

| Bereich | Vorschlag | Offener Punkt |
|---|---|---|
| Flashen | Erstes Flashen per USB vor dem Einstecken des ESP32, danach OTA per Menüeintrag Update, kein USB am Gehäuse | O22 (Partitionsgrössen des Fork prüfen) |
| Lautsprecher | Typ und Anzahl offen, Kandidat Visaton K 50. Muster liegen vor | O7 |
| Akku im Gerät | Endgültig offen: LiPo 103665, NCR18650B im Halter oder 14500 | O5 |

## Offen

Display-Pinbelegung des Moduls (O4), Teleskopantenne (Typ und Länge), Innendurchmesser der DC-Buchse, Zellenstecker, Rückspeiseschutz bei USB und DC-Eingang gleichzeitig (O22), Gehäusehöhe (T9), alle weiteren O-Punkte in der Projektdefinition.
