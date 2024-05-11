#include <iostream>
#include <vector>
#include "tree-library.h"

EdgeNode* add_direct_edge_node(TreeNode* parent, tree_t value);
TreeNode* add_direct_tree_node(EdgeNode* parent, tree_t value);
TreeNode* add_branch(TreeNode* parent, tree_t edgeValue, tree_t childTreeValue);

class A3Tree {
    private:
        TreeNode* t;
        std::vector<TreeNode*> variations;

    public:
        A3Tree(std::vector<std::vector<std::string>> input){ // constructor for initial tree
            t = build_tree_root(input.at(0).at(0));
        }

        TreeNode* get_t(){
            return t;
        }

        std::string query(std::vector<std::string> q){ // query the result from a set of conditions
            return 0;
        }

        std::string node_count();
        std::string leaf_node_count();
};

EdgeNode* cons_edge_node(TreeNode* t, EdgeNode* subtree_l, tree_t value){
    EdgeNode* tmp = new EdgeNode;
    tmp->subtree = t;
    tmp->next = subtree_l;
    tmp->val = value;
    return tmp;
}

// searches direct children and returns treenode of target edgenode or NULL if not found
TreeNode* find_edgenode(tree_t e, TreeNode* parent){
    if(parent == NULL) return NULL;
    else {
        EdgeNode* it = parent->subtree_l;
        while(it != NULL){
            if(it->val == e) return it->subtree;
            it = it->next;
        }
        return NULL;
    }
}


// returns the last existing node in path sequence. only applies for full unsimplified tree
TreeNode* find_node_path(std::vector<std::string> path, TreeNode* root){
    if(root == NULL) return NULL;
    TreeNode* tmp = root;
    TreeNode* buffer = tmp;
    for(int i = 0; i < path.size(); i++){
        tmp = find_edgenode(path.at(i), tmp);
        if(tmp != NULL) buffer = tmp;
    }
    return buffer;
}

void construct_node_path(std::vector<std::string> order, std::vector<std::string> path, TreeNode* root){
    TreeNode* existingPathNode = find_node_path(path, root);
    int depth = 0;
    for(int i = 0; i < order.size(); i++){
        if(existingPathNode->val == order.at(i)) depth = i;
        std::cout << depth;
    }
    TreeNode* head = existingPathNode;

    for(int i = depth; i+1 < order.size(); i++){
        tree_t tmp = order.at(i+1);
        if(i+1 == order.size()-1) tmp = path.back();
        head = add_branch(head, path.at(i), tmp);
    }

}

EdgeNode* add_direct_edge_node(TreeNode* parent, tree_t value){
    parent->subtree_l = cons_edge_node(NULL, parent->subtree_l, value);
    return parent->subtree_l;
}

TreeNode* add_direct_tree_node(EdgeNode* parent, tree_t value){
    parent->subtree = allocate_tree_node(value);
    return parent->subtree;
}

TreeNode* add_branch(TreeNode* parent, tree_t edgeValue, tree_t childTreeValue){
    EdgeNode* tmp = add_direct_edge_node(parent, edgeValue);
    tmp->subtree = add_direct_tree_node(tmp, childTreeValue);
    return tmp->subtree;
}