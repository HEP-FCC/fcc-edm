Design of the FCC-EDM
==

This document describes the reasoning behind the layout described in the [edm.yaml](https://github.com/HEP-FCC/fcc-edm/blob/master/edm.yaml). If you are interested in the principles behind the data structures and choices of implementation, have a look at the [PODIO Design document](https://github.com/HEP-FCC/podio/blob/master/doc/design.md).

The driving factors for the way chosen to describe the event content are:
1. Keep the event-size small
2. Allow writing generic analysis / reconstruction code that does not need to be templated

Generator level description
--

The description of a generated event was influenced by existing event descriptions, such as [HepMC](http://hepmc.web.cern.ch/hepmc/). Typically the generated particles and their relations are stored as the "Particles" themselves and "Vertices".

HepMC chooses to describe the relations by saving with each vertex all indices of particles that are associated to it (either as a production or as a decay vertex). Similarly, particles know which vertices they are associated with.

In the FCC-EDM we made the choice to only save the particle-to-vertex relation persistently. The vertex-to-particle relation on the other hand is dropped and needs to be re-created at run-time. For this we provide tools that [create and traverse a directed acyclic graph](https://github.com/HEP-FCC/fcc-edm/tree/master/utilities/ParticleGraph.h).

The `MCParticle` is composed of information about start and end vertex, as well as a `BareParticle`. The `BareParticle` is a POD and holds the kinematic information and properties of the particle. This composition was chosen to ease the development of code that runs both on reconstructed and generated particles (by writing algorithms that use a `BareParticle`). Also see the [usage document](./usage.md).

Simulated and reconstructed event description
--

The physics output of simulation are hits, describing the position and deposited energy of a particle traversal through a sensitive detector component. We have dedicated classes for Tracker and Calorimeter hits:
- [fcc::CaloHit](https://github.com/HEP-FCC/fcc-edm/blob/master/datamodel/datamodel/CaloHit.h)
- [fcc::TrackHit](https://github.com/HEP-FCC/fcc-edm/blob/master/datamodel/datamodel/TrackHit.h)

One implementation is used for both simulated and real detector hits. Additional information may be saved in `Sim*Hit` class with a `OneToOneRelation` to the `*Hit` and additional information as members.

Reconstruction is then performed with these hits as input. Following clusterisation, track fits are performed on track clusters, vertices are found based on the tracks and particles are identified based on calorimeter clusters and track parameters. Finally particles are added to particle jets.

The hierarchy of these physics objects is persistently saved through `OneToManyRelations`. E.g. a cluster knows which hits it contains, similarly a jet knows which particles are associated with it.

After this reconstruction further algorithms may be run to further classify physics objects (e.g. b-tagging algorithms on jets). `OneToOneRelations` are used to associate the results of such algorithms with the physics object.
