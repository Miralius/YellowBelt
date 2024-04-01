//
// Created by F-Mir on 3/30/2024.
//

#include "node.h"

// TODO: Check static functions suppressing
bool Node::Evaluate(const Date &date, const string &event) { // NOLINT(*-convert-member-functions-to-static)
    // TODO: implement function
    (void) date;
    (void) event;
    return {};
}

ComparisonNode::ComparisonNode(const Comparison &comparison)
        : _comparison(comparison) {
}

DateComparisonNode::DateComparisonNode(const Comparison &comparison, const Date &date)
        : ComparisonNode(comparison), _date(date) {
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) {
    (void) event;
    switch (_comparison) {
        case Comparison::Less:
            //TODO: implement < comparator
            break;
        case Comparison::LessOrEqual:
            //TODO: implement <= comparator
            break;
        case Comparison::Greater:
            //TODO: implement > comparator
            break;
        case Comparison::GreaterOrEqual:
            //TODO: implement >= comparator
            break;
        case Comparison::Equal:
            //TODO: implement == comparator
            break;
        case Comparison::NotEqual:
            return date != _date;
    }
    return {};
}

EventComparisonNode::EventComparisonNode(const Comparison &comparison, string event)
        : ComparisonNode(comparison), _event(std::move(event)) {
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logicalOperation, NodePtr left,
                                           NodePtr right)
        : _logicalOperation(logicalOperation), _left(std::move(left)), _right(std::move(right)) {
}