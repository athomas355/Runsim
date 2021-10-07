CC = gcc
CFLAGS = -g 
LFLAGS = -lrt
TARGET = runsim 
OBJS = runsim.o config.o

$(TARGET): $(OBJS) 							#LFLAGS has to come in at the end
	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS)
	$(CC) $(CFLAGS) -o destroy_shmem destroy_shmem.c config.c config.h $(LFLAGS)
	$(CC) $(CFLAGS) -o testsim testsim.c config.c config.h $(LFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -f *.o $(TARGET)