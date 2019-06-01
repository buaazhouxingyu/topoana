#!/bin/bash

# The following statements set the package path automatically.
pkgPath=`pwd`
verNum=`basename $pkgPath`
sed -i 's:m_pkgPath=.*:m_pkgPath=\"'$pkgPath'\/\";:g' include/topoana.h 
sed -i 's:RequirePackage.*ifxetex:RequirePackage{'$pkgPath'/share/ifxetex:g' share/geometry.sty
sed -i 's:m_verNum=.*:m_verNum=\"'$verNum'\";:g' include/topoana.h

# The following statements recompile the package.
cxxfile="src/*.cpp"
exefile="bin/topoana.exe"
if [ -f $exefile ]
then
rm $exefile
fi
ROOTCFLAGS=`root-config --cflags`
# The first method
ROOTLDFLAGS=`root-config --ldflags --glibs`
g++ -g -Wall ${ROOTCFLAGS} ${ROOTLDFLAGS} -lTreePlayer -o ${exefile} ${cxxfile}
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
echo "   export PATH=$pkgPath/bin:\$PATH"
echo "2) In case of (t)csh, please copy the following statement and paste it into ~/.(t)cshrc,"
echo "   setenv PATH $pkgPath/bin:\$PATH"
exit 0
