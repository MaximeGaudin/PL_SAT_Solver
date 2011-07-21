============================
Proposition Logic SAT Solver
============================

Author
======
* Maxime Gaudin

Purpose
=======
I'm currently doing my internship as a researcher in the calculus of computation domain and I'm working on SAT, theories combination or FOL every day. Moreover, I'm currently reading a book written by the famous Aaron Bradley : The Calculus of Computation and I realised that each algorithm is important to have a global understanding of the domain. That's why I'll try to implement at least these about PL and especially DPLL. 

Right now, the program use the Truth-table method to get an answer and therefore I discourage you to try with more than 15-20 propositions.

Finally, this code provides a ready to use flex/bison parser for the laziest of you !
Todo
----
* Implement unit resolution
* Implement DPLL

Example
=======
* To check 'A or B or NOT(C IMPLIES D)' : echo "A /\ B \/ \!(C->D)" | ./lp 
* Parameters are --sat (resp. --valid) for checking satisfiability (resp. validity) of the formula.

