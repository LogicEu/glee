#!/bin/bash

cc=gcc
src=src/*.c
name=libglee

flags=(
    -std=c99
    -Wall
    -Wextra
    -O2
)

inc=(
    -I.
    -Iinclude/
)

lib=(
    -lglfw
)

linux=(
    -lGL
    -lGLEW
)

mac=(
    -framework OpenGL
    # -mmacos-version-min=10.9
)

fail_op() {
    echo "Run with -d to build dynamically, or -s to build statically." && exit
}

fail_os() {
    echo "OS is not supported yet..." && exit
}

mac_dlib() {
    $cc ${flags[*]} ${inc[*]} ${lib[*]} ${mac[*]} -dynamiclib $src -o $name.dylib &&\
    install_name_tool -id @executable_path/$name.dylib $name.dylib 
}

linux_dlib() {
    $cc -shared ${flags[*]} ${inc[*]} ${lib[*]} ${linux[*]} -fPIC $src -o $name.so 
}

dlib() {
    if echo "$OSTYPE" | grep -q "darwin"; then
        mac_dlib
    elif echo "$OSTYPE" | grep -q "linux"; then
        linux_dlib
    else
        fails_os
    fi
}

slib() {
    $cc ${flags[*]} ${inc[*]} -c $src && ar -crv $name.a *.o && rm *.o
}

case "$1" in
    "-d")
        dlib;;
    "-s")
        slib;;
    *)
        fail_op;;
esac
