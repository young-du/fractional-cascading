//
//  Node.cpp
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#include <stdio.h>
#include "Node.h"

using namespace std;

bool comp(const ListNode& a, const ListNode& b) {
    return a.p.y < b.p.y;
}

void Node::build_helper(vector<Point> v) {
    // v is sorted
    for (auto el: v) {
        this->list.push_back(ListNode{el, -1, -1});
    }
    sort(this->list.begin(), this->list.end(), comp);
    
    if (v.size() == 1) {
        this->isLeaf = true;
        this->val = v[0].x;
    } else {
        this->isLeaf = false;
        size_t split = this->list.size() / 2;
        this->left = new Node;
        this->left->build_helper(vector<Point>(v.begin(), v.begin()+split));
        this->right = new Node;
        this->right->build_helper(vector<Point>(v.begin()+split, v.end()));
        this->val = (v[split].x + v[split - 1].x) / 2;
    }
}

void Node::link() {
    if (this->isLeaf) return;
    for (auto &el :this->list) {
        el.left = (int)this->left->list.size() - 1;
        el.right = (int)this->right->list.size() - 1;
        for (int i = 0; i < (int)this->left->list.size(); ++i) {
            if (this->left->list[i].p.y >= el.p.y) {el.left = i; break;}
        }
        for (int i = 0; i < (int)this->right->list.size(); ++i) {
            if (this->right->list[i].p.y >= el.p.y) {el.right = i; break;}
        }
    }
    this->left->link();
    this->right->link();
}


