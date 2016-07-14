CC	      =	gcc

CFLAGS	      = -DALONE_DEBUG

DEST	      = .

EXTHDRS	      =

HDRS	      = wav.h

INSTALL	      = cp

LD	      = $(CC)

LDFLAGS	      = -lm

LIBS	      =

MAKEFILE      = Makefile

OBJS	      = wav.o

PRINT	      = pr

PROGRAM       = a.out

SHELL	      = /bin/sh

SRCS	      = wav.c

SYSHDRS	      = /usr/include/floatingpoint.h \
		/usr/include/math.h \
		/usr/include/stdio.h \
		/usr/include/stdlib.h \
		/usr/include/string.h \
		/usr/include/strings.h \
		/usr/include/sys/auxv.h \
		/usr/include/sys/condvar.h \
		/usr/include/sys/copyops.h \
		/usr/include/sys/cred.h \
		/usr/include/sys/errno.h \
		/usr/include/sys/feature_tests.h \
		/usr/include/sys/fsr.h \
		/usr/include/sys/ieeefp.h \
		/usr/include/sys/int_types.h \
		/usr/include/sys/isa_defs.h \
		/usr/include/sys/klwp.h \
		/usr/include/sys/lwp.h \
		/usr/include/sys/machlock.h \
		/usr/include/sys/machsig.h \
		/usr/include/sys/machtypes.h \
		/usr/include/sys/msacct.h \
		/usr/include/sys/mutex.h \
		/usr/include/sys/param.h \
		/usr/include/sys/pcb.h \
		/usr/include/sys/pirec.h \
		/usr/include/sys/proc.h \
		/usr/include/sys/procset.h \
		/usr/include/sys/regset.h \
		/usr/include/sys/resource.h \
		/usr/include/sys/rwlock.h \
		/usr/include/sys/select.h \
		/usr/include/sys/semaphore.h \
		/usr/include/sys/siginfo.h \
		/usr/include/sys/signal.h \
		/usr/include/sys/sleepq.h \
		/usr/include/sys/synch.h \
		/usr/include/sys/t_lock.h \
		/usr/include/sys/thread.h \
		/usr/include/sys/time.h \
		/usr/include/sys/timer.h \
		/usr/include/sys/turnstile.h \
		/usr/include/sys/types.h \
		/usr/include/sys/ucontext.h \
		/usr/include/sys/unistd.h \
		/usr/include/sys/user.h \
		/usr/include/sys/va_list.h \
		/usr/include/sys/wait.h \
		/usr/include/sys/watchpoint.h \
		/usr/include/time.h \
		/usr/include/v7/sys/privregs.h \
		/usr/include/v7/sys/psr.h \
		/usr/include/vm/page.h \
		/usr/include/vm/seg_enum.h

all:		$(PROGRAM)

$(PROGRAM):     $(OBJS) $(LIBS)
		@echo "Linking $(PROGRAM) ..."
		@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)
		@echo "done"

clean:;		@rm -f $(OBJS) core *.bak

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
wav.o: /usr/include/stdio.h /usr/include/sys/feature_tests.h \
	/usr/include/sys/va_list.h /usr/include/stdlib.h \
	/usr/include/sys/wait.h /usr/include/sys/types.h \
	/usr/include/sys/isa_defs.h /usr/include/sys/machtypes.h \
	/usr/include/sys/int_types.h /usr/include/sys/select.h \
	/usr/include/sys/time.h /usr/include/sys/mutex.h /usr/include/time.h \
	/usr/include/sys/siginfo.h /usr/include/sys/machsig.h \
	/usr/include/sys/resource.h /usr/include/sys/procset.h \
	/usr/include/sys/proc.h /usr/include/sys/thread.h \
	/usr/include/sys/condvar.h /usr/include/sys/t_lock.h \
	/usr/include/sys/machlock.h /usr/include/sys/sleepq.h \
	/usr/include/sys/turnstile.h /usr/include/sys/param.h \
	/usr/include/sys/unistd.h /usr/include/sys/pirec.h \
	/usr/include/sys/rwlock.h /usr/include/sys/semaphore.h \
	/usr/include/sys/klwp.h /usr/include/sys/signal.h \
	/usr/include/sys/ucontext.h /usr/include/sys/regset.h \
	/usr/include/v7/sys/privregs.h /usr/include/v7/sys/psr.h \
	/usr/include/sys/fsr.h /usr/include/sys/pcb.h \
	/usr/include/sys/msacct.h /usr/include/sys/lwp.h \
	/usr/include/sys/synch.h /usr/include/vm/page.h \
	/usr/include/sys/cred.h /usr/include/sys/user.h \
	/usr/include/sys/auxv.h /usr/include/sys/errno.h \
	/usr/include/sys/timer.h /usr/include/sys/watchpoint.h \
	/usr/include/vm/seg_enum.h /usr/include/sys/copyops.h \
	/usr/include/strings.h /usr/include/string.h /usr/include/math.h \
	/usr/include/floatingpoint.h /usr/include/sys/ieeefp.h wav.h
