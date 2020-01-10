#!/bin/bash

function clean()
{
  if [[ ${#} != 1 ]]; then
    echo -e "\e[31mERROR:\e[0m Argument is missing!"
    echo -e "\e[32mINFOR:\e[0m Input should be a pdf file. The command line should be of the following format:"
    echo -e "\e[32mINFOR:\e[0m clean.sh *.pdf"
    return 1
  fi

  local pdfFile="${1}"
  echo "${pdfFile}" | grep --color=auto pdf$ >/dev/null 2>/dev/null
  if [[ $pdffileornot != 0 ]]; then
    echo -e "\e[31mERROR:\e[0m The input file \"${pdfFile}\" is not a pdf file! Please check it."
    return 2
  fi

  if [[ ! -f "${pdfFile}" ]]; then
    echo -e "\e[31mERROR:\e[0m The pdf file \"${pdfFile}\" does not exist! Please check it."
    return 3
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

export clean
