#include <iostream>
#include <string>
#include <vector>

typedef std::string tree_t;
typedef std::vector<std::vector<std::string>> input_t;

struct EdgeNode;
struct TreeNode;

class A3Tree {
    private:
        TreeNode* t;
        input_t tDataset;
        std::vector<int> tOrder;
        std::vector<TreeNode*> treeVariations;
        std::vector<input_t> dataVariations;

    public:
        A3Tree(input_t input);

        ~A3Tree();

        std::string query(std::vector<std::string> q);
        std::string node_count();
        std::string leaf_node_count();
};

EdgeNode* add_direct_edge_node(TreeNode* parent, tree_t value);
EdgeNode* cons_edge_node(TreeNode* t, EdgeNode* subtree_l, tree_t value);
TreeNode* add_branch(TreeNode* parent, tree_t edgeValue, tree_t childTreeValue);
TreeNode* add_direct_tree_node(EdgeNode* parent, tree_t value);
TreeNode* allocate_tree_node(tree_t e);
TreeNode* build_tree_root(tree_t e);
TreeNode* find_edgenode(tree_t e, TreeNode* parent);
TreeNode* find_node(tree_t e, TreeNode* t);
TreeNode* find_node_path(std::vector<std::string> path, TreeNode* root);
bool simplify_tree_node(TreeNode* targetNode);
input_t switch_columns(input_t data, std::vector<int> order);
input_t switch_rows(input_t data, std::vector<int> order);
input_t transpose_data(input_t data);
int count_leaf_nodes(TreeNode* t);
int count_nodes(TreeNode* t);
std::vector<TreeNode*> get_final_nodes(TreeNode* targetNode);
std::vector<input_t> generate_data_variations(input_t input);
std::vector<int> obtain_modified_order(input_t initialDataset, input_t modifiedDataset);
void construct_node_path(std::vector<std::string> order, std::vector<std::string> path, TreeNode* root);
void construct_tree_from_data(TreeNode* root, input_t input);
void deallocate_tree(TreeNode* t);
void generate_permutations(int k, std::vector<int> &order, std::vector<std::vector<int>> &permutations);
void simplify_tree(TreeNode* t);

struct EdgeNode{
    tree_t val;
    TreeNode* subtree;
    EdgeNode* next;
};

struct TreeNode{
    tree_t val;
    EdgeNode* subtree_l;
};

// generates and stores simplfiied tree for all possible permutations of the input data. sets t as tree with least node count
A3Tree::A3Tree(std::vector<std::vector<std::string>> input){
    dataVariations = generate_data_variations(input);
    for(int i = 0; i < dataVariations.size(); i++){
        treeVariations.push_back(build_tree_root(dataVariations.at(i).at(0).at(0)));
        construct_tree_from_data(treeVariations.at(i), dataVariations.at(i));
        simplify_tree(treeVariations.at(i));
        if(i == 0) {
            t = treeVariations.at(i);
            tDataset = dataVariations.at(i);
        }
        else if(count_nodes(treeVariations.at(i)) < count_nodes(t)) {
            t = treeVariations.at(i);
            tDataset = dataVariations.at(i);
            tOrder = obtain_modified_order(dataVariations.at(0), dataVariations.at(i));
        }
    }
}

A3Tree::~A3Tree(){
    deallocate_tree(t);
}

std::string A3Tree::query(std::vector<std::string> q){
    if(tOrder.empty()) return find_node_path(q, t)->val; // tOrder is empty if the category order of t is unchanged
    else {
        std::vector<std::string> tmp;
        for(int i = 0; i < q.size(); i++){
            tmp.push_back(q.at(tOrder.at(i)));
        }
        return find_node_path(tmp, t)->val;
    }
}

std::string A3Tree::node_count(){
    return std::to_string(count_nodes(t));
}
std::string A3Tree::leaf_node_count(){
    return std::to_string(count_leaf_nodes(t));
}

// allocates and returns pointer to edgenode assigned with specified values
EdgeNode* cons_edge_node(TreeNode* t, EdgeNode* subtree_l, tree_t value){
    EdgeNode* tmp = new EdgeNode;
    tmp->subtree = t;
    tmp->next = subtree_l;
    tmp->val = value;
    return tmp;
}

// searches direct children of parent. returns treenode of the target edgenode, or NULL if not found
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

// returns the last existing node in the queried path sequence. if no match, returns the root node
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

// constructs node path following from the last existing node in the specified path
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

// directly assigns and returns edge node of specified value to the specified parent node. inserts to the start of the existing edgenode list
EdgeNode* add_direct_edge_node(TreeNode* parent, tree_t value){
    parent->subtree_l = cons_edge_node(NULL, parent->subtree_l, value);
    return parent->subtree_l;
}

// directly assigns and returns tree node of specified value to the specified parent edgenode.
TreeNode* add_direct_tree_node(EdgeNode* parent, tree_t value){
    parent->subtree = allocate_tree_node(value);
    return parent->subtree;
}

