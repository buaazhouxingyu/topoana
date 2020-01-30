#!/bin/bash
cd ../
topoana.exe jpsi_ta.card | grep "Number of entries processed" -A 21 | grep 000 > get_nEtr_nSec/nEtr_nSec.dat
exit 0
