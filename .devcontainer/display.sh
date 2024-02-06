#/bin/bash
if ! [ $CODESPACES ]; then
    export DISPLAY="host.docker.internal:0.0"
fi