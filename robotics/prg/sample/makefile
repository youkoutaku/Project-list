#
# Makefile for C language by mame (2001/6/26)
#

TARGET = invK3d

EXEF = $(TARGET).exe
CC   = bcc32
CFLAGS = #-O2

SRCS = $(TARGET).c invK3d_l.c glwindow.c glshapes.c
HEADS = invK3d.h glwindow.h glshapes.h
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
