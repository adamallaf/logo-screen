CC = gcc

RELEASE = release
DEBUG = debug
OBJDIR = obj

#DEBUGINFO = -g
#ASM = -D_GNU_ASSEMBLER_

OPT = -O2

LIBS = -lSDL -lSDL_image -lSDL_ttf

CFLAGS = $(OPT) -Wall $(DEBUGINFO) $(LIBS)

BIN = rpi_logo.out

OBJS = main.o get_ip.o utils.o

TARGET = $(DEBUG)

all: $(TARGET)

debug: debug_dirs $(OBJS)
	$(CC) $(CFLAGS) -o $(DEBUG)/$(BIN) $(addprefix $(OBJDIR)/,$(OBJS))
	cp Ubuntu-Regular.ttf $(DEBUG)/ubuntu.ttf

release: release_dirs $(OBJS)
	$(CC) $(CFLAGS) -o $(RELEASE)/$(BIN) $(addprefix $(OBJDIR)/,$(OBJS))
	cp Ubuntu-Regular.ttf $(RELEASE)/ubuntu.ttf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

debug_dirs:
	+@[ -d ./$(DEBUG) ] || mkdir $(DEBUG)
	+@[ -d ./$(OBJDIR) ] || mkdir $(OBJDIR)

release_dirs:
	+@[ -d ./$(RELEASE) ] || mkdir $(RELEASE)
	+@[ -d ./$(OBJDIR) ] || mkdir $(OBJDIR)

clean:
	@$(RM) -f $(DEBUG)/* $(RELEASE)/* $(OBJDIR)/*
	@rm -rf $(DEBUG) $(RELEASE) $(OBJDIR)
