# Makefile to compile SystemC codes
 
BLOCKNAME = calc

# SYSTEMC definitions
SYSTEMC_HOME ?= /opt/systemc-2.3.3
SYSTEMC_CFLAGS ?= -DSC_INCLUDE_FX -Wl,-rpath=${SYSTEMC_HOME}/lib-linux64
SYSTEMC_LIBS ?= -L${SYSTEMC_HOME}/lib-linux64 -lsystemc
SYSTEMC_INCLUDES ?= -I${SYSTEMC_HOME}/include 

# Compiler definitions
CPPFLAGS = g++ ${SYSTEMC_CFLAGS}
LIBS = -L. -lm ${SYSTEMC_LIBS}
INCLUDES = -I. ${SYSTEMC_INCLUDES}

#SOURCES = ${BLOCKNAME}.cpp  main.cpp
SOURCES = main.cpp
OUTPUT_FILE = ${BLOCKNAME}.syscexe

all: compile run

compile: 
	${CPPFLAGS} ${INCLUDES} ${LIBS} ${SOURCES} -o ${OUTPUT_FILE}

run:
	./${OUTPUT_FILE}

cr:	compile run

clean:
	@echo "=========================="
	@echo "Removing compiled files..."
	@echo "=========================="
	@rm ${OUTPUT_FILE}
