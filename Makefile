CC=gcc
CFLAGS=-Wall -g
CPPFLAGS=-DDEBUG
OBJECTS= exercise.o exercise_test.o minunit.o
TARGET=exercise

all: $(TARGET)

#Pattern rule $< means the source file.   
#Next line means any .o file needed depends on the corresponding .c file and also exercise.h
%.o : %.c exercise.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< 

#Pattern rule $@ means the target file
$(TARGET): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

run: 
	./$(TARGET)
clean:
	rm $(OBJECTS)
	rm $(TARGET)
