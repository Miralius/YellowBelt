//
// Created by F-Mir on 3/30/2024.
//

#include "node.h"

EmptyNode::~EmptyNode() = default;

bool EmptyNode::Evaluate(const Date &date, const string &event) {
    // TODO: implement function;
    (void) date;
    (void) event;
    return {};
}

ComparisonNode::ComparisonNode(const Comparison &comparison)
        : _comparison(comparison) {
}

bool ComparisonNode::Evaluate(const Date &date, const string &event) {
    // TODO: implement function;
    (void) date;
    (void) event;
    return false;
}

ComparisonNode::~ComparisonNode() = default;

DateComparisonNode::DateComparisonNode(const Comparison &comparison, const Date &date)
        : ComparisonNode(comparison), _date(date) {
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) {
    (void) event;
    // TODO: implement function
    return _comparison == Comparison::NotEqual && date != _date;
}

DateComparisonNode::~DateComparisonNode() = default;

EventComparisonNode::EventComparisonNode(const Comparison &comparison, string event)
        : ComparisonNode(comparison), _event(std::move(event)) {
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) {
    // TODO: implement function
    return ComparisonNode::Evaluate(date, event);
}

EventComparisonNode::~EventComparisonNode() = default;

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logicalOperation, NodePtr left,
                                           NodePtr right)
        : _logicalOperation(logicalOperation), _left(std::move(left)), _right(std::move(right)) {
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) {
    // TODO: implement function
    (void) date;
    (void) event;
    return false;
}

LogicalOperationNode::~LogicalOperationNode() = default;
