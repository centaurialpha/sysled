# sysled
Turn on/off `PWR` led and `ath9k_htc-phy0` led of my RPi.

## Build and install
```
$ make
$ make install  # Install on ~/.local/bin
```

## Usage
```
-------------------------
Turn on/off LED1 and WiFi adapter LEDs
Options are:
    --help: print this help
    -a: turn on/off LED1 and WiFi adapter leds
    -w: turn on/off WiFi adapter led
    -l: turn on/off LED1 led

$ sudo sysled -w off  # Turn off wifi adapter led
$ sudo sysled -l off # Turn off PWR led
$ sudo sysled -a off  # Turn off all leds
$ sudo sysled -a on # Turn on all leds
```

## Uninstall
```
$ make uninstall
```
