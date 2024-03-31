//
// Created by F-Mir on 3/31/2024.
//

#ifndef YELLOW_BELT_DATE_COMPARISON_NODE_H
#define YELLOW_BELT_DATE_COMPARISON_NODE_H

#pragma once

#include "comparison_node.h"

class DateComparisonNode : public ComparisonNode {
public:
    DateComparisonNode(const Comparison &comparison, Date date);
    // TODO: May be it's needed to override Evaluate method
private:
    const Date _date;
};

#endif //YELLOW_BELT_DATE_COMPARISON_NODE_H