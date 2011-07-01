#ifndef DOT_CC
#define DOT_CC
#include <fstream>
#include "Node.hpp"

void visit(Node* root, ofstream& outStream);
void dotExport(string filename, Node* root);
#endif
