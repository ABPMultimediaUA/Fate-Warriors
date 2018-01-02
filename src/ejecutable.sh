#!/bin/bash
EXE=juego_sin_librerias

export LD_LIBRARY_PATH='${ORIGIN}/${LIB}'
./${EXE}
