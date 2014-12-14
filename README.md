fcc-edm
=======

FCC Event Data Model, version 1.

Prerequisite: before doing anything, compile albers and source its init script to set your environment for albers. 

Before compiling or using on lxplus:

    source init.sh

Before compiling or using on mac os: 

    source init_macos.sh

Compilation:

    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ..
    make -j 4 install
    cd ..

Test:

    ./install/bin/fccedm-write
    ./install/bin/fccedm-read
    

