EXECS=lab1

MPICC?=mpicc

all: ${EXECS}

lab1: lab1.c
    ${MPICC} -o lab1 lab1.c

clean:
    rm ${EXECS}
