CC = g++
OBJS = fvs_kernel.o graph_input.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}
	./a.out

fvs_kernel.o: fvs_kernel.cpp
	${CC} -c fvs_kernel.cpp

graph_input.o : graph_input.cpp
	${CC} -c graph_input.cpp

graph.o : graph.cpp
	${CC} -c graph.cpp

clean:
	\rm a.out *.o *.dot
