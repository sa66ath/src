CC	= g++

TARGET	= dc.exe
OBJS	= lexer.o main.o parser.o table.o

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) -o $@ $(OBJS)


clean:	
	rm -f $(TARGET) $(OBJS)
