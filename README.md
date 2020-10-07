fcc-edm
=======

The FCC Event Data Model.

The Data Model uses [PODIO](https://github.com/aidasoft/podio). On lxplus the PODIO installation is picked up by the `init.sh` script. 

If you are unable to use this central installation you'll have to [compile, install and setup](https://github.com/aidasoft/podio/blob/master/README.md) the environment for PODIO.

Bug tracker
--
Please report any feature requests and issues in the github repository.

Documentation
--
- [Introduction](doc/intro.md)
- [Design of the EDM](doc/design.md)
- [Using FCC-EDM collections](doc/usage.md)
- [Modifying the existing EDM](doc/how_to_modify.md)


Prerequisites
--

If you are on lxplus, all the necessary software is installed on CVMFS.

On Mac OS or Ubuntu, you need to install the following software.

### podio

https://github.com/aidasoft/podio

### Directed Acyclic Graph

https://github.com/HEP-FCC/dag


Setting up
--

Before compiling or using:

1. If on Mac OS, Ubuntu or using a custom installations:
   -  set up the PODIO environment (sourcing the PODIO `init.sh`)
   - set up the dag environment (set the FCCDAG environment variable to the install directory)

2. Set up the FCC-EDM environment:
```
    source ./init.sh
```

Compilation
--
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ..
    make -j 4 install


Test
--
Rudimentary tests that do write and read can be run with

    make test


Running
--
Make sure that the ROOT dictionaries are in the LD_LIBRARY_PATH. This is automatically done when you install, otherwise you may need to update the path accordingly.

The examples are located in the `examples` directory. This command writes an `example.root` file:
```
fccedm-write
```

That file can then be read with
```
fccedm-read
```
