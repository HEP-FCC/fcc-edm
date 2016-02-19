platform='unknown'
sw_afs=0
unamestr=`uname`

export FCCEDM=$PWD/install

if [[ "$unamestr" == 'Linux' ]]; then
    platform='Linux'
    if [[ -d /afs/cern.ch/sw/lcg ]] && [[ `dnsdomainname` = 'cern.ch' ]] ; then
	#should check domain to make sure we're at CERN
	#or is this software available somewhere in Lyon?
	sw_afs=1
	export PATH=/afs/cern.ch/sw/lcg/contrib/CMake/2.8.9/Linux-i386/bin:${PATH}
	source /afs/cern.ch/sw/lcg/contrib/gcc/4.9.3/x86_64-slc6/setup.sh
	source /afs/cern.ch/exp/fcc/sw/0.6/LCG_80/ROOT/6.04.06/x86_64-slc6-gcc49-opt/bin/thisroot.sh
	export PODIO=/afs/cern.ch/exp/fcc/sw/0.6/podio/0.2/x86_64-slc6-gcc49-opt/
	echo software taken from /afs/cern.ch/sw/lcg
    fi
    export LD_LIBRARY_PATH=$FCCEDM/lib:$PODIO/lib:$LD_LIBRARY_PATH
elif [[ "$unamestr" == 'Darwin' ]]; then
    platform='Darwin'
    export DYLD_LIBRARY_PATH=$FCCEDM/lib:$DYLD_LIBRARY_PATH:$PODIO/lib
fi
echo platform detected: $platform

