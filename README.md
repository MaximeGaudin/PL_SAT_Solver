Author
------
* Maxime Gaudin

Purpose
-------
I'm currently internship researcher in the calculus of computation domain and I'm working on SAT, theories combination, FOL every day. Moreover, I'm currently reading a book written by the famous Aaron Bradley. I realised that each algorithm is important to have a global understanding of the domain and that's why I'll try to implement at least these about PL and especially DPLL. 

Right now, the program use the Truth-table method to get an answer and therefor I discourage you to try with more than 15-20 propositions.

Finally, this code provides a flex/bison parser for the laziest of you !
Todo
----
* Implement every Normal form convertion
* Implement unit resolution
* Implement DPLL
Example
-------
* To call lp : echo "A /\ B \/ \!(C->D)" | ./lp 
stands for 'A or B or NOT(C IMPLIES D)'

* Parameters are --sat (resp. --valid) for checking satisfiability (resp. validity) of the formula.

