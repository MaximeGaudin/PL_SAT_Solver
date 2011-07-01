%{
	#include <iostream>
	#include "Node.hpp"

	using namespace std;

	extern int yylex();
	extern Node* root;

	void yyerror(Node& root, const char *s) { cout << "ERROR: " << s << endl; }
%}

%union {
	char tChar;
	int tInt;

	Node* tNode;
}

%parse-param{Node& root}

%token LEX_OPEN_PAR LEX_CLOSE_PAR

%token LEX_NOT
%token LEX_IFF LEX_IMPLIES LEX_OR LEX_AND 
%token LEX_PV LEX_TRUE LEX_FALSE

%left LEX_IFF LEX_IMPLIES 
%left LEX_OR 
%left LEX_AND 

%right LEX_NOT

%start root 

%type <tChar> LEX_PV

%type <tNode> formula simple_formula atom prefix_connectives binary_connectives
%%

root			: formula 				{ root = *($1); }
			;

simple_formula		: prefix_connectives simple_formula	{ $$ = $1; $1->setLeft($2); } 
			| LEX_OPEN_PAR formula LEX_CLOSE_PAR	{ $$ = $2; }
			| atom					{ $$ = $1; }
			;

formula			: simple_formula binary_connectives formula 	{ $$ = $2; $$->setLeft($1); $$->setRight($3); }
			| simple_formula			{ $$ = $1; }
			;

atom			: LEX_TRUE				{ $$ = new Node(PROPOSITION, LEX_TRUE); }
			| LEX_FALSE 				{ $$ = new Node(PROPOSITION, LEX_FALSE); }
			| LEX_PV				{ $$ = new Node(PROPOSITIONAL_VARIABLE, $1); }
			;

prefix_connectives	: LEX_NOT				{ $$ = new Node(PREFIX_CONNECTIVE, LEX_NOT); }
			;

binary_connectives	: LEX_OR				{ $$ = new Node(BINARY_CONNECTIVE, LEX_OR); }
			| LEX_AND				{ $$ = new Node(BINARY_CONNECTIVE, LEX_AND); }
			| LEX_IMPLIES				{ $$ = new Node(BINARY_CONNECTIVE, LEX_IMPLIES); }
			| LEX_IFF				{ $$ = new Node(BINARY_CONNECTIVE, LEX_IFF); }
			;
%%
