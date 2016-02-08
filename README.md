fcc-edm
=======

The FCC Event Data Model.

The Data Model uses [PODIO](https://github.com/HEP-FCC/podio). On lxplus the FCC PODIO installation is picked up by the `init.sh` script. If you are unable to use this central installation you'll have to compile, install and setup the environment for PODIO.

Setting up
--
### lxplus
Before compiling or using on lxplus:

    source ./init.sh

### MacOs
Before compiling or using on MacOS make sure PODIO is installed the environment setup, then do:

    source ./init_macos.sh

### Linux
On Linux (tested on Ubuntu) make sure PODIOis installed the environment setup, then do:

    source ./init_linux.sh


Compilation
--
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ..
    make -j 4 install
    cd ..

Test
--
Rudimentary tests that do write and read can be run with

    make test



