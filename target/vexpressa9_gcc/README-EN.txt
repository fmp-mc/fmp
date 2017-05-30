
                        README
           FMP porting for the QEMU Vexpress-A9 target

                2013 (C) Daniel Sangorrin
                daniel.sangorrin@gmail.com

--------
Overview
--------

TOPPERS/FMP (http://www.toppers.jp/en/fmp-kernel.html) is an RTOS with
support for multi-core processors. It is developed by the TOPPERS
project (http://www.toppers.jp/en/index.html) and distributed as open
source code through the TOPPERS license
(http://www.toppers.jp/en/license.html).

FMP follows the "TOPPERS New Generation Kernels" specification
(http://www.toppers.jp/documents.html). Contact me for an English
translation of the specification. A good way to understand FMP's API is
by looking at the sample program in the "fmp/sample" folder,
or the header files in "fmp/kernel/". (Hint: it is based on the uITRON4.0
interface).

The main characteristics of FMP are:

  - It supports SMP and AMP configurations (however, in the case of AMP
    all cores should be able to execute the same instruction set).

  - Kernel and applications are linked in a single binary without
    memory protection.

  - Tasks are assigned to processor cores during the design phase. This is
    done through a configuration file (.cfg) as shown in the sample program.

  - The kernel will not automatically migrate tasks (i.e., load balancing)
    during the execution of the system.

  - However, the API allows migrating a task to a different processor core
    at run time.

  - The execution of FMP can be traced and displayed graphically through
    the TLV tracelog visualizer (http://www.toppers.jp/tlv.html)

  - Several target boards supported (ARM Cortex-A9, NIOS2, SH2A, SH4A)

This guide provides a quickstart for running FMP on the QEMU Vexpress-A9
target (a model of the ARM Versatile Express A9 board that includes
4 ARM Cortex-A9 cores).

THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.

----------------
Host environment
----------------

You need a UNIX-based execution environment for building FMP. In particular,
we tested it on the following operating system:

    Ubuntu 12.04 (LTS) 32 bits

If you have a different environment, we recommend to first create a virtual
machine with the same operating system and run these instructions there.

Applications and libraries that must be installed:

  - C++ Boost libraries (>1.46)
    $ sudo apt-get install libboost libboost-regex-dev libboost-system-dev \
      libboost-filesystem-dev libboost-program-options-dev

  - ARM cross-compiler: arm-none-eabi-gcc version (download "Sourcery
    CodeBench Lite 2012.03-56 at "http://www.mentor.com/embedded-software/
    sourcery-tools/sourcery-codebench/editions/lite-edition/"

  - Essential software for building applications (make, etc.)
    $ sudo apt-get install build-essential

------------------
Build instructions
------------------

Download and uncompress the FMP vertex-a9 package:

$ wget http://www.toppers.jp/download.cgi/fmp_vexpressa9_gcc-20130401.tar.gz
$ tar zxvf fmp_vexpressa9_gcc-20130328.tar.gz

The folder "fmp/target/vexpressa9_gcc" contains the Versatile Express A9
dependent code (BSP):

$ ls fmp/target/
vexpressa9_gcc

In order to build an application we first have to build the configuration
tool for FMP. This tool depends on the C++ Boost libraries so you will have
to install them too (see instructions in the "Host environment" section).

$ cd fmp/cfg/
$ ./configure
$ make depend
$ make
$ cd ../../

The above instructions will generate the configurator binary 'cfg' (Note: when
using Cygwin the binary is named 'cfg.exe').

Now we will create an application in the folder "obj/obj_sample" by using
the application template at "fmp/sample":

$ mkdir -p fmp/obj/obj_sample
$ cd fmp/obj/obj_sample
$ perl ../../configure -T vexpressa9_gcc -f

Next, we will build the "obj/obj_sample/" application.

$ make realclean
$ make TARGET=vexpressa9_gcc ENABLE_QEMU=true ENABLE_G_SYSLOG=false PRC_NUM=4 KERNEL_FUNCOBJS= fmp.bin
$ cd ../../../

The option ENABLE_QEMU is necessary for running the binary on QEMU (it
just customizes FMP's idle loop). If you want to run it on a real board set
it to false. The option PRC_NUM indicates the number of cores for FMP to run
on. It can be set to 1, 2, 3 or 4. The resulting ELF binary (fmp) contains
the kernel and the application linked together.

-----------------
Load instructions
-----------------

Download and compile QEMU (version >=1.4.0):

$ wget http://wiki.qemu-project.org/download/qemu-1.4.0.tar.bz2
$ tar jxvf qemu-1.4.0.tar.bz2
$ cd qemu-1.4.0/
$ ./configure --target-list="arm-softmmu" --disable-strip --disable-xen --disable-kvm --disable-user --disable-docs --enable-debug --enable-debug-tcg
$ make
$ cd ../

The file "arm-softmmu/qemu-system-arm" contains the QEMU binary with
support for the Vexpress-A9 board. Set your environment PATH to include it
(e.g., export PATH=/home/dsl/qemu-1.4.0/arm-softmmu/:$PATH).

$ qemu-system-arm --version
QEMU emulator version 1.4.0, Copyright (c) 2003-2008 Fabrice Bellard

$ qemu-system-arm -M ? | grep vexpress-a9
vexpress-a9          ARM Versatile Express for Cortex-A9

Finally, run the FMP binary on QEMU:

$ qemu-system-arm -cpu cortex-a9 -M vexpress-a9 -smp 4 -serial vc:80Cx40C -serial vc:80Cx40C -serial vc:80Cx40C -serial vc:80Cx40C -no-reboot -m 1024M -kernel fmp/obj/obj_sample/fmp

Then, use "Ctrl+Alt+{4,5,6,7}" for switching between each virtual console in
order to see the output of FMP tasks on each core.

If you compiled the application with a different number of processors
(e.g., PRC_NUM=2), change QEMU's -smp as well (e.g., -smp 2).

------------------------
Pass the TTSP test suite
------------------------

TTSP is a test suite developed for easying the verification of
TOPPERS kernels (http://www.toppers.jp/en/ttsp.html). Download
TTSP and uncompress it inside the FMP directory:

$ cd fmp/
$ wget https://www.toppers.jp/download.cgi/ttsp_1.1.2.tar.gz
$ tar zxvf ttsp_1.1.2.tar.gz

The TTSP package should come with support for the Vexpress-A9 target:

$ ls ttsp/library/FMP/target/ | grep vexpressa9_gcc
vexpressa9_gcc

Modify configure.sh with the following parameters:

$ gedit configure.sh
TARGET_NAME="vexpressa9_gcc"
PROFILE_NAME="FMP"

The main modifications to the TTSP that were carried for the VexpressA9 are
contained in the following files:

    - fmp/ttsp/library/FMP/arch
    - fmp/ttsp/library/FMP/target/vexpressa9_gcc/

Make sure that in fmp/target/vexpressa9_gcc/Makefile.target, by default
(i.e., NOSAFEG) the Cortex-A9 private timers are used (instead of the
watchdog timers):

    - SYSTIMER_TYPE = CA9_PRIVATE_TIMER
    - KERNEL_COBJS := $(KERNEL_COBJS) chip_timer.o

You need to install ruby in order to run the TTSP tools.
The steps for running the API tests are:

$ cd ttsp/
$ ./ttb.sh
        a) Select 1 (API tests)
        b) Select 1 (Auto-code tests)
        c) Select 1 (Generate a MANIFEST file for all TESRYs)
        d) Select 4 (Build all program files. WARNING: takes time)
        e) Select e (Run the tests on QEMU. WARNING: takes even more time)

A few notes about TTSP:

    - The step d) may take a few minutes, depending on the host machine. That
      step generates a binary named 'fmp' inside the 'fmp/ttsp/obj/' folder.

    - The step e) may take a long time. On some hosts, tests could fail
      after a timeout due to the use of a simulator instead of a real board.

    - When the program is run it will display which tests are passed.

    - You can do the tests in parts by selecting the options "Generate a
      MANIFEST file divided by specified number" or "MANIFEST file for each
      functions".

    - You can also do tests for the SIL or the common functions for timer,
      interrupts and exceptions.

    - You can modify the number of processors and other variables at 'fmp/
      ttsp/library/FMP/target/vexpressa9_gcc/configure.yaml'
