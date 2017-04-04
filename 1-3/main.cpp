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
    List<int> my(5);
    for (auto i = my.begin(); i != my.end(); ++i) {
        cout << (*i).value;
    }
}
