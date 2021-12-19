#!/bin/sh
CHECKSUM=$1
RMFILES=${CHECKSUM}" *.md5"
#
cd ../models
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../bin
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../doc
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../elfe
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../elsy
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../eval
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../expm
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../math
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../objects
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../prv
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../scripts
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../tools
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
cd ../
rm -f ${RMFILES}
md5sum * > ${CHECKSUM}
