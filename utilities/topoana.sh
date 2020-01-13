#!/bin/bash

function topoana()
{
  if [ -z $1 ]; then

    local cardFile=topoana.card

    if ! [ -e  $cardFile ]; then
      echo -e "\e[31mERROR:\e[0m The card file \"$cardFile\" does not exist!"
      echo -e "\e[32mINFOR:\e[0m The card file name is the default one."
      echo -e "\e[32mINFOR:\e[0m Do you forget to append the name of your own card file to the end of the executable?"
      echo -e "\e[32mINFOR:\e[0m If yes, please specify it along with the executable by the command line \"topoana.exe nameOfyourOwnCardFile\""
      return 1
    fi

  else

    echo $1|grep --color=auto card$ >/dev/null 2>/dev/null
    local cardFileOrNot=$?
    if ! [ $cardFileOrNot -eq 0 ];   then
      echo -e "\e[31mERROR:\e[0m The input file \"$1\" is not a card file!"
      echo -e "\e[32mINFOR:\e[0m Please check it."
      return 2
    fi

    local cardFile=$1
    if ! [ -e  $cardFile ]; then
      echo -e "\e[31mERROR:\e[0m The card file \"$cardFile\" does not exist!"
      echo -e "\e[32mINFOR:\e[0m Please check it."
      return 3
    fi

  fi

  local OUTFile=${cardFile/card/OUT}
  local errFile=${cardFile/card/err}
  local timeFile=${cardFile/card/time}
  local outFile=${cardFile/card/out}

  time (topoana.exe $cardFile >$OUTFile 2>$errFile) 2>$timeFile
  mv $OUTFile $outFile
}

export topoana
