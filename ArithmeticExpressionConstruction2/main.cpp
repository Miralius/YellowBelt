#include <deque>
#include <string>
#include <iostream>

int main() {
    std::deque<std::string> expression;

    std::string firstNumber;
    std::cin >> firstNumber;
    expression.emplace_back(std::move(firstNumber));

    unsigned operationNumber;
    std::cin >> operationNumber;
    std::string previousOperation;
    for (unsigned i = 0; i < operationNumber; ++i) {
        std::string operation;
        std::string operand;
        std::cin >> operation >> operand;
        bool operationPriorityIsIncreased =
                (operation == "*" or operation == "/") and (previousOperation == "+" or previousOperation == "-");
        if (operationPriorityIsIncreased)
        {
            expression.emplace_front("(");
            expression.emplace_back(")");
        }
        expression.emplace_back(" ");
        expression.emplace_back(operation);
        expression.emplace_back(" ");
        expression.emplace_back(std::move(operand));
        previousOperation = std::move(operation);
    }

    while (!expression.empty())
    {
        std::cout << expression.front();
        expression.pop_front();
    }

    return 0;
}