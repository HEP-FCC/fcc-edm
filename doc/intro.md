Introduction
==

The FCC event data model (EDM) is based on simple C++ classes called POD structs (Plain Old Data structures). A POD struct can be thought of as a basic C struct with native data-type members. PODs can also be composed of other PODs.

Please see the [README.md](https://github.com/HEP-FCC/fcc-edm) for a quick-start guide.

The FCC-EDM is based on [PODIO](https://github.com/HEP-FCC/podio) (Plain Old Data Input/Output), which contains tools to generate, write and read the data model from configuration files.

Repository structure
--
- fcc-edm
  - cmake: Macros for the configuration of the build environment.
  - datamodel: The actual classes that are part of the data-model.
  - examples: Read / write examples.
  - tests: Python specific tests.
  - utilities: Tools associated with the data-model.
  - edm.yaml: The configuration file from which the data-model is generated.
