#!/bin/bash
grep "Number of entries processed" -A 21 ../ddbar.out | grep 000 > nEtr_nSec.dat
exit 0
