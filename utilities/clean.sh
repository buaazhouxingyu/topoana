#!/bin/bash

function PrintError()
{
  echo -e "\e[91mERROR: ${1}\e[0m"
}

if [[ ${#} != 1 ]]; then
  PrintError "Argument is missing!"
  echo "Input should be a pdf file. The command line should be of the following format:"
  echo "    ./clean.sh *.pdf"
  exit -1
fi

pdfFile="${1}"
echo "${pdfFile}" | grep --color=auto pdf$ >/dev/null 2>/dev/null
if [[ $pdffileornot != 0 ]]; then
  PrintError "The input file \"${pdfFile}\" is not a pdf file! Please check it."
  exit -2
fi

if [[ ! -f "${pdfFile}" ]]; then
  PrintError "The pdf file \"${pdfFile}\" does not exist! Please check it."
  exit -3
fi

texFile="${pdfFile/pdf/tex}"
txtFile="${pdfFile/pdf/txt}"
rootFile="${pdfFile/pdf/root}"
outFile="${pdfFile/pdf/out}"
errFile="${pdfFile/pdf/err}"
timeFile="${pdfFile/pdf/time}"

for file in $pdfFile $texFile $txtFile $rootFile $outFile $errFile $timeFile; do
  if [ -e $file ]; then
    echo $file
    rm $file
  fi
done