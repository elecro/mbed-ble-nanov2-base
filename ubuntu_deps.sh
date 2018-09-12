#!/usr/bin/env python2

pip install mbed-cli
wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2017q2/gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2 -O /tmp/gcc-arm.tar.bz2
mkdir ~/toolchain/
tar -xvf /tmp/gcc-arm.tar.bz2 -C ~/toolchain/

echo "Add $HOME/toolchain/gcc-arm-none-eabi-6-2017-q2-update/ to the $PATH env permanently"
echo "export PATH=$HOME/toolchain/gcc-arm-none-eabi-6-2017-q2-update/:$$PATH"
