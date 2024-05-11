#pragma once

#include <iostream>
#include <string>

typedef std::string tree_t;

struct TreeNode;
struct EdgeNode;
TreeNode* allocate_tree_node(tree_t e);
EdgeNode* cons_edge_node(TreeNode* t, EdgeNode* subtree_l);
void print_tree(TreeNode* t);
TreeNode* build_tree_root(tree_t e);
TreeNode* find_node(tree_t e, TreeNode* t);
void add_tree_node(tree_t s, tree_t d, TreeNode* t);
int count_nodes(TreeNode* t);
int count_leaf_nodes(TreeNode* t);
void deallocate_tree(TreeNode* t);

struct EdgeNode{
    tree_t val;
    TreeNode* subtree;
    EdgeNode* next;
};

struct TreeNode{
    tree_t val;
    EdgeNode* subtree_l;
};

TreeNode* allocate_tree_node(tree_t e){
    TreeNode* tmp = new TreeNode;
    tmp->val = e;
    tmp->subtree_l = NULL;
    return tmp;
}

EdgeNode* cons_edge_node(TreeNode* t, EdgeNode* subtree_l){
    EdgeNode* tmp = new EdgeNode;
    tmp->subtree = t;
    tmp->next = subtree_l;
    return tmp;
}

void print_tree(TreeNode* t){
    if(t != NULL){
        EdgeNode* it = t->subtree_l;
        while(it != NULL){
            print_tree(it->subtree);
            it = it->next;
        }
        std::cout << t->val << std::endl;
    }
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

/// s = parent name, d = child name, t = tree root
void add_tree_node(tree_t s, tree_t d, TreeNode* t){
    TreeNode* parentNode = find_node(s, t);
    if(parentNode != NULL) {
        TreeNode* childNode = allocate_tree_node(d);
        parentNode->subtree_l = cons_edge_node(childNode, parentNode->subtree_l);
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