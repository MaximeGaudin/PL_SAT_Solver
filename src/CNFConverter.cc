#include "NNFConverter.hpp"
#include "CNFConverter.hpp"

Node* CNF_PR_1(Node* formula) {
	if(formula->getType() == BINARY_CONNECTIVE && formula->getValue() == LEX_OR 
		&& formula->getLeft()->getType() == BINARY_CONNECTIVE && formula->getLeft()->getValue() == LEX_AND) {
		Node* F1 = formula->getLeft()->getLeft();
		Node* F2 = formula->getLeft()->getRight();
		Node* F3 = formula->getRight();

		Node* tmp2 = new Node(BINARY_CONNECTIVE, LEX_OR);
		tmp2->setLeft(F1); tmp2->setRight(F3);

		Node* tmp3 = new Node(BINARY_CONNECTIVE, LEX_OR);
		tmp3->setLeft(F2); tmp3->setRight(F3);

		Node* tmp = new Node(BINARY_CONNECTIVE, LEX_AND);
		tmp->setLeft(tmp2); tmp->setRight(tmp3);

		return tmp; 
	}

	return formula;
}

Node* CNF_PR_2(Node* formula) {
	if(formula->getType() == BINARY_CONNECTIVE && formula->getValue() == LEX_OR 
		&& formula->getRight()->getType() == BINARY_CONNECTIVE && formula->getRight()->getValue() == LEX_AND) {
		Node* F1 = formula->getLeft();
		Node* F2 = formula->getRight()->getLeft();
		Node* F3 = formula->getRight()->getRight();

		Node* tmp2 = new Node(BINARY_CONNECTIVE, LEX_OR);
		tmp2->setLeft(F1); tmp2->setRight(F2);

		Node* tmp3 = new Node(BINARY_CONNECTIVE, LEX_OR);
		tmp3->setLeft(F1); tmp3->setRight(F3);

		Node* tmp = new Node(BINARY_CONNECTIVE, LEX_AND);
		tmp->setLeft(tmp2); tmp->setRight(tmp3);

		return tmp; 
	}

	return formula;
}

void _Convert2CNF ( Node* formula ) {
	if(formula == NULL) return ;
	if(formula->getType() == PROPOSITIONAL_VARIABLE) return ;

	*formula = *CNF_PR_1(formula);
	*formula = *CNF_PR_2(formula);

	_Convert2CNF(formula->getLeft());
	_Convert2CNF(formula->getRight());
}

void Convert2CNF (Node* formula) {
	Convert2NNF(formula);
	_Convert2CNF(formula);
}


