FLAGS=-g

all: lp

parser.cc: lp.y
	bison -d lp.y && mv lp.tab.c parser.cc && mv lp.tab.h parser.hpp

lexer.cc: lp.l
	flex lp.l && mv lex.yy.c lexer.cc 

bin/dot.o: dot.cc dot.hpp
	g++ $(FLAGS) -c -o bin/dot.o dot.cc

bin/Node.o: Node.cc Node.hpp
	g++ $(FLAGS) -c -o bin/Node.o Node.cc

bin/parser.o: parser.cc parser.hpp
	g++ $(FLAGS) -c -o bin/parser.o parser.cc

bin/lexer.o: lexer.cc parser.hpp
	g++ $(FLAGS) -c -o bin/lexer.o lexer.cc

bin/NNFConverter.o: NNFConverter.cc NNFConverter.hpp
	g++ $(FLAGS) -c -o bin/NNFConverter.o NNFConverter.cc

bin/CNFConverter.o: CNFConverter.cc CNFConverter.hpp
	g++ $(FLAGS) -c -o bin/CNFConverter.o CNFConverter.cc

lp: parser.cc lexer.cc main.cc bin/CNFConverter.o bin/NNFConverter.o bin/dot.o bin/Node.o bin/parser.o bin/lexer.o
	g++ $(FLAGS) -o lp bin/*.o main.cc

.PHONY: clean mrproper

clean:
	@rm -rf bin/*.o >/dev/null

mrproper: clean
	@rm -rf lp >/dev/null
	@rm -rf lexer.cc parser.cc parser.hpp *.output *.dot *.pdf >/dev/null
