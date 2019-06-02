# * Author: Remco de Boer <remco.de.boer@ihep.ac.cn>
# * Date: January 11th, 2019
# * Based on the BOSS_Afterburner repository
# * For explanations, see:
# * - https://www.gnu.org/software/make/manual/make.html
# * - http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/


# * PATH DEFINITIONS * #
SUFFIXES += .d
dirINC     := inc
dirLIB     := lib
dirSOURCES := src
dirSCRIPTS := src

dirDEP := .d
dirBIN := bin
dirEXE := bin

extHEADER := h
extSOURCE := cpp
extSCRIPT := C
extOBJECT := o
extEXE    := exe

LIBNAME = TopoAna
OUTLIBF = ${dirLIB}/lib${LIBNAME}.a
INCLUDE_PATHS = -I${dirINC}


# * COMPILER FLAGS * #
CC = g++ # clang++
ROOTINC    := -I$(shell root-config --incdir)
ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS   := $(shell root-config --libs --evelibs --glibs)
CFLAGS   = \
	-fPIC -w -g -W ${ROOTCFLAGS} \
	-Wfatal-errors -Wall
LFLAGS   = ${ROOTLIBS} -lTreePlayer -g -lGenVector \
	-lRooFit -lRooFitCore -lRooStats -lMinuit
DEPFLAGS = -MT $@ -MMD -MP -MF $(dirDEP)/$*.Td
POSTCOMPILE = @mv -f $(dirDEP)/$*.Td $(dirDEP)/$*.d && touch $@


# * INVENTORIES OF FILES * #
SOURCES = $(wildcard ${dirSOURCES}/*.${extSOURCE}) $(wildcard ${dirSOURCES}/**/*.${extSOURCE})
SCRIPTS = $(wildcard ${dirSCRIPTS}/*.${extSCRIPT}) $(wildcard ${dirSCRIPTS}/**/*.${extSCRIPT})

# * for the binaries
BIN := $(SOURCES:${dirSOURCES}/%=${dirBIN}/%)
BIN := $(BIN:.${extSOURCE}=.${extOBJECT})

# * for the executables
EXE := $(SCRIPTS:${dirSCRIPTS}/%=${dirEXE}/%)
EXE := $(EXE:.${extSCRIPT}=.${extEXE})

# * for the dependencies
DEP_C := $(SCRIPTS:${dirSCRIPTS}/%=${dirDEP}/%)
DEP_X := $(SOURCES:${dirSOURCES}/%=${dirDEP}/%)
DEP_C := $(DEP_C:.${extSCRIPT}=.d)
DEP_X := $(DEP_X:.${extSCRIPT}xx=.d)
DEP   := ${DEP_C} ${DEP_X}

# * COMPILE RULES * #
# * (dependencies are constructed too)
.PHONY: all
all : ${BIN} $(OUTLIBF) ${EXE}
	@echo "\e[92;1mCOMPILING DONE\e[0m"


# * for the objects (inc and src)
${dirBIN}/%.${extOBJECT} : ${dirSOURCES}/%.${extSOURCE} $(dirDEP)/%.d #  ${dirINC}/%.h
	@echo "Compiling object \"$(notdir $<)\""
	@mkdir -p $(@D) > /dev/null
	@$(CC) $(CFLAGS) ${INCLUDE_PATHS} ${DEPFLAGS} -c $< -o $@
	$(POSTCOMPILE)

# * for linking the objects generated above.
$(OUTLIBF) : ${BIN}
	@mkdir -p "${dirLIB}"
	@ar rU $@ $^ > /dev/null
	@ranlib $@

# * for the scripts (executables)
${dirEXE}/%.${extEXE} : ${dirSCRIPTS}/%.${extSCRIPT} $(dirDEP)/%.d $(OUTLIBF)
	@echo "Compiling script \"$(notdir $<)\""
	@mkdir -p $(@D) > /dev/null
	@$(CC) $< -o $@ ${CFLAGS} ${INCLUDE_PATHS} ${DEPFLAGS} -L. ${BIN} ${LFLAGS}
	$(POSTCOMPILE)

# * for the dependencies
$(dirDEP)/%.d:
	@mkdir -p $(@D)
.PRECIOUS: $(dirDEP)/%.d

# * REMOVE ALL BINARIES * #
.PHONY : clean
clean:
	@rm -rf lib${LIBNAME}.a ${dirEXE}/* ${dirDEP}/* ${dirBIN}/*

.PHONY : cleanscripts
cleanscripts:
	@rm -rf ${dirEXE}/* ${DEP_C}

# Include all .d files
-include ${DEP}