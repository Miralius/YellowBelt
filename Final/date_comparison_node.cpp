//
// Created by F-Mir on 3/31/2024.
//

#include "date_comparison_node.h"

#include <utility>

DateComparisonNode::DateComparisonNode(const Comparison &comparison, Date date)
        : ComparisonNode(comparison), _date(std::move(date)) {
}