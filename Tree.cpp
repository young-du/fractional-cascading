//
//  Tree.cpp
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#include "Tree.h"
#include "Node.h"
#include <iostream>
using namespace std;

bool operator<(const Point& a, const Point& b) {
    return a.x < b.x;
}

void Tree::build(vector<Point> v) {
    if (v.empty()) {
        root = nullptr;
        return;
    }
    sort(v.begin(), v.end());
    this->root = new Node;
    root->build_helper(v);
    root->link();
}

vector<Point> Tree::search(Point upperLeft, Point lowerRight) {
    vector<Point> res;
    Node* split = this->findSpliteNode(root, upperLeft.x, lowerRight.x);
    if (split->isLeaf) {
        checkLeaf(split, upperLeft, lowerRight, res);
        return res;
    }
    
    auto start = lower_bound(split->list.begin(), split->list.end(), ListNode{Point{-1,lowerRight.y}, -1, -1}, comp);
    auto end = upper_bound(split->list.begin(), split->list.end(), ListNode{Point{-1,upperLeft.y}, -1, -1}, comp);
    if (start == split->list.end()) return res;
    if (end == split->list.end()) end--;
    checkLeft(split->left, upperLeft, lowerRight, res, start->left, end->left);
    checkRight(split->right, upperLeft, lowerRight, res, start->right, end->right);
    return res;
}

Node* Tree::findSpliteNode(Node* n, double x1, double x2) {
    if (n->isLeaf) return n;
    if (n->val <= x1) return findSpliteNode(n->right, x1, x2);
    if (n->val >= x2) return findSpliteNode(n->left, x1, x2);
    return n;
}

void Tree::checkRight(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res, int start, int end) {
    if (n->isLeaf) {
        checkLeaf(n, upperLeft, lowerRight, res);
        return;
    }
    while (n->list[end].p.y > upperLeft.y && end >= 0) end--;
    if (end < start) return;
    if (n->val <= lowerRight.x) {
        // report all the left subtree & go right
        int reportStart = n->list[start].left;
        int reportEnd = n->list[end].left;
        while (reportEnd >= 0 && n->left->list[reportEnd].p.y > upperLeft.y) reportEnd--;
        for (int i = reportStart; i <= reportEnd; ++i) {
            res.push_back(n->left->list[i].p);
        }
        checkRight(n->right, upperLeft, lowerRight, res, n->list[start].right, n->list[end].right);
    } else {
        // go left
        checkRight(n->left, upperLeft, lowerRight, res, n->list[start].left, n->list[end].left);
    }
}

void Tree::checkLeft(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res, int start, int end) {
    if (n->isLeaf) {
        checkLeaf(n, upperLeft, lowerRight, res);
        return;
    }
    while (end >= 0 && n->list[end].p.y > upperLeft.y) end--;
    if (end < start) return;
    if (n->val >= upperLeft.x) {
        // report all the right subtree & go left
        int reportStart = n->list[start].right;
        int reportEnd = n->list[end].right;
        while (n->right->list[reportEnd].p.y > upperLeft.y && reportEnd >= 0) reportEnd--;
        for (int i = reportStart; i <= reportEnd; ++i) {
            res.push_back(n->right->list[i].p);
        }
        checkLeft(n->left, upperLeft, lowerRight, res, n->list[start].left, n->list[end].left);
    } else {
        // go right
        checkLeft(n->right, upperLeft, lowerRight, res, n->list[start].right, n->list[end].right);
    }
}

void Tree::checkLeaf(Node* n, Point upperLeft, Point lowerRight, vector<Point>& res) {
    if (n->list[0].p.y >= lowerRight.y && n->list[0].p.y <= upperLeft.y
         && n->list[0].p.x <= lowerRight.x && n->list[0].p.x >= upperLeft.x) {
        res.push_back(n->list[0].p);
    }
}

void Tree::printPoints(vector<Point> v) {
    for (auto el: v) {
        cout << "("<< el.x<<", " << el.y<< ")\n";
    }
}
