fcc-edm
=======

FCC Event Data Model, version 1.

Prerequisite: before doing anything, compile albers-core and source its init script to set your environment for the use of this package.

Before compiling or using on lxplus:

    source init.sh

Before compiling or using on mac os: 

    source init_macos.sh

On Linux (tested on Ubuntu), do:

    source init_linux.sh 


Compilation:

    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ..
    make -j 4 install
    cd ..

Test:

    ./install/bin/fccedm-write
    ./install/bin/fccedm-read
    

