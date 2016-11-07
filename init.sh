platform='unknown'
sw_afs=0
unamestr=`uname`

export FCCEDM=$PWD/install

if [[ "$unamestr" == 'Linux' ]]; then
    platform='Linux'
    if [[ -d /afs/cern.ch/sw/lcg ]]; then
    #should check domain to make sure we're at CERN
    #or is this software available somewhere in Lyon?
       source /afs/cern.ch/exp/fcc/sw/0.8pre/setup.sh
    else
        if [ -z "$PODIO" ]; then
            echo "[ERROR] no podio setup detected, make sure it is setup"
            exit 1
        fi
        export LD_LIBRARY_PATH=$FCCEDM/lib:$PODIO/lib:$LD_LIBRARY_PATH
    fi
elif [[ "$unamestr" == 'Darwin' ]]; then
    platform='Darwin'
    export DYLD_LIBRARY_PATH=$FCCEDM/lib:$DYLD_LIBRARY_PATH:$PODIO/lib
fi
echo platform detected: $platform
