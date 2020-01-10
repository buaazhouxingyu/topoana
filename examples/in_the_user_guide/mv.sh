#!/bin/bash
for((iold=5;iold<=24;iold++))
do
inew=$(($iold+2))
numold=`printf "%02d" $iold`
numnew=`printf "%02d" $inew`
if [ -d ex_for_tb_$numold ]
then
mv ex_for_tb_$numold/ex_for_tb_$numold.card ex_for_tb_$numold/ex_for_tb_$numnew.card
mv ex_for_tb_$numold ex_for_tb_$numnew
fi
done
exit 0
