#!/bin/bash
set -x
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd $DIR > /dev/null
echo "Docker example: $DIR/docker/example"
bash $1 start $DIR/docker/example
bash simple_test.sh
bash $1 stop
popd> /dev/null
