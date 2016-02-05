export PATH=/afs/cern.ch/sw/lcg/contrib/CMake/2.8.9/Linux-i386/bin:${PATH}
source /afs/cern.ch/sw/lcg/contrib/gcc/4.9.3/x86_64-slc6/setup.sh
source /afs/cern.ch/exp/fcc/sw/0.6/LCG_80/ROOT/6.04.06/x86_64-slc6-gcc49-opt/bin/thisroot.sh

export PODIO=/afs/cern.ch/exp/fcc/sw/0.6/podio/0.1/x86_64-slc6-gcc49-opt/
export FCCEDM=$PWD/install
export LD_LIBRARY_PATH=$FCCEDM/lib:$LD_LIBRARY_PATH
export PATH=$FCCEDM/bin:$PATH

