# Makefile created by mkmf $Id: mkmf,v 1.2 2002/10/18 18:27:26 alangenh Exp $ 


.DEFAULT:
	-touch $@
CC	= gcc
LD	= gcc

all: a.out
midirx_proc.o: midirx_proc.c midi_def.h midirx.h
	$(CC) $(CPPDEFS) $(CPPFLAGS) $(CFLAGS) -c -I.	midirx_proc.c
midirx.o: midirx.c midi_def.h midirx.h
	$(CC) $(CPPDEFS) $(CPPFLAGS) $(CFLAGS) -c -I.	midirx.c
SRC = midirx_proc.c midirx.c midi_def.h midirx.h
OBJ = midirx_proc.o midirx.o
clean: neat
	-rm -f .cppdefs $(OBJ) a.out
neat:
	-rm -f $(TMPFILES)
TAGS: $(SRC)
	etags $(SRC)
tags: $(SRC)
	ctags $(SRC)
a.out: $(OBJ)
	$(LD) $(OBJ) -o a.out $(LDFLAGS)
