CC = g++
OBJS = fvs_ic.o graph_input.o graph.o

a.out : ${OBJS}
	${CC} ${OBJS}
	./a.out

fvs.o: fvs.cpp
	${CC} -c fvs_ic.cpp

graph_input.o : graph_input.cpp
	${CC} -c graph_input.cpp

graph.o : graph.cpp
	${CC} -c graph.cpp

clean:
	\rm a.out *.o *.dot
