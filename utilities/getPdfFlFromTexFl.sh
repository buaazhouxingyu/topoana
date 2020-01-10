#!/bin/bash

function getPdfFlFromTexFl()
{
  if [ -z $1 ]; then
    echo -e "\e[31mERROR:\e[0m The argument is missing!"
    echo -e "\e[32mINFOR:\e[0m It should be a .tex source file!"
    echo -e "\e[32mINFOR:\e[0m The command line should be of the following format: getPdfFlFromTexFl *.tex "
    return 1
  fi

  echo $1|grep --color=auto tex$ >/dev/null 2>/dev/null
  cppsrcfileornot=$?
  if ! [ $cppsrcfileornot -eq 0 ]; then
    echo -e "\e[31mERROR:\e[0m The input file \"$1\" is not a .tex source file!"
    echo -e "\e[32mINFOR:\e[0m Please check it."
    return 2
  fi

  if ! [ -e $1 ]; then
    echo -e "\e[31mERROR:\e[0m The tex source file \"$1\" does not exist!"
    echo -e "\e[32mINFOR:\e[0m Please check it."
    return 3
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

export getPdfFlFromTexFl
