//
// Created by F-Mir on 3/31/2024.
//

#ifndef YELLOW_BELT_EVENT_COMPARISON_NODE_H
#define YELLOW_BELT_EVENT_COMPARISON_NODE_H

#pragma once

#include "comparison_node.h"

using namespace std;

class EventComparisonNode : public ComparisonNode {
public:
    EventComparisonNode(const Comparison& comparison, string  event);
    // TODO: May be it's needed to override Evaluate method
private:
    const string _event;
};


#endif //YELLOW_BELT_EVENT_COMPARISON_NODE_H