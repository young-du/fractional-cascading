//
//  Node.h
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x;
    double y;
};

struct ListNode {
    Point p;
    int left = -1;
    int right = -1;
};


class Node {
public:
    vector<ListNode> list;
    double val;
    Node* left = nullptr;
    Node* right = nullptr;
    bool isLeaf = false;
    void build_helper(vector<Point> v); // v is sorted
    void link();
};

bool comp(const ListNode& a, const ListNode& b);
#endif /* Node_h */
