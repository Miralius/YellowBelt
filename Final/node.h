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
    virtual bool Evaluate(const Date &date, const string &event) = 0;
};

using NodePtr = shared_ptr<Node>;

class EmptyNode : public Node {
public:
    virtual ~EmptyNode();

    bool Evaluate(const Date &date, const string &event) override;
};

class ComparisonNode : public Node {
public:
    explicit ComparisonNode(const Comparison &comparison);

    virtual ~ComparisonNode();

    bool Evaluate(const Date &date, const string &event) override;

protected:
    [[maybe_unused]] const Comparison _comparison; // TODO: May be [[maybe_unused] attribute isn't needed here
};

class DateComparisonNode : public ComparisonNode {
public:
    DateComparisonNode(const Comparison &comparison, const Date &date);

    ~DateComparisonNode() override;

    bool Evaluate(const Date &date, const string &event) override;

private:
    const Date _date;
};

class EventComparisonNode : public ComparisonNode {
public:
    EventComparisonNode(const Comparison &comparison, string event);

    ~EventComparisonNode() override;

    bool Evaluate(const Date &date, const string &event) override;

private:
    const string _event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation &logicalOperation, NodePtr left, NodePtr right);

    virtual ~LogicalOperationNode();

    bool Evaluate(const Date &date, const string &event) override;

private:
    [[maybe_unused]] const LogicalOperation _logicalOperation; // TODO: delete attribute if it's needed
    const NodePtr _left;
    const NodePtr _right;
};

#endif //YELLOW_BELT_NODE_H