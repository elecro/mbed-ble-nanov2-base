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
- The `mbed` and `arm-none-eabi-g++` should be available in bash.
  For this please set the `$PATH` environment variable.

#### Short & Quick virtual env setup steps

Most of these steps are in the `ubuntu_deps.sh` file.

```
$ cd <navigate to a suitable directory>
$ virtualenv -p python2.7 mbedenv
$ source ./mbedenv/bin/activate

(mbedenv) $ pip install mbed-cli
(mbedenv) $ wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2017q2/gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2 -O /tmp/gcc-arm.tar.bz2
(mbedenv) $ mkdir ~/toolchain/
(mdedenv) $ tar -xf /tmp/gcc-arm.tar.bz2 -C ~/toolchain/
(mbedenv) $ export PATH=$HOME/toolchain/gcc-arm-none-eabi-6-2017-q2-update/bin:$HOME/.local/bin/:$PATH
```

If there is already an existing virtual environment with the `mbed-cli` installed there is no need to create a new one.
However make sure that the `PATH` environment variable contains the path to the toolchain.

### Building project

After the environment is configured the project can be cloned and built with the following steps:

```
$ git clone https://github.com/elecro/mbed-ble-nanov2-base.git
$ cd mbed-ble-nanov2-base
$ mbed deploy
$ mbed compile
```

After compile there should be a `./BUILD/RBLAB_BLENANO2/GCC_ARM/mbed-ble-nanov2.hex` file
which can be copied to the target device via DAPLink (on ubuntu: `/media/$USER/DAPLINK.
For example:
```
$ cp ./BUILD/RBLAB_BLENANO2/GCC_ARM/mbed-ble-nanov2-base.hex /media/student/DAPLINK/
```

**Notes**:
  - Make sure that the virtual environment is not inside the mbed project directory as the
    `mbed compile` command will try to compile all source files in the project but the virtual env sources are not needed.
  - The `mbed deploy` and `mbed compile` commands should be executed inside the virtual environment in which the
    `mbed-cli` was installed.
  - `mbed deploy` is not required before all `mbed compile`. It is only required if the mbed library dependencies are
    changed.
