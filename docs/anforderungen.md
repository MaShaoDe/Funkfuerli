# Funkfüürli: Anforderungen (Stand 2026-11-15, Entwurf)

Was das Funkfüürli können muss. Die Technik dazu steht in [konzept.md](konzept.md). Wo die Anforderungen vom Konzept abweichen, steht es unter "Klärungsbedarf".

## 1. Gerät

| Nr | Anforderung | Bemerkung |
|---|---|---|
| G1 | Wenig Stromverbrauch | Display abschaltbar, WLAN und Bluetooth aus beim Hören, Auto-Aus |
| G2 | Gute Empfangsqualität | UKW, MW, KW. Antennenanschlüsse (Teleskop, Ferritstab, BNC) |
| G3 | Störarm | Kein Schaltregler. Messen statt behaupten (Konzept Abschnitt 8) |
| G4 | Einfache Handhabung | Beschriftung mit Symbolen, ev. gelasert. Grosse Anzeige |
| G5 | Lautstärkebegrenzung | Vor allem für Kopfhörer |
| G6 | Hauptschalter und Tiefentladeschutz | Neu, im Konzept noch nicht enthalten |
| G7 | Robust: Falltest aus 1 m | Abnahmekriterium, Protokoll (Konzept Abschnitt 11) |
| G8 | Spritzwasser und Staub: Ziel IP54 | Nicht wasserdicht. Offen, siehe Klärungsbedarf |
| G9 | Akku aufladbar, mit Halterung gesichert | Variante 14650 offen, siehe Klärungsbedarf |

## 2. Hardware und Platine

| Nr | Anforderung | Bemerkung |
|---|---|---|
| H1 | Eigene Platine in KiCad 9, Gerber im Repo | DRC vor jeder Bestellung. Copyright und Repo-Link auf dem Siebdruck |
| H2 | Möglichst alles durchsteckmontiert (THT) | Von den Teilnehmern gelötet. Kein SMD zum Löten |
| H3 | Empfängerchip steckbar oder THT | Der Si4732 ist meines Wissens nur SMD. Lösung: fertiges Modul auf Stiftleisten |
| H4 | ESP32 sicher aufgesteckt | Weiche Sicherung (Schaumstoff oder TPU-Pad vom Deckel), kein starrer Druck |
| H5 | Empfindliche Teile gesteckt, der Rest verlötet | ESP32 und Empfängermodul gesteckt, alles andere gelötet |
| H6 | Kein Schaltnetzteil | Linearer Lader, LDO. Siehe Klärungsbedarf zum PAM8403 |
| H7 | Reparierbar | Gesteckte Module lassen sich tauschen |

## 3. Gehäuse

| Nr | Anforderung | Bemerkung |
|---|---|---|
| C1 | 3D-Druck | Gehäuse vor dem Kurs gedruckt |
| C2 | 1 bis 2 Gehäuse im Kurs drucken | Teil des Erlebnisses, Druckzeit höchstens 2 bis 3 Stunden |
| C3 | Beschriftung mit Symbolen, ev. gelasert | Kein Rufzeichen, keine privaten Angaben |
| C4 | Schutz gegen Spritzwasser | Dichtungen an Öffnungen, siehe G8 |

## 4. Kurs

| Nr | Anforderung | Bemerkung |
|---|---|---|
| K1 | 5 bis 8 Personen pro Kurs | Entscheidung 2026-11-15 |
| K2 | Kostenziel 30 bis 60 CHF pro Bausatz | Annahme: inklusive Gehäuse, ohne Kursgebühr. Nach der Stückliste prüfen |
| K3 | Bauanleitung bebildert, im Stil von "Sendung mit der Maus" | Deutsch, Schritt für Schritt, Selbsttest nach jedem Block |
| K4 | Sicherheit | Lötkolben, bleifreies Lot, Schutzbrille, Aufsicht, Li-Ion nur mit Schutz und Verpolschutz, Altersgrenze festlegen |
| K5 | Fertiges Prüfstück für den Kursleiter | Zum Vergleichen und für die Fehlersuche |
| K6 | Lernmodule | RFI-Jagd, Abschirmung, Falltest |

## 5. Betrieb im Notfall

| Nr | Anforderung | Bemerkung |
|---|---|---|
| N1 | Laden ohne Netz | Powerbank, externes Solar, Reservezelle. Soll in einem eigenen Konzept stehen |
| N2 | Lange Laufzeit | Messen, nicht schätzen |

## 6. Beschaffung und Recht

| Nr | Anforderung | Bemerkung |
|---|---|---|
| B1 | Lieferkette prüfen | Ersatz für Si4732-Modul und ESP32-Modul, Mindestmengen, Lieferzeiten, Clones |
| B2 | Konformität bei Verkauf | Bluetooth und WLAN senden. Vor einem Verkauf CE und EMV klären. Reiner Empfang ist unkritisch |

## Klärungsbedarf

1. **Akku 14650:** Neu gegenüber dem Konzept (dort LiPo 103665, 18650 und 14500). Meines Wissens 14 x 65 mm und etwa 1000 bis 1600 mAh, ungeprüft. Als vierte Variante aufnehmen oder eine der bisherigen streichen.
2. **Si4732:** Der Chip ist SMD. Entweder fertiges Modul (Mikroe Click) oder ein eigenes, vorbestücktes Mini-Modul (SMD ab Fertigung, nicht von den Kindern gelötet). Eigenes Repo für das Modul ist noch offen.
3. **PAM8403:** Class-D-Verstärker, schaltet selbst bei einigen 100 kHz. H6 gilt für Regler und Lader, der Verstärker bleibt mit Messung. Ausweichlösung LM386.
4. **IP54:** Offene Ausschnitte (USB-C, BNC, Klinke, Lautsprecher, Teleskopantenne) machen IP54 schwierig. Mit Dichtungen und Abdeckungen lösen oder das Ziel zu "spritzwassergeschützt" abschwächen.
5. **Störarm statt "alles entstört":** Ein ESP32, ein Display und ein Verstärker im gleichen Gehäuse stören immer etwas. Ziel ist, dass MW und KW im Test brauchbar bleiben.
6. **Kostenziel 30 bis 60 CHF:** Mit der Stückliste prüfen. Platine, Gehäuse, ESP32-Modul, Display, Empfängermodul, Akku und Verstärker liegen zusammen schnell im oberen Bereich.
7. **Notfall-Laden (N1):** Eigenes Konzept, noch nicht begonnen.
8. **Alterszielgruppe:** Mindestalter für das Löten festlegen.

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
