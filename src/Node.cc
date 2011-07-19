#include "Node.hpp"
#include "parser.hh"

#include <sstream>

Node::Node ( ) {
	_children[0] = _children[1] = NULL;
	_value = -1;
}

Node::Node ( NodeType type, int value ) {
	_children[0] = _children[1] = NULL;
	_type = type;
	_value = value;
}

Node::~Node ( ) {
//	if(_children[0] != NULL) delete _children[0];
//	if(_children[1] != NULL) delete _children[1];
}

string Node::pretty() { 
	if(_type == PROPOSITIONAL_VARIABLE) {
		stringstream ss; string s;
		ss << (char)_value;
		ss >> s;
		return s;
	}

	switch (_value) {
		case(LEX_NOT): return "!";

		case(LEX_IFF): return "<->";
		case(LEX_IMPLIES): return "->";
		case(LEX_OR): return "\\\\/";
		case(LEX_AND): return "/\\\\";

		case(LEX_TRUE): return "T";
		case(LEX_FALSE): return "F";

		default: return "";
	}
}

bool Node::isTrue ( map < int, bool > interpretation ) {
	if(_type == PROPOSITIONAL_VARIABLE) return interpretation[_value];

	switch (_value) {
		case(LEX_NOT): return ! _children[0]->isTrue(interpretation);

		case(LEX_IMPLIES): 
			return !(_children[0]->isTrue(interpretation) 
			&& !_children[1]->isTrue(interpretation));

		case(LEX_IFF): return 
			!(_children[0]->isTrue(interpretation) 
			&& !_children[1]->isTrue(interpretation)) 
			&& !(_children[1]->isTrue(interpretation) 
			&& !_children[0]->isTrue(interpretation));

		case(LEX_OR): 
			return _children[0]->isTrue(interpretation) 
			|| _children[1]->isTrue(interpretation);

		case(LEX_AND): 
			return _children[0]->isTrue(interpretation) 
			&& _children[1]->isTrue(interpretation);

		case(LEX_TRUE): return true;
		case(LEX_FALSE): return false;

		default: return false;
	}

}
