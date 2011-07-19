%{
	#include <iostream>
	#include "Node.hpp"

	#include "parser.hh"

	extern "C" int yywrap() { return 0; }

	using namespace std;
%}

%%

[ \r\n\t]			{}

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
