#!/usr/bin/env bash
work_dir=$(pwd)

function build_example {
    if [ $# -ne 1 ]; then
        usage
        exit 1
    fi

    mkdir -p build_dir
    if [ $1 == 'x86' ]; then
        cmake -G "Unix Makefiles" -S. -Bbuild_dir \
              -DCMAKE_TOOLCHAIN_FILE=linux-x86-gcc.cmake \
              -DCMAKE_INSTALL_PREFIX=out \
              -DSMART_ACCESS_LIB_FOLDER=../lib-linux-x86-gcc_7
    elif [ $1 == 'x86_64' ]; then
        cmake -G "Unix Makefiles" -S. -Bbuild_dir \
              -DCMAKE_TOOLCHAIN_FILE=linux-x86_64-gcc.cmake \
              -DCMAKE_INSTALL_PREFIX=out \
              -DSMART_ACCESS_LIB_FOLDER=../lib-linux-x86_64-gcc_7
    elif [ $1 == 'armv7hf' ]; then
        cmake -G "Unix Makefiles" -S. -Bbuild_dir \
              -DCMAKE_TOOLCHAIN_FILE=linux-armv7hf-gcc.cmake \
              -DCMAKE_INSTALL_PREFIX=out \
              -DSMART_ACCESS_LIB_FOLDER=../lib-linux-armv7hf-gcc_7
    elif [ $1 == 'armv8' ]; then
        cmake -G "Unix Makefiles" -S. -Bbuild_dir \
              -DCMAKE_TOOLCHAIN_FILE=linux-armv8-gcc.cmake \
              -DCMAKE_INSTALL_PREFIX=out \
              -DSMART_ACCESS_LIB_FOLDER=../lib-linux-armv8-gcc_7
    else
        echo "Unknown architecture $1"
        usage
    fi
    make -C build_dir
    make -C build_dir install
}

function usage {
    echo "Usage:"
    echo "  To build example app with gcc 7:"
    echo "    ./build.sh --build <x86_64 | x86 | armv7hf | armv8>"
    echo "  If a different compiler version is used, the DSMART_ACCESS_LIB_FOLDER"
    echo "  in build.sh script must be changed. This is necessary so that the"
    echo "  example app is linked against the smart access libs that were built"
    echo "  with the same compiler version. The compiler and version is specified"
    echo "  in the linux-<architecture>-gcc.cmake files."
    exit 1
}

case $1 in
    --build)
        if [ $# -ne 2 ]; then usage; fi
        build_example $2
        ;;
    *)
        usage
        ;;
esac
