#include <iostream>
#include <vector>
#include "tree-library.h"

typedef std::vector<std::vector<std::string>> input_t;

EdgeNode* add_direct_edge_node(TreeNode* parent, tree_t value);
TreeNode* add_direct_tree_node(EdgeNode* parent, tree_t value);
TreeNode* add_branch(TreeNode* parent, tree_t edgeValue, tree_t childTreeValue);
void construct_tree_from_data(TreeNode* root, std::vector<std::vector<std::string>> input);


class A3Tree {
    private:
        TreeNode* t;

    public:
        A3Tree(std::vector<std::vector<std::string>> input){
            t = build_tree_root(input.at(0).at(0));
            construct_tree_from_data(t, input);
        }

        TreeNode* get_t() {return t;}

        std::string query(std::vector<std::string> q){
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

// returns the last existing node in path sequence. only applies to full unsimplified tree
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

void construct_tree_from_data(TreeNode* root, std::vector<std::vector<std::string>> input){
    for(int i = 1; i < input.size(); i++){
        construct_node_path(input.at(0), input.at(i), root);
    }
}

std::vector<TreeNode*> get_final_nodes(TreeNode* targetNode){
    if(targetNode == NULL) return std::vector<TreeNode*>();
    else if (targetNode->subtree_l == NULL){
        return std::vector<TreeNode*>{targetNode};
    }
    else{
        std::vector<TreeNode*> finalNodes;
        EdgeNode* it = targetNode->subtree_l;
        while(it != NULL){
            std::vector<TreeNode*> tmp = get_final_nodes(it->subtree);
            finalNodes.insert(finalNodes.end(), tmp.begin(), tmp.end());
            it = it->next;
        }
        return finalNodes;
    }
}

bool simplify_tree_node(TreeNode* targetNode){
    std::vector<TreeNode*> finalNodes = get_final_nodes(targetNode);
    std::vector<tree_t> finalNodesValues(finalNodes.size());
    for(int i = 0; i < finalNodes.size(); i++){
        finalNodesValues.at(i) = finalNodes.at(i)->val;
    }
    if(targetNode == NULL || finalNodes.empty()) return false; // should only occur if targetnode NULL
    if(finalNodes.size() == 1 && targetNode == finalNodes.at(0)) return false; // false if targetnode IS the final node
    else if(std::equal(finalNodesValues.begin()+1, finalNodesValues.end(), finalNodesValues.begin()) == true){
        targetNode->val = finalNodes.at(0)->val;
        targetNode->subtree_l = NULL;
        return true;
    }
    else return false;
}

void simplify_tree(TreeNode* t){
    if(t != NULL){
        EdgeNode* it = t->subtree_l;
        while(it != NULL){
            simplify_tree(it->subtree);
            it = it->next;
        }
        simplify_tree_node(t);
    }
}

std::vector<std::vector<std::string>> transpose_data(std::vector<std::vector<std::string>> data){
    int rows = data.size();
    int columns = data.at(0).size();
    std::vector<std::vector<std::string>> transposed(columns, std::vector<std::string>(rows));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            transposed.at(j).at(i) = data.at(i).at(j);
        }
    }
    return transposed;
}

void generate_permutations(int k, std::vector<int> &order, std::vector<std::vector<int>> &permutations){
    if(k == 1){
        permutations.push_back(order);
    }
    else {
        for (int i = 0; i < k; i++) {
			generate_permutations(k-1, order, permutations);
			if(k % 2) std::swap(order.at(0), order.at(k-1));
			else std::swap(order.at(i), order.at(k-1));
		}
    }
}

/// switches rows of the already transposed data according to specified order
std::vector<std::vector<std::string>> switch_rows(std::vector<std::vector<std::string>> data, std::vector<int> order){
    std::vector<std::vector<std::string>> tmp;
    for(int i = 0; i < order.size(); i++){ // data.size() should be 1 greater than order.size() as "not a feature" row not switched
        tmp.push_back(data.at(order.at(i)));
    }
    tmp.push_back(data.back());
    return tmp;
}

input_t switch_columns(std::vector<std::vector<std::string>> data, std::vector<int> order){
    input_t tmp = transpose_data(data);
    tmp = switch_rows(tmp, order);
    data = transpose_data(tmp);
    return data;
}

std::vector<input_t> generate_data_variations(input_t input) {
    std::vector<input_t> variations;
    std::vector<std::vector<int>> orderPermutations;
    std::vector<int> order;
    for(int i = 0; i < input.at(0).size()-1; i++){ // generate tmp = {0, 1, 2}
        order.push_back(i);
    }
    generate_permutations(order.size(), order, orderPermutations); // orderPermutations holds all permutations of tmp
    for(int i = 0; i < orderPermutations.size(); i++){
        input_t tmp = switch_columns(input, orderPermutations.at(i));
        variations.push_back(tmp);
    }
    return variations;
}