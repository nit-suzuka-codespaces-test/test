#/bin/bash
if [ $CODESPACES ]; then
    export DISPLAY="localhost:0"
else
    export DISPLAY="host.docker.internal:0.0"
fi