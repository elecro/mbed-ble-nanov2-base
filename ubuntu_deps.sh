#!/usr/bin/env python2

pip install mbed-cli
wget https://developer.arm.com/-/media/Files/downloads/gnu-rm/6-2017q2/gcc-arm-none-eabi-6-2017-q2-update-linux.tar.bz2 -O /tmp/gcc-arm.tar.bz2
mkdir ~/toolchain/
tar -xf /tmp/gcc-arm.tar.bz2 -C ~/toolchain/

echo ""
echo "Add $HOME/.local/bin/ to the $PATH env permanently (mbed-cli)"
echo "Add $HOME/toolchain/gcc-arm-none-eabi-6-2017-q2-update/ to the $PATH env permanently (toolchain)"
echo "example:"
echo 'export PATH=$HOME/toolchain/gcc-arm-none-eabi-6-2017-q2-update/:$HOME/.local/bin/:$PATH'
