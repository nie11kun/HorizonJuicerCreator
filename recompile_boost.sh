#!/bin/bash

# Configuration based on HorizonJuicerCreator.pro
BOOST_ROOT="/Users/marconie/libs/boost_1_84_0"
BOOST_LIBS="--with-filesystem --with-regex"

# Qt6 typically requires C++17
CXX_FLAGS="-std=c++17 -stdlib=libc++"
LINK_FLAGS="-stdlib=libc++"

echo "==========================================="
echo "Boost Compilation Script for macOS (Qt6)"
echo "Target: $BOOST_ROOT"
echo "Libs:   $BOOST_LIBS"
echo "==========================================="

# Check if Boost directory exists
if [ ! -d "$BOOST_ROOT" ]; then
    echo "Error: Boost directory not found at $BOOST_ROOT"
    echo "Please check the path or download Boost 1.84.0."
    exit 1
fi

cd "$BOOST_ROOT" || exit 1

# Check for b2, bootstrap if needed
if [ ! -f "b2" ]; then
    echo "Building Boost Build engine (b2)..."
    ./bootstrap.sh
    if [ $? -ne 0 ]; then
        echo "Error: Bootstrap failed."
        exit 1
    fi
else
    echo "Found existing b2, skipping bootstrap."
fi

# Clean previous builds usually good practice, but optional. Un-comment if needed.
# ./b2 --clean

echo "Compiling Boost libraries..."
# Command explanation:
# toolset=clang       : Use native macOS compiler
# cxxflags/linkflags  : Ensure libc++ and C++17 for Qt6 compatibility
# link=static         : Static libraries (.a) as requested by context (Windows script used static)
# runtime-link=shared : Link against shared C/C++ runtime (standard)
# threading=multi     : Thread-safe
# stage               : Put libs in 'stage/lib'
./b2 toolset=clang \
    cxxflags="$CXX_FLAGS" \
    linkflags="$LINK_FLAGS" \
    variant=release \
    link=static \
    threading=multi \
    runtime-link=shared \
    address-model=64 \
    $BOOST_LIBS \
    stage

if [ $? -eq 0 ]; then
    echo "==========================================="
    echo "Build Complete!"
    echo "Libraries should be in: $BOOST_ROOT/stage/lib"
else
    echo "==========================================="
    echo "Build Failed."
    exit 1
fi
