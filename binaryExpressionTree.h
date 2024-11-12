#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>
#include "binaryTree.h" 

class binaryExpressionTree : public binaryTreeType<std::string> {
public:
    bool search(const std::string& searchItem) const override { return false; }
    void insert(const std::string& insertItem) override { /* Not used in expression tree */ }
    void deleteNode(const std::string& deleteItem) override { /* Not used in expression tree */ }

    void buildTree(const std::string& postfixExpression);
    double evaluate() const;

private:
    bool isOperator(const std::string& token) const;
    double evaluate(nodeType<std::string>* node) const;
};

void binaryExpressionTree::buildTree(const std::string& postfixExpression) {
    std::stack<nodeType<std::string>*> stack;
    std::istringstream exprStream(postfixExpression);
    std::string token;

    while (exprStream >> token) {
        if (isOperator(token)) {
            nodeType<std::string>* right = stack.top(); stack.pop();
            nodeType<std::string>* left = stack.top(); stack.pop();
            nodeType<std::string>* operatorNode = new nodeType<std::string>();
            operatorNode->info = token;
            operatorNode->lLink = left;
            operatorNode->rLink = right;
            stack.push(operatorNode);
        }
        else {
            nodeType<std::string>* operandNode = new nodeType<std::string>();
            operandNode->info = token;
            operandNode->lLink = operandNode->rLink = nullptr;
            stack.push(operandNode);
        }
    }

    root = stack.top();
}

bool binaryExpressionTree::isOperator(const std::string& token) const {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

double binaryExpressionTree::evaluate() const {
    return evaluate(root);
}

double binaryExpressionTree::evaluate(nodeType<std::string>* node) const {
    if (node->lLink == nullptr && node->rLink == nullptr) {
        return std::stod(node->info);
    }

    double leftValue = evaluate(node->lLink);
    double rightValue = evaluate(node->rLink);

    if (node->info == "+") return leftValue + rightValue;
    else if (node->info == "-") return leftValue - rightValue;
    else if (node->info == "*") return leftValue * rightValue;
    else if (node->info == "/") {
        if (rightValue == 0) {
            throw std::runtime_error("Division by zero error");
        }
        return leftValue / rightValue;
    }

    throw std::runtime_error("Unknown operator: " + node->info);
}

// Main function
int main() {
    std::ifstream inFile("RpnData.txt");
    if (!inFile) {
        std::cerr << "File could not be opened." << std::endl;
        return 1;
    }

    std::string expression;
    while (std::getline(inFile, expression)) {
        binaryExpressionTree exprTree;
        exprTree.buildTree(expression);

        try {
            double result = exprTree.evaluate();
            std::cout << "Expression: " << expression << " = " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error evaluating expression: " << e.what() << std::endl;
        }
    }

    inFile.close();
    return 0;
}

