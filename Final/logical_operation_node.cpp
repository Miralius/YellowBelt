//
// Created by F-Mir on 3/31/2024.
//

#include "logical_operation_node.h"

#include <utility>

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logicalOperation, NodePtr left,
                                           NodePtr right)
        : _logicalOperation(logicalOperation), _left(std::move(left)), _right(std::move(right)) {
}