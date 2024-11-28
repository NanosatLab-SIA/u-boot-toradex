.. SPDX-License-Identifier: GPL-2.0-or-later

Toradex SMARC iMX8M Plus Module
===============================

- SoM: https://www.toradex.com/computer-on-modules/smarc-arm-family/nxp-imx-8m-plus
- Carrier board: https://www.toradex.com/products/carrier-board/smarc-development-board-kit

Quick Start
-----------

- Build the ARM trusted firmware binary
- Get the DDR firmware
- Build U-Boot
- Flash to eMMC
- Boot

Get and Build the ARM Trusted Firmware (Trusted Firmware A)
-----------------------------------------------------------

.. code-block:: bash

    $ echo "Downloading and building TF-A..."
    $ git clone https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git
    $ cd trusted-firmware-a

Then build ATF (TF-A):

.. code-block:: bash

    $ export CROSS_COMPILE=aarch64-linux-gnu-
    $ make PLAT=imx8mp IMX_BOOT_UART_BASE=0x30a60000 bl31
    $ cp build/imx8mp/release/bl31.bin ../

Get the DDR Firmware
--------------------

.. code-block:: bash

    $ cd ..
    $ wget https://www.nxp.com/lgfiles/NMG/MAD/YOCTO/firmware-imx-8.10.1.bin
    $ chmod +x firmware-imx-8.10.1.bin
    $ ./firmware-imx-8.10.1.bin
    $ cp firmware-imx-8.10.1/firmware/ddr/synopsys/lpddr4*_202006.bin ./

Build U-Boot
------------

.. code-block:: bash

    $ export CROSS_COMPILE=aarch64-linux-gnu-
    $ make toradex-smarc-imx8mp_defconfig
    $ make

Flash to eMMC
-------------

.. code-block:: bash

    > tftpboot ${loadaddr} flash.bin
    > setexpr blkcnt ${filesize} + 0x1ff && setexpr blkcnt ${blkcnt} / 0x200
    > mmc dev 2 1 && mmc write ${loadaddr} 0x0 ${blkcnt}

As a convenience, instead of the last two commands, one may also use the update
U-Boot wrapper:

.. code-block:: bash

    > run update_uboot

Boot
----

ATF, U-Boot proper and u-boot.dtb images are packed into a FIT image,
which is loaded and parsed by SPL.

Boot sequence is:

* SPL ---> ATF (TF-A) ---> U-Boot proper
