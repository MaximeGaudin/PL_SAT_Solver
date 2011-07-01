%{
	#include <iostream>
	#include "Node.hpp"

	#include "parser.hpp"

	extern "C" int yywrap() { }

	using namespace std;
%}

%%

[ \t]				{}
[\r\n]				{ return NEWLINE; }

"\\/"				{ return LEX_OR; } 
"/\\"				{ return LEX_AND; }

"!"				{ return LEX_NOT; }

"->"				{ return LEX_IMPLIES; }
"<->"				{ return LEX_IFF; }

[A-EG-SU-Z]			{ yylval.tChar= *yytext; return LEX_PV; }

"T"				{ return LEX_TRUE; }
"F"				{ return LEX_FALSE; }

"("				{ return LEX_OPEN_PAR; }
")"				{ return LEX_CLOSE_PAR; }

.				{ cout << "Unknow token !" << endl; yyterminate(); }

%%
