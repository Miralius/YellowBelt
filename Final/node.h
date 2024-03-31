//
// Created by F-Mir on 3/30/2024.
//

#ifndef YELLOW_BELT_NODE_H
#define YELLOW_BELT_NODE_H

#pragma once

#include "date.h"
#include "logical_operation.h"
#include "comparison.h"

#include <memory>

using namespace std;

class Node {
public:
    bool Evaluate(const Date &date, const string &event);
};

using NodePtr = shared_ptr<Node>;

class EmptyNode : public Node {
    // TODO: May be it's needed to override Evaluate method
};

class ComparisonNode : public Node {
public:
    explicit ComparisonNode(const Comparison &comparison);
    // TODO: May be it's needed to override Evaluate method
private:
    [[maybe_unused]] const Comparison _comparison; // TODO: May be [[maybe_unused] attribute isn't needed here
};

class DateComparisonNode : public ComparisonNode {
public:
    DateComparisonNode(const Comparison &comparison, Date date);
    // TODO: May be it's needed to override Evaluate method
private:
    const Date _date;
};

class EventComparisonNode : public ComparisonNode {
public:
    EventComparisonNode(const Comparison &comparison, string event);
    // TODO: May be it's needed to override Evaluate method
private:
    const string _event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &logicalOperation, NodePtr left, NodePtr right);

private:
    [[maybe_unused]] const LogicalOperation _logicalOperation; // TODO: delete attribute if it's needed
    const NodePtr _left;
    const NodePtr _right;
};

#endif //YELLOW_BELT_NODE_H