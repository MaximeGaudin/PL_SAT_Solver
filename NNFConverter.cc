#include "NNFConverter.hpp"

Node* NNF_PR_1(Node* formula) {
	if(formula->getType() == PREFIX_CONNECTIVE && formula->getValue() == LEX_NOT 
		&& formula->getLeft()->getType() == PREFIX_CONNECTIVE && formula->getLeft()->getValue() == LEX_NOT) {
		return formula->getLeft()->getLeft();
	}

	return formula;
}

Node* NNF_PR_2(Node* formula) {
	if(formula->getType() == PREFIX_CONNECTIVE && formula->getValue() == LEX_NOT 
		&& formula->getLeft()->getType() == PROPOSITION && formula->getLeft()->getValue() == LEX_TRUE) {
		return new Node(PROPOSITION, LEX_FALSE);
	}

	return formula;
}

Node* NNF_PR_3(Node* formula) {
	if(formula->getType() == PREFIX_CONNECTIVE && formula->getValue() == LEX_NOT 
		&& formula->getLeft()->getType() == PROPOSITION && formula->getLeft()->getValue() == LEX_FALSE) {
		return new Node(PROPOSITION, LEX_TRUE);
	}

	return formula;
}

Node* NNF_PR_4(Node* formula) {
	if(formula->getType() == PREFIX_CONNECTIVE && formula->getValue() == LEX_NOT 
		&& formula->getLeft()->getType() == BINARY_CONNECTIVE && formula->getLeft()->getValue() == LEX_AND) {
		Node* tmp = new Node(BINARY_CONNECTIVE, LEX_OR);

		Node* tmp2 = new Node(PREFIX_CONNECTIVE, LEX_NOT);
		tmp2->setLeft(formula->getLeft()->getLeft());

		Node* tmp3 = new Node(PREFIX_CONNECTIVE, LEX_NOT);
		tmp3->setLeft(formula->getLeft()->getRight());

		tmp->setLeft(tmp2);
		tmp->setRight(tmp3);
		return tmp;
	}

	return formula;
}

Node* NNF_PR_5(Node* formula) {
	if(formula->getType() == PREFIX_CONNECTIVE && formula->getValue() == LEX_NOT 
		&& formula->getLeft()->getType() == BINARY_CONNECTIVE && formula->getLeft()->getValue() == LEX_OR) {
		Node* tmp = new Node(BINARY_CONNECTIVE, LEX_AND);

		Node* tmp2 = new Node(PREFIX_CONNECTIVE, LEX_NOT);
		tmp2->setLeft(formula->getLeft()->getLeft());

		Node* tmp3 = new Node(PREFIX_CONNECTIVE, LEX_NOT);
		tmp3->setLeft(formula->getLeft()->getRight());

		tmp->setLeft(tmp2);
		tmp->setRight(tmp3);
		return tmp;
	}

	return formula;
}

Node* NNF_PR_6(Node* formula) {
	if(formula->getType() == BINARY_CONNECTIVE && formula->getValue() == LEX_IMPLIES) {
		Node* tmp = new Node(BINARY_CONNECTIVE, LEX_OR);

		Node* tmp2 = new Node(PREFIX_CONNECTIVE, LEX_NOT);
		tmp2->setLeft(formula->getLeft());

		tmp->setLeft(tmp2);
		tmp->setRight(formula->getRight());
		return tmp;
	}

	return formula;
}

Node* NNF_PR_7(Node* formula) {
	if(formula->getType() == BINARY_CONNECTIVE && formula->getValue() == LEX_IFF) {
		Node* tmp = new Node(BINARY_CONNECTIVE, LEX_AND);

		Node* tmp2 = new Node(PREFIX_CONNECTIVE, LEX_IMPLIES);
		tmp2->setLeft(formula->getLeft());
		tmp2->setRight(formula->getRight());

		Node* tmp3 = new Node(PREFIX_CONNECTIVE, LEX_IMPLIES);
		tmp3->setLeft(formula->getRight());
		tmp3->setRight(formula->getLeft());

		tmp->setLeft(NNF_PR_6(tmp2));
		tmp->setRight(NNF_PR_6(tmp3));

		return tmp;
	}

	return formula;
}

void Convert2NNF (Node* formula) {
	if(formula == NULL) return ;
	if(formula->getType() == PROPOSITIONAL_VARIABLE) return ;

	*formula = *NNF_PR_1(formula);
	*formula = *NNF_PR_2(formula);
	*formula = *NNF_PR_3(formula);
	*formula = *NNF_PR_4(formula);
	*formula = *NNF_PR_5(formula);
	*formula = *NNF_PR_6(formula);
	*formula = *NNF_PR_7(formula);

	Convert2NNF(formula->getLeft());
	Convert2NNF(formula->getRight());
}
