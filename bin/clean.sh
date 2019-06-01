#!/bin/bash
if [ -z $1 ]
then
echo "Error: The argument is missing!"
echo "Infor: It should be a pdf file!"
echo "Infor: The command line should be of the following format: ./clean.sh *.pdf "
exit -1
fi

echo $1|grep --color=auto pdf$ >/dev/null 2>/dev/null
pdffileornot=$?
if ! [ $pdffileornot -eq 0 ]
then
echo "Error: The input file \"$1\" is not a pdf file!"
echo "Infor: Please check it."
exit -2
fi

if ! [ -e $1 ]
then
echo "Error: The pdf file \"$1\" does not exist!"
echo "Infor: Please check it."
exit -3
fi

pdffile=$1
texfile=${pdffile/pdf/tex}
txtfile=${pdffile/pdf/txt}
rootfile=${pdffile/pdf/root}
outfile=${pdffile/pdf/out}
errfile=${pdffile/pdf/err}
timefile=${pdffile/pdf/time}

for file in $pdffile $texfile $txtfile $rootfile $outfile $errfile $timefile
do
if [ -e $file ]
then
echo $file
rm $file
fi
done
exit 0
