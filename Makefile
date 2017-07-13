PROGRAM=exec_test
SRCDIR=chapter8
INCLUDEDIR=
EXCLUDE_SRCS=chapter8/ex-8.17.c
#CC=gcc -Os -U NDEBUG
CC=gcc -Os -U NDEBUG
LDFAGS=

ALLSRCS = $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.c))
SRCS = $(filter-out $(EXCLUDE_SRCS),$(ALLSRCS))
OBJS = $(SRCS:%.c=%.o)
INCLUDEDEPEND = $(SRCS:%.c=%.d)
CFLAGS := $(CFLAGS) $(INCLUDEDIR)

$(PROGRAM):$(OBJS)
	@$(CC) -o $@ $(filter %.o,$^) $(LDFLAGS)
	@echo -e '\n'Succeed to build $(PROGRAM)'\n' 
%.o:%.c
	@$(CC) -c -o $@ $(CFLAGS) $<
	@echo "CC " $<
$(INCLUDEDEPANDS):%.d:%.c
	@$(CC) $(DEPENDFLAG) $(CFLAGS)  $< | \
	sed "s?\\(.*\\):?$(basename $<).o $(basename $<).d :?g" \
	> $@ || $(RM) $@
include $(INCLUDEDEPANDS)

.PHONY:clean 
clean:
	$(Q)-rm -f $(OBJS) $(INCLUDEDEPANDS)
	@echo "Clean finish"