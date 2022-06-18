#!/bin/sh
PORTNAME=amadeus
RELEASE=v1.0r2
DISTNAME=${PORTNAME}-${RELEASE}

# switch into package directory
cd ../../

# Create archive of specially selected sources:
#echo "tar -czf spcf-${RELEASE}.tgz"
tar -czf spcf-${RELEASE}.tgz \
${DISTNAME}/bin \
${DISTNAME}/default \
${DISTNAME}/disp \
${DISTNAME}/doc \
${DISTNAME}/math \
${DISTNAME}/objects \
${DISTNAME}/samples \
${DISTNAME}/scripts \
${DISTNAME}/src \
${DISTNAME}/work \
${DISTNAME}/CONFIG.H \
${DISTNAME}/INSTALL \
${DISTNAME}/README \
${DISTNAME}/SETUP \
${DISTNAME}/Makefile \
${DISTNAME}/makefile.unx \
${DISTNAME}/mk.unx \
