//
// Created by F-Mir on 3/31/2024.
//

#include "event_comparison_node.h"

#include <utility>

EventComparisonNode::EventComparisonNode(const Comparison &comparison, string event)
        : ComparisonNode(comparison), _event(std::move(event)) {
}