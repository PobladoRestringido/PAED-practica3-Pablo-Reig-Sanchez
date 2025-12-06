#!/bin/bash
( make ; echo "" ; valgrind ./main ; echo "" ; make clean ) | less