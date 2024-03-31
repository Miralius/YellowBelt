//
// Created by F-Mir on 3/31/2024.
//

#include "logical_operation_node.h"

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logicalOperation, const NodePtr &left,
                                           const NodePtr &right)
        : _logicalOperation(logicalOperation), _left(left), _right(right) {

}
