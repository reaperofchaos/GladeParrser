# change application name here (executable output name)
TARGET=GladeTemplateParser

# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
#version
VERSION=-std=c++17

PTHREAD=-pthread

CCFLAGS=$(VERSION) $(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe


# linker
LD=g++
LDFLAGS=$(PTHREAD) -export-dynamic

OBJS= gtkWidget.o \
	  signalHandler.o \
	  gladeTemplate.o \
      main.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
gtkWidget.o: gtkWidget.h
	$(CC) -c $(CCFLAGS) gtkWidget.cpp -o gtkWidget.o

signalHandler.o: signalHandler.h
	$(CC) -c $(CCFLAGS) signalHandler.cpp -o signalHandler.o
	
gladeTemplate.o: gladeTemplate.h
	$(CC) -c $(CCFLAGS) gladeTemplate.cpp -o gladeTemplate.o
	
main.o: main.cpp
	$(CC) -c $(CCFLAGS) main.cpp -o main.o
    
clean:
	rm -f *.o $(TARGET)