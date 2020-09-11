#!/bin/bash

cd ex_for_tb_01
   pwd
   ls
   ../../../bin/topoana.exe jpsi_ta.card 
cd ../

for((i=2;i<=17;i++))
do
num=`printf "%02d" $i`
if [ -d ex_for_tb_$num ]
then
cd ex_for_tb_$num
  pwd
  ls
  ../../../bin/topoana.exe ex_for_tb_$num.card
cd ../ 
fi
done

exit 0
