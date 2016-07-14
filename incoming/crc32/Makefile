CC	      =	gcc

CFLAGS	      =

DEST	      = .

EXTHDRS	      =

HDRS	      =

INSTALL	      = cp

LD	      = $(CC)

LDFLAGS	      =

LIBS	      =

MAKEFILE      = Makefile

OBJS	      = crc32.o \
		main.o

PRINT	      = pr

PROGRAM       = crc32

SHELL	      = /bin/sh

SRCS	      = crc32.c \
		main.c

SYSHDRS	      = /usr/include/stdio.h \
		/usr/include/sys/feature_tests.h \
		/usr/include/sys/va_list.h

all:		$(PROGRAM)

$(PROGRAM):     $(OBJS) $(LIBS)
		@echo "Linking $(PROGRAM) ..."
		@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)
		@echo "done"

clean:;		@rm -f $(OBJS) core

clobber:;	@rm -f $(OBJS) $(PROGRAM) core tags

depend:;	@mkmf -f $(MAKEFILE)

echo:;		@echo $(HDRS) $(SRCS)

index:;		@ctags -wx $(HDRS) $(SRCS)

install:	$(PROGRAM)
		@echo Installing $(PROGRAM) in $(DEST)
		@-strip $(PROGRAM)
		@if [ $(DEST) != . ]; then \
		(rm -f $(DEST)/$(PROGRAM); $(INSTALL) $(PROGRAM) $(DEST)); fi

print:;		@$(PRINT) $(HDRS) $(SRCS)

tags:           $(HDRS) $(SRCS); @ctags $(HDRS) $(SRCS)
###
main.o: /usr/include/stdio.h /usr/include/sys/feature_tests.h \
	/usr/include/sys/va_list.h
