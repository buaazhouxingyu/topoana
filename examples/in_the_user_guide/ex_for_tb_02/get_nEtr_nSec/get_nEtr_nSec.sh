#!/bin/bash
cd ../
topoana.exe ex_for_tb_02.card | grep "Number of entries processed" -A 21 | grep 000 > get_nEtr_nSec/nEtr_nSec.dat
exit 0
