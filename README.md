fcc-edm
=======

The FCC Event Data Model.

The Data Model uses [PODIO](https://github.com/HEP-FCC/podio). On lxplus the PODIO installation is picked up by the `init.sh` script. 

If you are unable to use this central installation you'll have to [compile, install and setup](https://github.com/hegner/podio/blob/master/README.md) the environment for PODIO.

Bug tracker
--
Please report any feature requests and issues at this [JIRA](https://sft.its.cern.ch/jira/projects/FCC/issues/) for the component DataModel.

Documentation
--
- [Introduction](doc/intro.md)
- [Design of the EDM](doc/design.md)
- [Using FCC-EDM collections](doc/usage.md)
- [Modifying the existing EDM](doc/how_to_modify.md)

Browse the API documentation created with Doxygen at [http://fccsw.web.cern.ch/fccsw/fcc-edm/index.html](http://fccsw.web.cern.ch/fccsw/fcc-edm/index.html).

Prerequisites
--

If you are on lxplus, all the necessary software is preinstalled.

On Mac OS or Ubuntu, you need to install the following software.

### podio

https://github.com/HEP-FCC/podio


Setting up
--

Before compiling or using:

1. If on Mac OS, Ubuntu or using a custom PODIO installation, set up the PODIO environment.

2. Set up the FCC-EDM environment:
```
    source ./init.sh
```

Compilation
--
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=$FCCEDM ..
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
$FCCEDM/bin/fcc-edm-write
```

That file can then be read with
```
$FCCEDM/bin/fcc-edm-read
```
