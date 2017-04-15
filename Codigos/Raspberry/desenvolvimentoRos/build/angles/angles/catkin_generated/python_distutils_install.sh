#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/pi/Documents/desenvolvimentoRos/src/angles/angles"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/pi/Documents/desenvolvimentoRos/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/pi/Documents/desenvolvimentoRos/install/lib/python2.7/dist-packages:/home/pi/Documents/desenvolvimentoRos/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/pi/Documents/desenvolvimentoRos/build" \
    "/usr/bin/python" \
    "/home/pi/Documents/desenvolvimentoRos/src/angles/angles/setup.py" \
    build --build-base "/home/pi/Documents/desenvolvimentoRos/build/angles/angles" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/pi/Documents/desenvolvimentoRos/install" --install-scripts="/home/pi/Documents/desenvolvimentoRos/install/bin"