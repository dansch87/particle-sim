#!/bin/sh
set -xe
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/
clang `pkg-config --cflags raylib` -o main main.c `pkg-config --libs raylib`
