#
# Makefile for C language by mame (2001/6/26)
#

TARGET = hello

EXEF = $(TARGET).exe
CC   = bcc32
CFLAGS = #-O2

SRCS = $(TARGET).c
OBJS = ${SRCS:.c=.obj}

all : $(EXEF)

$(EXEF): $(OBJS)
	$(CC) $(OBJS)

$(OBJS): makefile $(HEADS)

.c.obj:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

run  :
	./$(EXEF)

clean :
	del $(EXEF);
	del *.obj;
	del *.tds
