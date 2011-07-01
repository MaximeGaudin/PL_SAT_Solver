#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <map>

using namespace std;

enum NodeType { 
	PREFIX_CONNECTIVE, 
	BINARY_CONNECTIVE, 
	PROPOSITIONAL_VARIABLE, 
	PROPOSITION 
};

class Node 
{
	public:
		Node();
		Node(NodeType type, int value);
	
		bool isTrue ( map < int, bool > interpretation );

	public:
		NodeType getType() { return _type; }
		int getValue() { return _value; }

		void setLeft(Node* leftChild) { _children[0] = leftChild; }
		void setRight(Node* rightChild) { _children[1] = rightChild; }
		
		Node* getLeft() {return _children[0]; }
		Node* getRight() { return _children[1]; }

	public:
		string pretty();

	private:
		Node* _children[2];

		NodeType _type;
		int _value;
};
#endif 
