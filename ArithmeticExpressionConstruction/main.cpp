#include <deque>
#include <string>
#include <iostream>

struct Operation
{
    char operation;
    int number;
};

int main() {
    std::deque<Operation> operations;

    std::string number;
    std::cin >> number;

    unsigned operationNumber;
    std::cin >> operationNumber;
    for (unsigned i = 0; i < operationNumber; ++i)
    {
        char operation;
        int operand;
        std::cin >> operation >> operand;
        operations.push_back({ operation, operand });
    }

    auto result = std::move(number);
    while (!operations.empty())
    {
        auto operation = operations.front();
        result = '(' + std::move(result) + ") " + operation.operation + ' ' + std::to_string(operation.number);
        operations.pop_front();
    }
    std::cout << result;

    return 0;
}