all: lp.l
	flex lp.l && mv lex.yy.c lexer.cc 
	bison -d lp.y && mv lp.tab.c parser.cc && mv lp.tab.h parser.hpp
	g++ -o lp dot.cc Node.cc parser.cc lexer.cc main.cc

.PHONY: clean

clean:
	rm lexer.cc parser.cc parser.hpp *.output *.dot *.pdf
