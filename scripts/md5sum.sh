#!/bin/sh
CHECKSUM=$1
RMFILES="*"$1
RELEASE="amadeus-v1.0r2"
#
cd ../bin
rm -f ${RMFILES}
md5sum * > "bin"${CHECKSUM}
cd ../doc
rm -f ${RMFILES}
md5sum * > "doc"${CHECKSUM}
cd ../default
rm -f ${RMFILES}
md5sum * > "default"${CHECKSUM}
cd ../disp
rm -f ${RMFILES}
md5sum * > "disp"${CHECKSUM}
cd ../math
rm -f ${RMFILES}
md5sum * > "math"${CHECKSUM}
cd ../objects
rm -f ${RMFILES}
md5sum * > "objects"${CHECKSUM}
cd ../samples
rm -f ${RMFILES}
md5sum * > "samples"${CHECKSUM}
cd ../scripts
rm -f ${RMFILES}
md5sum * > "scripts"${CHECKSUM}
cd ../src
rm -f ${RMFILES}
md5sum * > "src"${CHECKSUM}
cd ../work
rm -f ${RMFILES}
md5sum * > "work"${CHECKSUM}
cd ../
rm -f ${RMFILES}
md5sum * > ${RELEASE}${CHECKSUM}
