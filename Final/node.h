//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_NODE_H
#define YELLOW_BELT_NODE_H

#pragma once

#include "date.h"

#include <memory>

using namespace std;

class Node {
public:
    bool Evaluate(const Date &date, const string &event);
};

using NodePtr = shared_ptr<Node>;

#endif //YELLOW_BELT_NODE_H