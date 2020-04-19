#!/bin/bash
topoana.exe jpsi_ta.card -i ../../in_the_paper/input/jpsi1.root -o jpsi1_ta -n 25000
topoana.exe jpsi_ta.card -i ../../in_the_paper/input/jpsi2.root -o jpsi2_ta -n 25000
topoana.exe jpsi_ta.card -i ../../in_the_paper/input/jpsi1.root ../../in_the_paper/input/jpsi2.root -o jpsi3_ta -n 75000
topoana.exe jpsi_ta.card -i ../../in_the_paper/input/jpsi[1-2].root -o jpsi4_ta -n 75000
topoana.exe jpsi_ta.card -i ../../in_the_paper/input/jpsi?.root -o jpsi5_ta -n 75000
topoana.exe jpsi_ta.card -i ../../in_the_paper/input/jpsi*.root -o jpsi6_ta -n 75000
exit 0
