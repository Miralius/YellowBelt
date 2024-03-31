//
// Created by F-Mir on 3/31/2024.
//

#ifndef YELLOW_BELT_LOGICAL_OPERATION_NODE_H
#define YELLOW_BELT_LOGICAL_OPERATION_NODE_H

#pragma once

#include "node.h"
#include "logical_operation.h"

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& logicalOperation, const NodePtr& left, const NodePtr& right);
private:
    const LogicalOperation _logicalOperation;
    const NodePtr _left;
    const NodePtr _right;
};


#endif //YELLOW_BELT_LOGICAL_OPERATION_NODE_H
