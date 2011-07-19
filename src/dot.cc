#include "dot.hpp"

void visit(Node* root, ofstream& outStream) {
	outStream << "\t" << (long int)(root) 
		<< " [label=\"" << root->pretty() << "\"]" << endl;

	Node* buffer[2] = { root->getLeft(), root->getRight() };

	for(int i = 0; i < 2; ++i) {
		if(buffer[i] != NULL) {
			outStream << "\t" << (long int)(root) 
				<< " -> " << (long int)(buffer[i]) << endl;
			visit(buffer[i], outStream);
		}
	}
}

void dotExport(string filename, Node* root) {
	ofstream outStream (filename.c_str());

	outStream << "digraph G {" << endl;
	visit(root, outStream);
	outStream << "}" << endl;

	outStream.close();
}
