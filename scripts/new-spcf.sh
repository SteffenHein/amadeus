#!/bin/sh
PORTNAME=amadeus
RELEASE=v1.0r1
DISTNAME=${PORTNAME}-${RELEASE}

# switch into package directory
cd ../../

# Create archive of specially selected sources:
#echo "tar -czf spcf-${RELEASE}.tgz"
tar -czf spcf-${RELEASE}.tgz \
${DISTNAME}/bin \
${DISTNAME}/default \
${DISTNAME}/doc \
${DISTNAME}/math \
${DISTNAME}/objects \
${DISTNAME}/ports \
${DISTNAME}/prv \
${DISTNAME}/samples \
${DISTNAME}/scripts \
${DISTNAME}/src \
${DISTNAME}/tools \
${DISTNAME}/work \
${DISTNAME}/CONFIG.H \
${DISTNAME}/INSTALL \
${DISTNAME}/README \
${DISTNAME}/SETUP \
${DISTNAME}/Makefile \
${DISTNAME}/makefile.gnu \
${DISTNAME}/mk.gnu \
