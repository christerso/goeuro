#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Keep the pwd in mind!
# Example: RUN="java -jar $DIR/target/magic.jar"

# Of-course I could also install it but this works also
RUN="$DIR/build/src/goeuro"
NAME="goeuro"

DATA_FILE=$2

PIDFILE=/tmp/$NAME.pid
LOGFILE=/tmp/$NAME.log

start() {
    if [ -f $PIDFILE ]; then
		if `pidof $NAME`; then
           echo 'Service already running' >&2
           return 1
        else
            rm -f $PIDFILE
        fi
    fi
    local CMD="$RUN $DATA_FILE &> \"$LOGFILE\" & echo \$!"
    sh -c "$CMD" > $PIDFILE
}

stop() {
	if pidof $NAME; then
    	kill -15 `pidof $NAME`
		rm -f $PIDFILE
        echo 'Service Stopped' >&2
        return 1
	else
		echo 'Service not running' >&2
		rm -f $PIDFILE
	fi
}


case $1 in
    start)
        start
        ;;
    stop)
        stop
        ;;
    block)
        start
        sleep infinity
        ;;
    *)
        echo "Usage: $0 {start|stop|block} DATA_FILE"
esac
