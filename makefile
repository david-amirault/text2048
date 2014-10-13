#===========================================================================
#
#  Description:  
#
#    Makefile for building applications with Cygwin.
#
#  Licence:
#
#    Copyright (C) 2001,2005 Ken Fitlike
#
#    This program is free software; you can redistribute it and/or
#    modify it under the terms of the GNU General Public License
#    as published by the Free Software Foundation; either version 2
#    of the License, or (at your option) any later version.
#  
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License, http://www.gnu.org/copyleft/gpl.html
#    for more details.
#
#  Author:
#
#    Ken Fitlike. www.foosyerdoos.org.uk
#
#===========================================================================
# Use of gcc with *.cpp files implicitly causes c++ compilation - but not 
# always. Use of g++ ensures explicit c++ compilation.
# Define all rules with a <TAB> character and NOT spaces.
#
# This makefile automatically finds all source files based on file extension
# in the source subdirectory and outputs compiled object (*.o) to the
# release subdirectory.
# The same process is performed to convert resource scripts (*.rc) to 
# resource objects (*.res). The objects, source and resource, are then
# linked into the final executable.
#
# When invoking make, any of the macros defined in the makefile can be
# overridden if passed as command line parameters. For example, to specify
# the executable name (the quotes, "", are optional):
#
#        make EXENAME="another_test.exe"
#
# This makefile does not produce or use dependency information and therefore
# can only be used for complete builds in its present form.
#---------------------------------------------------------------------------
#define the compilers to be used. CXX is defined by make as g++; CC does not
#seem to be defined as gcc
CC       = g++
#---------------------------------------------------------------------------
#first name the (i)output dir (ii) include dir and (iii) resources dir
OUTDIR   = bin
SRCDIR   = src
#---------------------------------------------------------------------------
#name the final exe
EXENAME  = $(notdir $(CURDIR))
#and the source extensions
SRCEXT   = .cpp
OBJEXT   = .o
#---------------------------------------------------------------------------
#name the source files and compiled objects
SRC     := $(wildcard $(SRCDIR)/*$(SRCEXT))
SRCOBJS := $(patsubst $(SRCDIR)/%,$(OUTDIR)/%,$(subst $(SRCEXT),$(OBJEXT),$(SRC)))
#---------------------------------------------------------------------------
#finally set various flags for compiling, linking or building
CPPFLAGS = -Wall -c -g -std=c++11
#Note that -Wl,--subsystem,windows is synonymous with -mwindows; -Wl is used
#to ensure that linker switches are passed to the linker when it (ld) is
#invoked by another program, eg gcc. Both have the effect of building a 
#windows app ie. no console window.
LIBS     = 
#---------------------------------------------------------------------------
#main rule to compile the whole program ('all' - the first rule - is 
#called/invoked by default).
#link all compiled source and resource objects to produce final exe in
#output dir
all: $(OUTDIR) $(SRCOBJS)
	 $(CC) -o $(OUTDIR)/$(EXENAME) $(SRCOBJS) $(LIBS)

#create the output directory
$(OUTDIR):
	@-mkdir $(OUTDIR)

#compile all source files in src dir to object (o) files in output dir
$(OUTDIR)/%$(OBJEXT): $(SRCDIR)/%$(SRCEXT)
	$(CC) $(CPPFLAGS) $< -o $@
#===========================================================================
#cleanup
clean:
	-rm $(SRCOBJS)
	
run:
	$(OUTDIR)/$(EXENAME)
#===========================================================================
.PHONY: all clean run
#===========================================================================
