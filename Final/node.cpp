//
// Created by F-Mir on 3/30/2024.
//

#include "node.h"

EmptyNode::~EmptyNode() = default;

bool EmptyNode::Evaluate(const Date &, const string &) {
    return true;
}

ComparisonNode::ComparisonNode(const Comparison &comparison)
        : _comparison(comparison) {
}

ComparisonNode::~ComparisonNode() = default;

DateComparisonNode::DateComparisonNode(const Comparison &comparison, const Date &date)
        : ComparisonNode(comparison), _date(date) {
}

bool DateComparisonNode::Evaluate(const Date &date, const string &) {
    return ComparisonNode::compare(date, _date);
}

DateComparisonNode::~DateComparisonNode() = default;

EventComparisonNode::EventComparisonNode(const Comparison &comparison, string event)
        : ComparisonNode(comparison), _event(std::move(event)) {
}

bool EventComparisonNode::Evaluate(const Date &, const string &event) {
    return ComparisonNode::compare(event, _event);
}

EventComparisonNode::~EventComparisonNode() = default;

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logicalOperation, NodePtr left,
                                           NodePtr right)
        : _logicalOperation(logicalOperation), _left(std::move(left)), _right(std::move(right)) {
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) {
    switch (_logicalOperation)
    {
        case LogicalOperation::And:
            return _left->Evaluate(date, event) and _right->Evaluate(date, event);
        case LogicalOperation::Or:
            return _left->Evaluate(date, event) or _right->Evaluate(date, event);
        default:
            return {};
    }
}

LogicalOperationNode::~LogicalOperationNode() = default;
