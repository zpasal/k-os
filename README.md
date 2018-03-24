# STM32-p103 playground OS

## Install

* Install http://beckus.github.io/qemu_stm32/ qemu with stm32 support
  * `git clone https://github.com/beckus/qemu_stm32.git`
  * `cd qemu_stm32`
  * `git submodule update --init dtc`

```
./configure --disable-werror --enable-debug \
    --target-list="arm-softmmu" \
    --extra-cflags=-DSTM32_UART_NO_BAUD_DELAY \
    --extra-cflags=-DSTM32_UART_ENABLE_OVERRUN \
    --disable-gtk
make
make install
```

* Install arm-none-eabi toolchain for mac ([GNU Arm Embedded Toolchain | Downloads – Arm Developer](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads))


## Quick start
* `make`
* `make run`

## Make targets

* `make` to build main.elf
* `make run` to run qemu
