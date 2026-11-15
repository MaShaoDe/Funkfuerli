# Funkfüürli: Prototyp in 3 Stufen (Stand 2026-11-15, Entwurf)

Der Prototyp entsteht in 3 Stufen. Jede Stufe beantwortet andere Fragen und kostet mehr Aufwand als die vorige. Die Stückliste für Stufe 2 und 3 steht in [stueckliste.md](stueckliste.md), die Pins in [pinplan.md](pinplan.md).

| Stufe | Aufbau | Frage | Aussagekraft für Empfang und Störungen |
|---|---|---|---|
| 1 | Breadboard mit Kabeln (Labortest) | Funktioniert alles zusammen? | Gering |
| 2 | Lochraster, 1 Stück | Wie gut empfängt es, was stört? | Mittel |
| 3 | Eigene Platine (KiCad) | Stimmt das Design? | Hoch |

Entscheid 2026-11-15: Breadboard für den Labortest, danach Lochraster, die Platine erst nach bestandenem Test.

## Stufe 1: Breadboard (Labortest)

Zweck: Funktion, Firmware und Pinplan prüfen, bevor etwas gelötet wird. Alle Module sind vorhanden, ausser dem Si4732-Modul (noch zu bestellen). Kabel und Breadboards sind da.

Reihenfolge, jeweils erst weiter, wenn der Schritt läuft:

1. **ESP32-S3 allein:** Flashen, Serieller Monitor. Versorgung über USB.
2. **Display:** ST7789V mit den Pins aus dem Pinplan. Auflösung 240x320 und Backlight (ein/aus über Transistor).
3. **Encoder:** Drehen und Klick, Entprellung (RC oder Software).
4. **Si4732-Modul:** I2C-Scan, Reset, Firmware (Fork von ats-mini oder PU2CLR-Beispiel). Eine UKW-Station abstimmen.
5. **Audio:** Klinke (Kopfhörer), dann PAM8403 mit Lautsprecher K 50. Mono-Mischer und Jumper testen.
6. **Lautstärke und Menü:** Abstimmen mit Fein- und Grobschritt, Speicherplätze.
7. **Strom:** Stromaufnahme messen (Multimeter oder USB-Messgerät), mit und ohne Display, mit und ohne Verstärker. Danach Akku, LDO, Schottky-Diode und Hauptschalter dazu. Erst jetzt Akku anschliessen.
8. **Ergebnis festhalten:** Pinplan korrigieren, wo er vom Fork oder vom Modul abweicht (Pinplan Abschnitt "Vor dem Layout prüfen").

Grenzen des Breadboards:
* Lange Kabel und die Kontaktfedern machen I2C, SPI und Audio störanfällig. Fehler dort sind kein Beweis gegen das Konzept.
* Empfang auf MW und KW und der Störtest sind auf dem Breadboard kaum aussagekräftig (keine Massefläche, Kabel wirken als Antenne).
* Kein Falltest.
* Für den Akku gilt: Nur geschützte Zelle, nie ohne Schutz an ein Breadboard. Zuerst Strom über USB, Akku später.

Weiter zu Stufe 2, wenn: Display, Encoder, Empfang (UKW), Ton über Lautsprecher und Klinke laufen und der Pinplan bestätigt ist (Vorschlag).

## Stufe 2: Lochraster

Aufbau mit kurzen Leitungen, wenn möglich auf doppelseitigem Raster mit Massefläche, Ferritstab am Rand. Hier gelten die Tests aus der Stückliste (Abschnitt "Prototyp: Tests vor der Platine"): Empfang, Störtest, Laufzeit, Bedienung, Falltest mit Testgehäuse.

Auch hier ist ein schlechter Wert kein Beweis gegen das Konzept, ein guter Wert ein gutes Zeichen.

Weiter zu Stufe 3, wenn die Tests bestanden sind und die offenen Punkte (Akku, LDO, Verstärker, Einspeisung des ESP32) entschieden sind (Vorschlag).

## Stufe 3: Eigene Platine

KiCad 9, Gerber im Repo, erst nach Stufe 2. Siehe [konzept.md](konzept.md) Abschnitt 9 und den Plan in der [README](../README.md).

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
