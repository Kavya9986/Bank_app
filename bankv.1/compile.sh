#!/bin/bash

gcc -o start startup.c bank.h -pthread
gcc -o open open.c bank.h
gcc -o deposit deposit.c bank.h -pthread
gcc -o withdraw withdraw.c bank.h
gcc -o balchk balchk.c bank.h
gcc -o shut shuddown.c bank.h -pthread