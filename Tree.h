//
//  Tree.hpp
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include <stdio.h>
#include "Node.h"

class Tree {
public:
    Node* root = nullptr;
    void build(vector<Point> v);
    vector<Point> search(Point upperLeft, Point lowerRight);
    void printPoints(vector<Point> v);
private:
    Node* findSpliteNode(Node* n, double x1, double x2);
    void checkLeft(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res, int start, int end);
    void checkRight(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res, int start, int end);
    void checkLeaf(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res);
};

#endif /* Tree_hpp */
