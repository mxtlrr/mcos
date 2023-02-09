#!/bin/bash


export PREFIX="/usr/local/i386elfgcc"
export TARGET=x86_64-elf

CORES=$(nproc)

echo "Preparing to install gcc for $TARGET"

mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.35.1.tar.gz
tar xf binutils-2.35.1.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.35.1/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
sudo make all install 2>&1 | tee make.log
cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
tar xf gcc-10.2.0.tar.gz
mkdir gcc-build
cd gcc-build
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c++ --without-headers
sudo make all-gcc -j$CORES
sudo make all-target-libgcc -j$CORES
sudo make install-gcc -j$CORES
sudo make install-target-libgcc -j$CORES


echo "Finished! Put PATH=\"$PREFIX/bin:\$PATH\" in your shell startup"
echo "then restart your shell"