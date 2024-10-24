# Decision Tree Classifier

This project implements a **Decision Tree** data structure, designed to classify datasets based on various features. The tree is constructed and simplified using an efficient algorithm that permutes feature orders and selects the minimal tree with the fewest nodes. Once constructed, the tree can be queried to classify data using the specified feature values.

## Features

- **Dynamic Tree Construction**: The tree is built based on input datasets that represent different features and their corresponding categories.
- **Tree Permutation and Simplification**: The decision tree is constructed using all permutations of feature columns to optimize its structure, and redundant nodes are removed for efficiency.
- **Querying Functionality**: Users can query the tree with specific feature values and receive a classification based on the decision tree's structure.
- **Node Counting**: The tree tracks its structure with functionality to count total nodes and leaf nodes for analysis and optimization.
- **Memory Management**: Proper memory allocation and deallocation ensure that the decision tree is efficiently managed and does not cause memory leaks.

## Core Functionalities

1. **Tree Construction**: 
   - The tree is built from datasets representing different features (e.g., weather conditions). For each permutation of feature columns, a tree is constructed and simplified.
   
2. **Tree Simplification**: 
   - After constructing each tree, the structure is simplified by removing redundant nodes. If all child nodes of a parent node lead to the same result, the parent node is collapsed into a single node.
   
3. **Querying**:
   - The decision tree can be queried using feature values (such as temperature, wind, or humidity). The tree will traverse the nodes based on the provided values and return the corresponding classification (e.g., "acceptable" or "good").
   
4. **Node Counting**:
   - The total number of nodes and leaf nodes can be counted, allowing for the evaluation of the tree's complexity.
   
5. **Memory Management**:
   - Proper memory management is handled through dynamic allocation and deallocation of nodes, ensuring that the decision tree does not cause memory leaks when created or destroyed.

## Usage Example

In the main example provided:
- A dataset consisting of weather conditions (like temperature and wind) is input to create a decision tree.
- A query such as `{"high", "yes", "moderate"}` may return a result like `"acceptable"`.
  
## Installation

To use this project, clone the repository and compile the code with a standard C++ compiler (e.g., `g++`).
<br><br>
*The original header and implementation files are included within `project files/`. The modules were combined into a single source file, main.cpp.*

```bash
g++ main.cpp -o main.exe
./decision_tree
```
