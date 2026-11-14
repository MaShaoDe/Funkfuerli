# Funkfüürli: Pinplan (Stand 2026-11-15, Entwurf)

Pinplan für das ESP32-S3-DevKitC-1 (N16R8). Er ist auf die strengste Variante ausgelegt und noch nicht gegen das Datenblatt und den Schaltplan des vorhandenen Moduls geprüft (siehe "Vor dem Layout prüfen"). Das Blockschaltbild steht in [blockschaltbild.md](blockschaltbild.md).

## Zuteilung

| GPIO | Funktion | Signal | Bemerkung |
|---|---|---|---|
| 8 | I2C | SDA zum Si4732 | Standard-Pin von Wire beim S3 |
| 9 | I2C | SCL zum Si4732 | Pull-ups prüfen (Modul oder Platine) |
| 7 | Si4732 | RESET | |
| 10 | Display SPI | CS | FSPI-Pins, schnell |
| 11 | Display SPI | MOSI (SDA am Display) | |
| 12 | Display SPI | SCLK (SCL am Display) | |
| 13 | Display | DC | MISO wird nicht gebraucht |
| 14 | Display | RST | |
| 21 | Display | Backlight ein/aus | Über Transistor schalten, kein PWM (Konzept Abschnitt 8) |
| 1 | Encoder | A | Entprell-RC auf der Platine |
| 2 | Encoder | B | Entprell-RC auf der Platine |
| 42 | Encoder | Taster | Gegen Masse, Pull-up |
| 5 | Audio | Verstärker-Versorgung ein/aus | Schaltung offen (High-Side, Bauteil klären) |
| 6 | Audio | Klinken-Schaltkontakt | Eingang mit Pull-up |
| 40 | Bluetooth | Taster | Nur wenn das Sendemodul bestückt wird |
| 41 | Bluetooth | Enable Sendemodul | |
| 4 | Akku | Spannung (ADC) über Teiler | ADC1, nicht ADC2 (ADC2 stört bei WLAN) |
| 16 | Lader | Status CHRG | TP4056, Open-Collector |
| 17 | Lader | USB erkannt (VBUS über Teiler) | Trennt die Last beim Laden |

Das sind 19 Pins. Die Schätzung im Konzept lag bei etwa 17, weil Display (6) und Lader (3) genauer gezählt sind.

## Reserve (frei nutzbar)

15, 18, 38, 39, 47, 48.

* GPIO 48 (Modul v1.0) und GPIO 38 (Modul v1.1) hängen an der RGB-LED des DevKits. Nur nutzen, wenn die LED stört, nicht.
* Mögliche Verwendung: zweiter Ladestatus (STDBY), Notfall-Extras, Statusled.

## Gesperrt oder zu meiden

| GPIO | Grund |
|---|---|
| 0, 3, 45, 46 | Strapping-Pins (Bootmodus). Nur mit Vorsicht, hier nicht verwendet |
| 19, 20 | USB (Anschluss "USB" des DevKits) |
| 43, 44 | UART0 (USB-UART-Brücke, Flashen und Log) |
| 35, 36, 37 | Octal-PSRAM beim N16R8 |
| 26 bis 34 | Flash und PSRAM, am DevKit nicht herausgeführt |

## Vor dem Layout prüfen

1. Pinbelegung der Stiftleisten am vorhandenen Modul gegen den Schaltplan des Herstellers. Clones unterscheiden sich.
2. Pins des ATS-Mini-Forks im Quelltext (`esp32-si4732/ats-mini`) mit diesem Plan vergleichen. Wo der Fork andere Pins nutzt, entweder Plan anpassen oder im Fork die Pindefinitionen ändern. Der Fork zielt auf ein Display mit 320x170, hier kommt ein 2.0"-TFT mit 240x320 und ST7789V.
3. Pins des 2.0"-TFT am vorhandenen Modul (Beschriftung, Stiftleiste, Backlight-Strom).
4. Si4732-Modul: I2C-Adresse (SEN-Pin), Pull-ups, Pegel und Anschlüsse laut Datenblatt.
5. Schaltung für die Verstärker-Versorgung (GPIO 5): THT-Bauteil, das mit 3.3 V sicher schaltet.
6. USB-Erkennung (GPIO 17): Spannungsteiler so wählen, dass 5 V nie auf den Pin gelangen.

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
