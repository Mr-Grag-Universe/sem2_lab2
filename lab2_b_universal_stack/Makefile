CC= gcc -std=c99 -DVECTOR
CFLAGS=-c -Wall -Wextra -L../lab2_b_univrsalsatck/lib

LDFLAGS= -L./lib

LIBS = -lunistack_v # -I./lib -L../stack_lib

SRCS= KGetLine.c MyString.c main.c
# SRCS = func.c func_template.c

OBJS_DIR = ./lib

OBJS=$(SRCS:.c=.o)

EXE=app1
# EXE = ./lib/libunistack_v.a

all: $(SRCS) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)
	# ar -r $@ $(OBJS) $(LIBS)
	rm -rf $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $< -c $(LIBS)

clean:
	rm -rf $(OBJS) $(EXE)
