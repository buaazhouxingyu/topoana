#!/bin/bash
root -l -b -q MCGenTopo.C > MCGenTopo.log
topoana.exe topoana.card
grep ^[0-9] MCGenTopo.log | sort -n -r -k 2 > nDcyTrOld_iDcyTrOld.dat
grep "rowNo" topoana.txt | awk '{print $4"\t"$6}' > nDcyTrNew_iDcyTrNew.dat
paste nDcyTrOld_iDcyTrOld.dat nDcyTrNew_iDcyTrNew.dat | awk '{print $2"\t"$1"\t-->\t  "$3"\t"$4}' > nDcyTrOld_iDcyTrOld_iDcyTrNew_nDcyTrNew.dat
rm nDcyTrOld_iDcyTrOld.dat nDcyTrNew_iDcyTrNew.dat -f
exit 0
