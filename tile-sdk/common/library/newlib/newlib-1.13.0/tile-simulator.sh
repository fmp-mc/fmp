#!/bin/sh

if [ $# != 1 ]; then
    echo "Usage: $0 exe" 1>&2
    exit 1
fi

exe=$1
shift

if [ -n "$TEST_IMAGE" ]; then
  exec @TILE_MONITOR_EXE@ --image 1x1 --upload "$exe" /tmp/test -- /tmp/test
else
  exec @TSIM_EXE@ --config 1x1 --magic-os "$exe"
fi
