#include <vector>
#include <iostream>

void vprint(std::vector<std::vector<int>> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.at(i).size(); j++){
            std::cout << v[i][j] << " ";
        }
        std::cout << std::endl;
    }
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

int main(){
    std::vector<int> order;
    int x = 6;
    for(int i = 0; i < x; i++){ // generate tmp = {0, 1, 2, ... x-1}
        order.push_back(i);
    }

    std::vector<std::vector<int>> results;
    generate_permutations(order.size(), order, results);
    vprint(results);

    return 0;
}