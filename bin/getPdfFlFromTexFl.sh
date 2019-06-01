#!/bin/bash
if [ -z $1 ]
then
echo "Error: The argument is missing!"
echo "Infor: It should be a .tex source file!"
echo "Infor: The command line should be of the following format: ./getPdfFlFromTexFl.sh *.tex "
exit -1
fi

echo $1|grep --color=auto tex$ >/dev/null 2>/dev/null
cppsrcfileornot=$?
if ! [ $cppsrcfileornot -eq 0 ]
then
echo "Error: The input file \"$1\" is not a .tex source file!"
echo "Infor: Please check it."
exit -2
fi

if ! [ -e $1 ]
then
echo "Error: The tex source file \"$1\" does not exist!"
echo "Infor: Please check it."
exit -3
fi

texfile=$1
pdffile=${texfile/tex/pdf}
auxfile=${texfile/tex/aux}
logfile=${texfile/tex/log}
lotfile=${texfile/tex/lot}
navfile=${texfile/tex/nav}
outfile=${texfile/tex/out}
snmfile=${texfile/tex/snm}
tocfile=${texfile/tex/toc}

if [ -e $pdffile ]
then
rm $pdffile
fi

if [ -e $outfile ]
then
mv $outfile ${outfile/out/OUT}
fi

pdflatex ${texfile}
pdflatex ${texfile}
pdflatex ${texfile}

for file in $auxfile $logfile $lotfile $navfile $outfile $snmfile $tocfile
do
if [ -e $file ]
then
rm $file
fi
done

if [ -e ${outfile/out/OUT} ]
then
mv ${outfile/out/OUT} $outfile
fi

exit 0