// adds an edgenode -> treenode to an existing parent treenode. 
TreeNode* add_branch(TreeNode* parent, tree_t edgeValue, tree_t childTreeValue){
    EdgeNode* tmp = add_direct_edge_node(parent, edgeValue);
    tmp->subtree = add_direct_tree_node(tmp, childTreeValue);
    return tmp->subtree;
}

// iterates through the input dataset and constructs each path onto the root
void construct_tree_from_data(TreeNode* root, input_t input){
    for(int i = 1; i < input.size(); i++){
        construct_node_path(input.at(0), input.at(i), root);
    }
}

// returns a vector list of all the final nodes stemming from a specified target node (i.e. the "not a feature" nodes)
// operates recursively; if the queried node is itself a final node, it returns itself
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

// if all the final nodes stemming from a target node have the same value
// it can be simplified by turning the target node itself into a final node with said same value
// returns true if a simplification has been performed
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

// recursively simplifies the tree stemming from a specified (root) node
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

// transposes dataset for easier manipulation when swapping order of categories
input_t transpose_data(input_t data){
    int rows = data.size();
    int columns = data.at(0).size();
    input_t transposed(columns, std::vector<std::string>(rows));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            transposed.at(j).at(i) = data.at(i).at(j);
        }
    }
    return transposed;
}

// generates all permutations of a list using Heap's algorithm
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

// switches rows of the (already transposed) data according to specified order
// does not involve switching the last row as this is the "not a feature" row
input_t switch_rows(input_t data, std::vector<int> order){
    input_t tmp;
    for(int i = 0; i < order.size(); i++){
        tmp.push_back(data.at(order.at(i)));
    }
    tmp.push_back(data.back());
    return tmp;
}

// combines switch_rows and transpose_data to switch the order of the categories in the data (i.e. the columns)
// does not switch the last "not a feature" column
input_t switch_columns(input_t data, std::vector<int> order){
    input_t tmp = transpose_data(data);
    tmp = switch_rows(tmp, order);
    data = transpose_data(tmp);
    return data;
}

// generate all possible permutations of the initial data by switching the order of the categories
std::vector<input_t> generate_data_variations(input_t input) {
    std::vector<input_t> variations;
    std::vector<std::vector<int>> orderPermutations;
    std::vector<int> initialOrder;
    for(int i = 0; i < input.at(0).size()-1; i++){ // generate tmp = {0, 1, 2, 3, ... etc}
        initialOrder.push_back(i);
    }
    generate_permutations(initialOrder.size(), initialOrder, orderPermutations); // orderPermutations holds all permutations of tmp
    for(int i = 0; i < orderPermutations.size(); i++){
        input_t tmp = switch_columns(input, orderPermutations.at(i));
        variations.push_back(tmp);
    }
    return variations;
}

// obtain the switched order of categories of a specified modified dataset
std::vector<int> obtain_modified_order(input_t initialDataset, input_t modifiedDataset){
    std::vector<std::string> initial;
    std::vector<std::string> modified;
    std::vector<int> modifiedOrder;
    for(int i = 0; i < initialDataset.at(0).size()-1; i++){
        initial.push_back(initialDataset.at(0).at(i));
        modified.push_back(modifiedDataset.at(0).at(i));
    }
    for(int i = 0; i < initial.size(); i++){
        for(int j = 0; j < modified.size(); j++){
            if(initial.at(i) == modified.at(j)) modifiedOrder.push_back(j);
        }
    }
    return modifiedOrder;
}

TreeNode* allocate_tree_node(tree_t e){
    TreeNode* tmp = new TreeNode;
    tmp->val = e;
    tmp->subtree_l = NULL;
    return tmp;
}

TreeNode* build_tree_root(tree_t e){
    return allocate_tree_node(e);
}

TreeNode* find_node(tree_t e, TreeNode* t){
    if(t==NULL) return NULL;
    else {
        if(t->val == e) return t;
        else {
            TreeNode* tmp = NULL;
            EdgeNode* it = t->subtree_l;
            while(it != NULL && tmp == NULL){
                tmp = find_node(e, it->subtree);
                it = it->next;
            }
            return tmp;
        }
    }
}

int count_nodes(TreeNode* t){
    if(t == NULL){
        return 0;
    } 
    else {
        int tmp = 0;
        EdgeNode* it = t->subtree_l;
        while(it != NULL){
            tmp += count_nodes(it->subtree);
            it = it->next;
        }
        return (tmp + 1);
    }
}

int count_leaf_nodes(TreeNode* t){
    if(t == NULL){
        return 0;
    } 
    else {
        int tmp = 0;
        EdgeNode* it = t->subtree_l;
        while(it != NULL){
            tmp += count_leaf_nodes(it->subtree);
            it = it->next;
        }
        if(t->subtree_l == NULL) return (tmp + 1);
        else return tmp;
    }
}

void deallocate_tree(TreeNode* t){
    if(t != NULL){
        EdgeNode* it = t->subtree_l;
        EdgeNode* tmp;
        while(it != NULL){
            deallocate_tree(it->subtree);
            tmp = it;
            it = it->next;
            delete tmp;
        }
        delete t;
    }
}