#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

#include "Node.hpp"
#include "dot.hpp"

#include "NNFConverter.hpp"

#include "parser.hpp"

extern int yyparse(Node& root);

using namespace std;

void recGetAllPropositions(Node* root, vector < int >* props ) {
	if ( root->getType() == PROPOSITIONAL_VARIABLE ) 
		if ( find( props->begin(), props->end(), root->getValue() ) == props->end() ) props->push_back(root->getValue());

	Node* children[2] = { root->getLeft(), root->getRight() };

	for(int i = 0; i < 2; ++i)
		if(children[i] != NULL) 
			recGetAllPropositions(children[i], props);
}

vector < int > getAllPropositions( Node* root ) {
	vector < int > buffer;
	recGetAllPropositions(root, &buffer);

	return buffer;
}

void displayInterpretation ( map < int, bool >& interpretation ) {
	map < int, bool >::iterator it = interpretation.begin();

	cout << "{ ";
	while( it != interpretation.end() ) {
		cout << (char)(it->first) 
			<< "=" << ((it->second) ? "1" : "0") << " ,";
		it++;
	}
	cout << "}" << endl; 
}

bool SAT ( Node* root, map< int, bool > interpretation, int last, int propsCount ) {
	if (last == propsCount) {
		if(root->isTrue(interpretation)) {
			displayInterpretation(interpretation);
			return true;
		}

		return false;
	}

	map< int, bool>::iterator it = interpretation.begin();
	for(int i = 0; i < last; i++) it++;

	(*it).second = false; if (SAT( root, interpretation, last + 1, propsCount)) return true;
	(*it).second = true; if (SAT( root, interpretation, last + 1, propsCount)) return true;

	return false;
}

int main(int argc, char **argv)
{
	Node root; yyparse(root); 
	vector < int > props = getAllPropositions( &root );
	map < int, bool > interpretation; for( int i = 0; i < props.size(); ++i ) interpretation[props[i]] = false; 

	if(argc == 1 || (argc == 2 && string(argv[1], 5) == string("--sat", 5))) 
		cout << "Is SAT :" << ( SAT ( &root, interpretation, 0, props.size() ) ? "Yes" : "No" ) << endl;

	if(argc == 1 || (argc == 2 && string(argv[1], 5) == string("--nnf", 5))) { 
		Convert2NNF(&root); 
		dotExport("ast.dot", &root);
	}

	if(argc == 1 || (argc == 2 && string(argv[1],7) == string("--valid",7))) {
		Node* negRoot = new Node (PREFIX_CONNECTIVE, LEX_NOT); negRoot->setLeft(&root);
		cout << "Is VALID :" << ( !SAT( negRoot, interpretation, 0, props.size() ) ? "Yes" : "No" ) << endl;
	}

	for( int i = 0; i < props.size(); ++i ) interpretation[props[i]] = false;

	return 0;
}
