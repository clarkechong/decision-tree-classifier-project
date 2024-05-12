#include <vector>
#include <iostream>

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

int main(){
    //std::vector<int> x = {1, 2, 3, 4};
    //std::vector<std::vector<int>> results;
    //generate_permutations(x.size(), x, results);

    std::vector<int> order;
    for(int i = 0; i < 3; i++){ // generate tmp = {0, 1, 2}
        order.push_back(i);
    }
    return 0;
}