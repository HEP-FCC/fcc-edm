fcc-edm
=======

FCC Event Data Model, version 1.

Prerequisite: before doing anything, compile albers-core and source its init script to set your environment for the use of this package.

Before compiling or using 

    source ./init.sh

Compilation:

    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ..
    make -j 4 install
    cd ..

Test:

    ./install/bin/fccedm-write
    ./install/bin/fccedm-read
    

