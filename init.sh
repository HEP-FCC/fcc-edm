platform='unknown'
unamestr=`uname`

if [ -z "$FCCEDM" ]; then
    export FCCEDM=$PWD/install
    echo "FCCEDM is unset, setting to $FCCEDM"
fi


if [[ "$unamestr" == 'Linux' ]]; then
    platform='Linux'
    if [[ -d /cvmfs/fcc.cern.ch/sw ]] ; then
        #should check domain to make sure we're at CERN
        #or is this software available somewhere in Lyon?
        source /cvmfs/fcc.cern.ch/sw/0.8.1/init_fcc_stack.sh
    else
        if [ ! -z "$PODIO" ]; then
            export LD_LIBRARY_PATH=$FCCEDM/lib:$PODIO/lib:$LD_LIBRARY_PATH
        fi
    fi
elif [[ "$unamestr" == 'Darwin' ]]; then
    platform='Darwin'
    if [ ! -z "$PODIO" ]; then
        export DYLD_LIBRARY_PATH=$FCCEDM/lib:$DYLD_LIBRARY_PATH:$PODIO/lib
    fi
fi
if [ -z "$PODIO" ]; then
    echo "[ERROR] no podio setup detected, make sure it is setup"
    return 1
fi
if [ -z "$FCCDAG" ]; then
    echo "[ERROR] no dag setup detected, make sure it is setup by setting the FCCDAG environment variable or adding it to your cmake prefix path"
    return 1
fi

echo platform detected: $platform
