//
// Created by F-Mir on 3/31/2024.
//

#ifndef YELLOW_BELT_COMPARISON_NODE_H
#define YELLOW_BELT_COMPARISON_NODE_H

#pragma once

#include "node.h"
#include "comparison.h"

class ComparisonNode : public Node {
public:
    explicit ComparisonNode(const Comparison& comparison);
private:
    const Comparison _comparison;
};


#endif //YELLOW_BELT_COMPARISON_NODE_H