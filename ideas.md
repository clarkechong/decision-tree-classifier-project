- modified add node function which deconstructs sequence of nodes (i.e. no rain, high temp, strong wind) and uses the regular add node function to add one after the other
have the parameter be a type vector so that the length is dynamic
    - 

- function that detects common nodes in trees
used to simplify the tree
then count the nodes in the simplified tree and compare to other tree variations

- function to swap the order of the variables (and hence create new tree variations to see which has less nodes after simplification)
    - how to implement this?:
    imagine matrix form; take the transpose and then switch the order of the vectors.
    requires taking all the 1st elements into 1 vector, then all 2nd elements into the next vector, etc

- coefficient function to be more selective about which order to place variables. place greater weight on variables that more strongly affect the outcome to be nearer the top of the tree

- function to check if a path (given as a vector<string>) exists. if not, or if partially, then return the last node in the already existing path (the last element is always the node, the other elements are edge node values)
    what is required to create a path?
    - the order in which variables are added in that tree variation


ORDER OF OPERATION:
construct initial FULL tree with full paths
simplify
count nodes
store in array
repeat for all order variations
select tree with lowest node count