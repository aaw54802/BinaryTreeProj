#include <iostream>
#include <fstream>
#include <string>
#include "binaryExpressionTree.h"

using namespace std;

int read() {
    // Opens the file containing postfix expressions
    ifstream inFile("RpnData.txt");
    if (!inFile) {
        cerr << "Error: Could not open RpnData.txt" << endl;
        return 1;
    }

    string expression;
    // Reads each postfix expression from the file
    while (getline(inFile, expression)) {
        cout << "Processing expression: " << expression << endl;

        // Creates a binaryExpressionTree instance
        binaryExpressionTree exprTree;

        // Builds the tree based on the postfix expression
        exprTree.buildTree(expression);

        // Evaluates the expression tree and display the result
        try {
            double result = exprTree.evaluate();
            cout << "Result: " << result << endl;
        }
        catch (const runtime_error& e) {
            cerr << "Error evaluating expression: " << e.what() << endl;
        }

        cout << "---------------------------------" << endl;
    }

    // Closes the file
    inFile.close();

    return 0;
}
