# Funkfüürli: DIY Emergency Radio

[Deutsch](README.md) | [English](README.en.md)

*A little fire in the dark. FM, MW and SW in your pocket when the grid goes down.*

**Status: concept.** No hardware and no firmware yet. The main documentation ([README](README.md) and [docs/konzept.md](docs/konzept.md)) is in German. This page is a short summary.

* **What:** a workshop kit for kids and teens, soldered in 2 to 3 hours. Receives FM, MW and SW.
* **Receiver:** Silicon Labs Si4732 DSP chip. Not an SDR. Long wave is hidden in the firmware.
* **Brain:** a small ESP32 module (Wemos S3 or C3 Mini) plugged into a carrier board.
* **Tuning:** rotary encoder with push button and a small display.
* **Sound:** built in speaker, 3.5 mm jack (headphones or line out), optional Bluetooth speaker.
* **Antennas:** telescopic antenna, ferrite rod for MW, BNC socket for a wire antenna.
* **Power:** protected 18650 or a flat 2000 mAh LiPo, USB-C charging with a linear charger. Solar only as a separate external charger.
* **Case:** 3D printed for any FDM printer in a club or FabLab.
* **Rugged:** acceptance test is a 1 m drop onto wood or tiles. Soft mounting, the case carries the loads.
* **Firmware plan:** fork of [esp32-si4732/ats-mini](https://github.com/esp32-si4732/ats-mini) (MIT).
* **Quiet by design:** solar charge controllers and switching regulators make noise on MW and SW, so charging, power and antenna are kept apart.

Licenses: hardware CERN-OHL-P-2.0, documentation CC-BY-4.0, firmware follows its upstream. See [LICENSE.md](LICENSE.md).

73 de Marcel (MaShaoDe)
