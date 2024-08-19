#!/bin/sh

set -xe
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/

clang `pkg-config --cflags raylib` -c src/particle.c -o build/particle.o `pkg-config --libs raylib`
clang `pkg-config --cflags raylib` -c src/kdtree.c -o build/kdtree.o `pkg-config --libs raylib`
clang `pkg-config --cflags raylib` -c src/main.c -o build/main.o `pkg-config --libs raylib`
clang build/main.o build/particle.o build/kdtree.o -o build/particle_simulation -lraylib -lm

./build/particle_simulation
