#!/bin/sh

make TWE_CHIP_MODEL=JN5148 clean all $*
make TWE_CHIP_MODEL=JN5164 clean all $*
make TWE_CHIP_MODEL=JN5164 TWE_DEVKIT=002L clean all $*
