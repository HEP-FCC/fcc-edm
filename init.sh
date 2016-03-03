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
        source /afs/cern.ch/sw/lcg/views/LCG_83/x86_64-slc6-gcc49-opt/setup.sh
        if [ -z "$PODIO" ]; then
            export PODIO=/afs/cern.ch/exp/fcc/sw/0.7/podio/0.3/x86_64-slc6-gcc49-opt/
        fi
        echo software taken from /afs/cern.ch/sw/lcg
    fi
    export LD_LIBRARY_PATH=$FCCEDM/lib:$PODIO/lib:$LD_LIBRARY_PATH
elif [[ "$unamestr" == 'Darwin' ]]; then
    platform='Darwin'
    export DYLD_LIBRARY_PATH=$FCCEDM/lib:$DYLD_LIBRARY_PATH:$PODIO/lib
fi
echo platform detected: $platform

