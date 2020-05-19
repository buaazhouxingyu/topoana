#!/bin/bash
dirs=`ls | grep -v do_all_jobs.sh`
for dir in $dirs
do
  echo $dir
  cd $dir
  time (topoana.exe $dir.card >$dir.Out 2>$dir.err) 2>$dir.time
  mv $dir.Out $dir.out
  cd get_nEtr_nSec
     ./get_nEtr_nSec.sh
  cd ../
  cd ../
done
exit 0
