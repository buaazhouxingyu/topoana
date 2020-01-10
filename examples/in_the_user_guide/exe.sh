#!/bin/bash
for((i=1;i<=26;i++))
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
