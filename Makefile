CC = gcc
CFLAGS = -g 
LFLAGS = -lrt
TARGET = runsim 
OBJS = runsim.o testsim.o config.o

$(TARGET): $(OBJS) 							#LFLAGS has to come in at the end
	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS)
	$(CC) -o destroy_shmem destroy_shmem.c config.c config.h $(LFLAGS)



# runsim.o: runsim.c 
# 	$(CC) $(CFLAGS) -c runsim.c

# testsim.o: testsim.c 
# 	$(CC) $(CFLAGS) -c testsim.c

# config.o: config.c 
# 	$(CC) $(CFLAGS) -c config.c

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -f *.o $(TARGET)