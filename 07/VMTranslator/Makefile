	### Toolchain ###
CC			= gcc
CPP			= g++
AS			= as
LD			= ld

	### Target ###

PROGRAM		= parser

	### File extensions ###
ASEXT		= .s
CEXT		= .c
CPPEXT		= .cpp
OBJEXT		= .o
BINEXT		= .exe

	### Directories ###
SRCDIR		:= ./src/
BINDIR		:= ./bin/
LIBDIR		:= ./lib/
INCDIR		:= ./inc/
OBJDIR		:= ./obj/

CDIR		:= $(SRCDIR)C/
CPPDIR		:= $(SRCDIR)CPP/
ASDIR		:= $(SRCDIR)AS/

DIR			= $(SRCDIR) $(BINDIR) $(LIBDIR) $(INCDIR) $(OBJDIR) $(CDIR) $(ASDIR) $(CPPDIR)

	### Objects ###
	
ASSOURCES	:= $(shell find $(ASDIR) -type f -name *$(ASEXT))
ASOBJECTS 	= $(patsubst $(ASDIR)%,$(OBJDIR)%,$(ASSOURCES:$(ASEXT)=$(OBJEXT)))
CSOURCES	:= $(shell find $(CDIR) -type f -name *$(CEXT))
COBJECTS	= $(patsubst $(CDIR)%,$(OBJDIR)%,$(CSOURCES:$(CEXT)=$(OBJEXT)))
CPPSOURCES	:= $(shell find $(CPPDIR) -type f -name *$(CPPEXT))
CPPOBJECTS	= $(patsubst $(CPPDIR)%,$(OBJDIR)%,$(CPPSOURCES:$(CPPEXT)=$(OBJEXT)))

OBJECTS		= $(ASOBJECTS) $(COBJECTS) $(CPPOBJECTS)

	### Flags ###

CFLAGS		+= -Wall -g

CPPFLAGS	+= -Wall -g

	### Libraries ###
	
#SEARCHDIR	= -LC:/windows/system32

#LIB			= -lkernel32

all: directory clean $(BINDIR)$(PROGRAM)$(BINEXT)

debug:
	@echo $(OBJECTS)

directory:
	@echo "Making directories: " $(DIR)
	@mkdir -p $(DIR)

$(BINDIR)$(PROGRAM)$(BINEXT): $(OBJECTS)
	$(CPP) $(CPPFLAGS) $^ -o $@ $(SEARCHDIR) $(LIB)

$(OBJDIR)%$(OBJEXT): $(CDIR)%.c
	$(CC) $(CFLAGS) -c $^ -o $@ -g -Wall
	
$(OBJDIR)%$(OBJEXT): $(CPPDIR)%.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@ -g -Wall

$(OBJDIR)%$(OBJEXT): $(ASDIR)%.s
	$(AS) -c $^ -o $@

clean:
	rm -f $(OBJDIR)*
	rm -f $(BINDIR)*.exe
	
.PHONY: all clean debug