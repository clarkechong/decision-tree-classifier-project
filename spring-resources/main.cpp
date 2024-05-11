#include "tree-library.h"
#include <fstream>
#include <cstdlib>

int main(){
    
    std::string filename;
    std::cin >> filename;
    
    std::ifstream infile;
    infile.open(filename);
    
    if(!infile.is_open()){
        std::cout << "error opening file" << std::endl;
        return(EXIT_FAILURE);
    }
    
    std::string s1, s2;
    infile >> s1;
    
    TreeNode* t1;
    t1 = build_tree_root(s1);

    while(infile >> s1 >> s2){
        add_tree_node(s1, s2, t1);
    }
    
    infile.close();
    
    print_tree(t1);
    
    std::cout << "node count: " << count_nodes(t1) << std::endl;

    ///following code added to demonstrate the issue with count_nodes
    std::cout << "node count (function called second time): " << count_nodes(t1) << std::endl;

    std::cout << "leaf node count: " << count_leaf_nodes(t1) << std::endl;

     ///following code added to demonstrate the issue with count_lead_nodes
    std::cout << "leaf node count (function called second time): " << count_leaf_nodes(t1) << std::endl;
    
    deallocate_tree(t1);

}