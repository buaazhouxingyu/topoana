#!/bin/bash

# The following statements set the package path automatically.
pkgPath=`pwd`
sed -i 's:m_pkgPath=.*:m_pkgPath=\"'$pkgPath'\/\";:g' include/topoana.h 
sed -i 's:RequirePackage.*ifxetex:RequirePackage{'$pkgPath'/share/ifxetex:g' share/geometry.sty

# The following statements compile the package.
scripts="src/*.C"
sources="src/*.cpp"
exefile="bin/topoana.exe"
if [ -f $exefile ]; then
  rm $exefile
fi
ROOTCFLAGS=$(root-config --cflags)
ROOTLDFLAGS=$(root-config --ldflags --glibs)
verNum=`gcc --version|sed -n '1p'|awk '{print $3}'|awk -F \. '{print $1$2}'`
# The following statements decide whether to add the argument "-std=c++0x" in the compile command as an compile flag according to the current version of "gcc". If the version number is higher than 4.6, then "-std=c++0x" won't be added. Otherwise, added. Here, version 4.6 is used as the watershed because "gcc" starts to support c++ 11 from version 4.7.
if [ $verNum -gt 46 ]; then
  g++ -g -Wall ${ROOTCFLAGS} ${ROOTLDFLAGS} -lTreePlayer -o ${exefile} ${sources} ${scripts}
else
  g++ -std=c++0x -g -Wall ${ROOTCFLAGS} ${ROOTLDFLAGS} -lTreePlayer -o ${exefile} ${sources} ${scripts}
fi

# The following statements suggest adding the absolute path of the executable to the envionment variable PATH.
echo "Here is a suggestion: in order to execute \"topoana.exe\" without any path, you had better add its absolute path to the envionment variable \"PATH\". Upon the shell you are using, you can set this up by following one of the two guidelines below:"
echo "1) In case of bash, please copy the following statement and paste it into ~/.bash_profile,"
echo "   export PATH=${pkgPath}/bin:\$PATH"
echo "2) In case of (t)csh, please copy the following statement and paste it into ~/.(t)cshrc,"
echo "   setenv PATH ${pkgPath}/bin:\$PATH"

exit 0
