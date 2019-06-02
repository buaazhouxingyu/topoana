#!/bin/bash

function PrintError()
{
  echo -e "\e[91mERROR: ${1}\e[0m"
}

function topoanaClean()
{
  if [[ ${#} != 1 ]]; then
    PrintError "Argument is missing!"
    echo "Input should be a pdf file. The command line should be of the following format:"
    echo "    ./clean.sh *.pdf"
    return -1
  fi

  local pdfFile="${1}"
  echo "${pdfFile}" | grep --color=auto pdf$ >/dev/null 2>/dev/null
  if [[ $pdffileornot != 0 ]]; then
    PrintError "The input file \"${pdfFile}\" is not a pdf file! Please check it."
    return -2
  fi

  if [[ ! -f "${pdfFile}" ]]; then
    PrintError "The pdf file \"${pdfFile}\" does not exist! Please check it."
    return -3
  fi

  local texFile="${pdfFile/pdf/tex}"
  local txtFile="${pdfFile/pdf/txt}"
  local rootFile="${pdfFile/pdf/root}"
  local outFile="${pdfFile/pdf/out}"
  local errFile="${pdfFile/pdf/err}"
  local timeFile="${pdfFile/pdf/time}"

  for file in $pdfFile $texFile $txtFile $rootFile $outFile $errFile $timeFile; do
    if [ -e $file ]; then
      echo $file
      rm $file
    fi
  done
}
export topoanaClean

function topoanaGetPdf()
{
  if [ -z $1 ]; then
    echo "Error: The argument is missing!"
    echo "Infor: It should be a .tex source file!"
    echo "Infor: The command line should be of the following format: ./getPdfFlFromTexFl.sh *.tex "
    return -1
  fi

  echo $1|grep --color=auto tex$ >/dev/null 2>/dev/null
  cppsrcfileornot=$?
  if ! [ $cppsrcfileornot -eq 0 ]; then
    echo "Error: The input file \"$1\" is not a .tex source file!"
    echo "Infor: Please check it."
    return -2
  fi

  if ! [ -e $1 ]; then
    echo "Error: The tex source file \"$1\" does not exist!"
    echo "Infor: Please check it."
    return -3
  fi

  local texfile=$1
  local pdffile=${texfile/tex/pdf}
  local auxfile=${texfile/tex/aux}
  local logfile=${texfile/tex/log}
  local lotfile=${texfile/tex/lot}
  local navfile=${texfile/tex/nav}
  local outfile=${texfile/tex/out}
  local snmfile=${texfile/tex/snm}
  local tocfile=${texfile/tex/toc}

  if [ -e $pdffile ]; then
    rm $pdffile
  fi

  if [ -e $outfile ]; then
    mv $outfile ${outfile/out/OUT}
  fi

  local pdflatex ${texfile}
  local pdflatex ${texfile}
  local pdflatex ${texfile}

  for file in $auxfile $logfile $lotfile $navfile $outfile $snmfile $tocfile; do
    if [ -e $file ]; then
      rm $file
    fi
  done

  if [ -e ${outfile/out/OUT} ]; then
    mv ${outfile/out/OUT} $outfile
  fi
}
export topoanaGetPdf


function topoana()
{
  if [ -z $1 ]; then

    local cardfile=topoana.card

    if ! [ -e  $cardfile ]; then
      echo "Error: The card file \"$cardfile\" does not exist!"
      echo "Infor: Infor: The card file name is the default one."
      echo "Infor: Do you forget to append the name of your own card file to the end of the executable?"
      echo "Infor: If yes, please specify it along with the executable by the command line \"pathOfTheExecutable/topoana.exe nameOfyourOwnCardFile\""
      return -1
    fi

  else

    echo $1|grep --color=auto card$ >/dev/null 2>/dev/null
    local cardfileornot=$?
    if ! [ $cardfileornot -eq 0 ];   then
      echo "Error: The input file \"$1\" is not a card file!"
      echo "Infor: Please check it."
      return -2
    fi

    local cardfile=$1
    if ! [ -e  $cardfile ]; then
      echo "Error: The card file \"$cardfile\" does not exist!"
      echo "Infor: Please check it."
      return -3
    fi

  fi

  local OUTfile=${cardfile/card/OUT}
  local errfile=${cardfile/card/err}
  local timefile=${cardfile/card/time}
  local outfile=${cardfile/card/out}

  time (/home/belle2/zhouxy/studyarea/c++/tools/topoana/v1.3.8/bin/topoana.exe $cardfile >$OUTfile 2>$errfile) 2>$timefile
  mv $OUTfile $outfile
}