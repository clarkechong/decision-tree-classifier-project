#include <iostream>
#include <vector>
#include "A3Tree.h"

int main(){
 
    std::vector<std::vector<std::string>> input1
    {
        {"temperature", "rain", "wind", "quality"},
        {"high", "yes", "light", "acceptable"},
        {"low", "yes", "light", "acceptable"},
        {"low", "no", "moderate", "good"},
        {"high", "yes", "strong", "poor"},
        {"high", "yes", "moderate", "acceptable"},
        {"high", "no", "moderate", "good"},
        {"low", "yes", "strong", "poor"},
        {"high", "no", "light", "good"},
        {"low", "yes", "moderate", "poor"},
        {"high", "no", "strong", "poor"}
    };
 
    std::vector<std::vector<std::string>> input2
    {
        {"Feature_3", "feature2", "feature", "feature0", "not_a_feature"},
        {"a13480", "10", "a13480", "a", "1"},
        {"B_34203", "9", "1343432", "a", "a2"},
        {"a13480", "8", "57657", "a", "3"},
        {"B_34203", "B_34203", "4523", "a", "2"},
        {"B_34203", "6", "4523", "a", "some_value"},
        {"a13480", "5", "4523", "a", "1"}
    };

    std::vector<std::vector<std::string>> inputNew = transpose_data(input1);
    std::swap(inputNew.at(0), inputNew.at(2));
    input1 = transpose_data(inputNew);
    
 
    A3Tree t1(input1);
    A3Tree t2(input2);

    simplify_tree(t1.get_t());
   
    return 0;
}