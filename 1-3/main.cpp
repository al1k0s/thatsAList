//
//  main.cpp
//  1-3
//
//  Created by Alex Vovkotrub on 29.03.17.
//  Copyright © 2017 Alex Vovkotrub. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>

#include "List.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream input("input");
    List<int> my;
    char c;
    int number = 0, i = 0;
    while (input.read(&c, sizeof(char)))
        switch (int(c)) {
            case int(' '):
                if (number != 0) my.push_back(number);
                number = 0;
                i = 0;
                break;
            case int('+'):
                my.push_back(my.pop_back() + my.pop_back());
                break;
            case int('*'):
                my.push_back(my.pop_back() * my.pop_back());
                break;
            case int('-'):
                my.push_back(my.pop_back() - my.pop_back());
                break;
            default:
                number += pow(10, i) * (int(c)-int('0'));
                i += 1;
                break;
        }
    while (!my.empty()) {
        cout << my.pop_back() << ' ';
    }
    
}
