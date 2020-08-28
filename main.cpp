//
//  main.cpp
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#include <iostream>
#include "Tree.h"

using namespace std;



int main(int argc, const char * argv[]) {
    vector<Point> v;
    v.push_back(Point{2,10});
    v.push_back(Point{5,3});
    v.push_back(Point{8,4});
    v.push_back(Point{3,9});
    v.push_back(Point{4,2});
    v.push_back(Point{9,1});
    Tree t;
    t.build(v);
    auto res = t.search(Point{0, 10}, Point{5, 5});
    t.printPoints(res);
    return 0;
}
