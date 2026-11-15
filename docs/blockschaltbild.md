# Funkfüürli: Blockschaltbild (Stand 2026-11-15, Entwurf)

Grober Aufbau. Der Empfänger ist in [rx-board.md](rx-board.md) beschrieben. Die Pins stehen in [pinplan.md](pinplan.md), die Gründe in [konzept.md](konzept.md). Die Anschlüsse am Si4732 (welche Antenne an welchen Eingang) sind noch zu klären und hier bewusst offen.

## Gesamt

```mermaid
flowchart LR
  subgraph ANT["Antennen"]
    TEL["Teleskopantenne"]
    BNC["BNC fuer Drahtantenne"]
    FER["Ferritstab MW"]
  end

  subgraph STROM["Strom"]
    USB["USB-C"]
    LAD["Lader TP4056 mit Schutz"]
    AKKU["Akku 1 Zelle 3.0 bis 4.2 V"]
    VP["Schottky-Diode Verpolschutz"]
    SW["Hauptschalter"]
    FIL["Ferrit und Kondensator"]
    LDO["LDO 3.3 V"]
    USB --> LAD --> AKKU --> VP --> SW --> FIL --> LDO
    USB -. "trennt Last beim Laden" .-> SW
  end

  subgraph STEUER["Steuerung"]
    ESP["ESP32-S3-DevKitC-1 aufgesteckt"]
    ENC["Drehencoder mit Taster"]
    TFT["Display 2.0 Zoll ST7789V"]
    ENC --> ESP
    ESP --> TFT
  end

  subgraph AUDIO["Audio"]
    MIX["Mischer und Mono Jumper"]
    AMP["PAM8403 Modul"]
    LS["Lautsprecher K 50"]
    KL["Klinke 3.5 mm mit Schaltkontakt"]
    BT["Bluetooth Sendemodul optional"]
    MIX --> AMP --> LS
    KL -. "Schaltkontakt schaltet LS ab" .-> AMP
  end

  RX["Empfänger RX-Board gesteckt"]

  TEL --> RX
  BNC --> RX
  FER --> RX
  ESP <-- "I2C, Reset" --> RX
  RX -- "Audio L und R" --> MIX
  RX -- "Audio L und R" --> KL
  RX -- "Audio" --> BT

  LDO --> RX
  LDO --> ESP
  SW -- "geschaltet ueber ESP32" --> AMP
  AKKU -. "ADC ueber Teiler" .-> ESP
  LAD -. "Status" .-> ESP
```

## Hinweise

* Ein Schaltregler kommt nicht ins Gerät. Der PAM8403 schaltet selbst und wird im Prototyp gemessen (siehe Anforderungen).
* Der Ferritstab sitzt am Gehäuserand, weit weg von Akku, Lautsprecher, ESP32, Display und Lader.
* Die Verstärker-Versorgung wird über den ESP32 geschaltet (GPIO 5), weil das Modul vermutlich keinen Standby-Pin hat.
* Laden und Hören gehen nicht gleichzeitig. Die USB-Erkennung trennt die Last.

*Copyright FerienBSD aka Marcel Sauder. Doku unter CC-BY-4.0.*
