#!/bin/bash

VENDOR_DIR="./vendor"
LIB_DIR="./src"
GITREPO_MICROCAP="https://github.com/1248/microcoap" 
GITREPO_MPACK="https://github.com/ludocode/mpack"

if [[ ! -d "${VENDOR_DIR}" ]]; then
	mkdir "${VENDOR_DIR}"
fi

if [[ ! -d "${LIB_DIR}" ]]; then
	mkdir -p "${LIB_DIR}"
fi

if [[ ! -d "${VENDOR_DIR}/microcoap" ]]; then
	git clone "${GITREPO_MICROCAP}" "${VENDOR_DIR}/microcoap"
	# check out revision
	(cd "${VENDOR_DIR}/microcoap" && git checkout ef272895925f0d4c563725fe0102966f544a0fdc )
fi

if [[ ! -d "${VENDOR_DIR}/mpack" ]]; then
	git clone "${GITREPO_MPACK}" "${VENDOR_DIR}/mpack"
	# check out tag
	( cd "${VENDOR_DIR}/mpack" && git fetch --tags && git checkout "v0.8.2" )
fi

if [[ ! -f "${LIB_DIR}/microcoap" ]]; then
	mkdir -p "${LIB_DIR}/microcoap"
	cp "${VENDOR_DIR}/microcoap/coap.h" "${VENDOR_DIR}/microcoap/coap.c" "${LIB_DIR}/microcoap/"
fi

if [[ ! -f "${LIB_DIR}/mpack" ]]; then
	mkdir -p "${LIB_DIR}/mpack"
	cp -r "${VENDOR_DIR}/mpack/src/mpack" "${LIB_DIR}/"
	cp -r "${VENDOR_DIR}/mpack/src/mpack-config.h.sample" "${LIB_DIR}/mpack/"
fi
