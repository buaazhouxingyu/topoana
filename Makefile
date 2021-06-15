# * Author: Remco de Boer <remco.de.boer@ihep.ac.cn> (creator), Xingyu Zhou <zhouxy@lnnu.edu.cn> (reviser)
# * Date: January 11th, 2019 (created), June 13th, 2019 (revised)
# * Based on the BOSS_Afterburner repository (from Remco)
# * Only the necessary things are kept in the current revised version (from Xingyu)
# * For explanations, see:
# * - https://www.gnu.org/software/make/manual/make.html
# * - http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/


# * PATH DEFINITIONS * #

dirSOURCE := src
dirSCRIPT := src
dirINTERF := src
dirOBJECT := bin
dirEXE    := bin
dirLIB    := bin
dirDEP    := .d

extSOURCE := cpp
extSCRIPT := C
extINTERF := cxx
extOBJECT := o
extEXE    := exe
extLIB    := so
extDEP	  := d

SUFFIXES += .${extDEP}


# * COMPILER FLAGS * #

CC := g++ # clang++
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLFLAGS := $(shell root-config --libs --glibs)
# * The following statement is used for deciding whether to assign the argument 
# * "-std=c++0x" to the variable "CFLAGS" according to the current version of "gcc".
# * If the version number is lower than or equal to 4.6, then assign "-std=c++0x" 
# * to "CFLAGS". Otherwise, no assignment is performed. Here, version 4.6 is used
# * as the watershed because "gcc" starts to support c++ 11 from version 4.7.
CFLAGS     := $(shell gcc --version | sed -n '1p' \
              | awk '{print $$3}' | awk -F \. '{print $$1$$2}' \
              | awk '{if($$1<=46) {print "-std=c++0x"}}')
CFLAGS     += -g -Wfatal-errors -Wall -Wextra ${ROOTCFLAGS}
LFLAGS     := ${ROOTLFLAGS} -lTreePlayer
DEPFLAGS = -MT $@ -MMD -MP -MF ${dirDEP}/$*.Td
POSTCOMPILE = @mv -f ${dirDEP}/$*.Td ${dirDEP}/$*.${extDEP} && touch $@

PYTHONCFLAGS := $(shell python3-config --includes) -lboost_python

# * INVENTORIES OF FILES * #

# * for the sources
SOURCES := $(wildcard ${dirSOURCE}/*.${extSOURCE})

# * for the scripts
SCRIPTS := $(wildcard ${dirSCRIPT}/*.${extSCRIPT})

# * for the interfaces
INTERFS := $(wildcard ${dirINTERF}/*.${extINTERF})

# * for the objects
OBJECTS := $(SOURCES:${dirSOURCE}/%=${dirOBJECT}/%)
OBJECTS := $(OBJECTS:.${extSOURCE}=.${extOBJECT})

# * for the executables
EXES := $(SCRIPTS:${dirSCRIPT}/%=${dirEXE}/%)
EXES := $(EXES:.${extSCRIPT}=.${extEXE})

# * for the libraries
LIBS := $(INTERFS:${dirINTERF}/%=${dirLIB}/%)
LIBS := $(LIBS:.${extINTERF}=.${extLIB})

# * for the source dependencies
DEPS_SOURCE := $(SOURCES:${dirSOURCE}/%=${dirDEP}/%)
DEPS_SOURCE := $(DEPS_SOURCE:.${extSOURCE}=.${extDEP})

# * for the script dependencies
DEPS_SCRIPT := $(SCRIPTS:${dirSCRIPT}/%=${dirDEP}/%)
DEPS_SCRIPT := $(DEPS_SCRIPT:.${extSCRIPT}=.${extDEP})

# * for the script dependencies
DEPS_INTERF := $(INTERFS:${dirINTERF}/%=${dirDEP}/%)
DEPS_INTERF := $(DEPS_INTERF:.${extINTERF}=.${extDEP})

# * for the sources for the libraries
SOURCESFORLIBS := src/makeMapsOnPdata.cpp src/cutToSelect.cpp src/countSubstr.cpp src/trim.cpp src/getPidFromTxtPnm.cpp src/sortByPidAndPchrg.cpp src/writeErrInfOnPid3PchrgMap.cpp src/getStrFromLi.cpp src/writePnmFromPid.cpp src/getCcPid.cpp

# * COMPILE AND LINK RULES * #
# * (dependencies are constructed too)

.PHONY: all
all : ${EXES} ${LIBS}

# * for the libraries
${dirLIB}/%.${extLIB} : ${dirINTERF}/%.${extINTERF} ${SOURCESFORLIBS} ${dirDEP}/%.${extDEP}
	@echo "Compiling interface file \"$(notdir $<)\""
	@mkdir -p $(@D) > /dev/null
	@${CC} $< -fPIC -shared -o $@ ${CFLAGS} ${DEPFLAGS} ${SOURCESFORLIBS} ${LFLAGS} ${PYTHONCFLAGS}
	${POSTCOMPILE}
	@echo -e "\e[32;1m\"$(notdir $@)\" generated successfully!\e[0m"

# * for the executables
${dirEXE}/%.${extEXE} : ${dirSCRIPT}/%.${extSCRIPT} ${OBJECTS} ${dirDEP}/%.${extDEP}
	@echo "Compiling script file \"$(notdir $<)\""
	@mkdir -p $(@D) > /dev/null
	@${CC} $< -o $@ ${CFLAGS} ${DEPFLAGS} ${OBJECTS} ${LFLAGS}
	${POSTCOMPILE}
	@echo -e "\e[32;1m\"$(notdir $@)\" installed successfully!\e[0m"

# * for the objects
${dirOBJECT}/%.${extOBJECT} : ${dirSOURCE}/%.${extSOURCE} ${dirDEP}/%.${extDEP}
	@echo "Compiling source file \"$(notdir $<)\""
	@mkdir -p $(@D) > /dev/null
	@${CC} ${CFLAGS} ${DEPFLAGS} -c $< -o $@
	${POSTCOMPILE}
.SECONDARY:

# * for the dependencies
${dirDEP}/%.${extDEP}:
	@mkdir -p $(@D)
.PRECIOUS: ${dirDEP}/%.${extDEP}


# * CLEAN RULES * #

.PHONY : clean
clean: cleanobjects cleanexes cleanlibs

# * for the objects and the dependencies associated with them
.PHONY : cleanobjects
cleanobjects:
	@rm -rf ${OBJECTS} ${DEPS_SOURCE}

# * for the executables and the dependencies associated with them
.PHONY : cleanexes
cleanexes:
	@rm -rf ${EXES} ${DEPS_SCRIPT}

# * for the libraries and the dependencies associated with them
.PHONY : cleanlibs
cleanlibs:
	@rm -rf ${LIBS} ${DEPS_INTERF}

# * INCLUDE ALL DEPENDENCIES * #
-include ${DEPS_SOURCE} ${DEPS_SCRIPT} ${DEPS_INTERF}
