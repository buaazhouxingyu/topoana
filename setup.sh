#!/bin/bash

export TopoAna="$(pwd)"
export TopoAnaVersion="1.8.7"

# The following statements set the package path automatically.
sed -i 's:m_pkgPath=.*:m_pkgPath=\"'${TopoAna}'\/\";:g' include/topoana.h
sed -i 's:RequirePackage.*ifxetex:RequirePackage{'${TopoAna}'/share/ifxetex:g' share/geometry.sty
sed -i 's:m_verNum=.*:m_verNum=\"'${TopoAnaVersion}'\";:g' include/topoana.h

# The following statements recompile the package.
scripts="src/*.C"
cxxfile="src/*.cpp"
exefile="bin/topoana.exe"
if [ -f $exefile ]
then
rm $exefile
fi
ROOTCFLAGS=$(root-config --cflags)
ROOTLDFLAGS=$(root-config --ldflags --glibs)
ALLFLAGS="${ROOTCFLAGS} ${ROOTLDFLAGS} -lTreePlayer -o ${exefile} ${scripts} ${cxxfile}"

g++ -g -Wall ${ALLFLAGS}
if [[ $? != 0 ]]; then
  echo
  echo -e "\e[93mRetrying with c++0x compiler flag...\e[0m"
  g++ -g -Wall -std=c++0x ${ALLFLAGS}
fi
if [[ $? != 0 ]]; then
  ROOTLDFLAGS=$(root-config --ldflags --glibs)
  ALLFLAGS="${ROOTCFLAGS} ${ROOTLDFLAGS} -lTreePlayer -o ${exefile} ${scripts} ${cxxfile}"
  echo
  echo -e "\e[93mRetrying with ROOT5 compiler flags...\e[0m"
  g++ -g -Wall -std=c++0x ${ALLFLAGS}
fi
if [[ $? != 0 ]]; then
  echo -e "\e[91mCompilation failed! Check setup.sh script\e[0m"
  exit 1
fi

#The compiler options -std=c++0x or -std=gnu++0x should be added in order to avoid the following errors on some platforms.
#error: ISO C++ forbids declaration of `unordered_map` with no type
#error: ‘unordered_map’ does not name a type
#error: error This file requires compiler and library support for the upcoming ISO C++ standard, C++0x. This support is currently experimental, and must be enabled with the -std=c++0x or -std=gnu++0x compiler options.
#g++ -g -Wall -std=c++0x ${ROOTCFLAGS} ${ROOTLDFLAGS} -lTreePlayer -o ${exefile} ${cxxfile}

# The second method
# This method can't be used with a lower version of ROOT, such as ROOT 5.24.
#ROOTLDFLAGS=`root-config --ldflags --glibs --evelibs` # Note that the argument "--evelibs" is indispensable here; only "--ldflags" and "--glibs" are not enough!
#g++ -g -Wall ${ROOTCFLAGS} ${ROOTLDFLAGS} -o ${exefile} ${cxxfile}

echo "Here is a suggestion: in order to execute \"topoana.exe\" without any path, you had better add its absolute path to the envionment variable \"PATH\". Upon the shell you are using, you can set this up by following one of the two guidelines below:"
echo "1) In case of bash, please copy the following statement and paste it into ~/.bash_profile,"
echo "   export PATH=${TopoAna}/bin:\$PATH"
echo "2) In case of (t)csh, please copy the following statement and paste it into ~/.(t)cshrc,"
echo "   setenv PATH ${TopoAna}/bin:\$PATH"