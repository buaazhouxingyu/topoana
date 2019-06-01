#!/bin/bash
if [ -z $1 ]
then

cardfile=topoana.card

if ! [ -e  $cardfile ]
then
echo "Error: The card file \"$cardfile\" does not exist!"
echo "Infor: Infor: The card file name is the default one."
echo "Infor: Do you forget to append the name of your own card file to the end of the executable?"
echo "Infor: If yes, please specify it along with the executable by the command line \"pathOfTheExecutable/topoana.exe nameOfyourOwnCardFile\""
exit -1
fi

else

echo $1|grep --color=auto card$ >/dev/null 2>/dev/null
cardfileornot=$?
if ! [ $cardfileornot -eq 0 ]
then
echo "Error: The input file \"$1\" is not a card file!"
echo "Infor: Please check it."
exit -2
fi

cardfile=$1

if ! [ -e  $cardfile ]
then
echo "Error: The card file \"$cardfile\" does not exist!"
echo "Infor: Please check it."
exit -3
fi

fi

OUTfile=${cardfile/card/OUT}
errfile=${cardfile/card/err}
timefile=${cardfile/card/time}
outfile=${cardfile/card/out}

time (/home/belle2/zhouxy/studyarea/c++/tools/topoana/v1.3.8/bin/topoana.exe $cardfile >$OUTfile 2>$errfile) 2>$timefile
mv $OUTfile $outfile
exit 0
