# Empty ARM Mbed project for RedBear BLE Nano v2

This project serves as a base for the [RedBear BLE Nano v2](https://github.com/redbear/nRF5x/tree/master/nRF52832)
device development using [ARM mbed OS 5.4](https://github.com/ARMmbed/mbed-os) platform.

## Building and Flashing the Project

### Tooling requirements:
- Install Python 2 and `pip`. (The steps for installing Python are platform dependent.
  Installation steps for `pip` are described in its [documentation](https://pip.pypa.io/en/stable/).
  But both may already by available on your system.)
- Install the mbed CLI by `pip install mbed-cli`.
- Download and install the
  [GNU Embedded Toolchain for ARM](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads).

For Ubuntu quick tool install see (ubuntu_deps.sh)

### Building project

```
$ git clone https://github.com/elecro/mbed-ble-nanov2-base.git
$ cd mbed-ble-nanov2-base
$ mbed deploy
$ mbed compile
```

After compile there should be a `./BUILD/RBLAB_BLENANO2/GCC_ARM/mbed-ble-nanov2.hex` file
which can be copied to the target device via DAPLink.
