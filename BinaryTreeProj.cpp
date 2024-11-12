#include <iostream>
#include <fstream>
#include <string>
#include "binaryExpressionTree.h"  // Include your binaryExpressionTree class header

using namespace std;

int read() {
    // Open the file containing postfix expressions
    ifstream inFile("RpnData.txt");
    if (!inFile) {
        cerr << "Error: Could not open RpnData.txt" << endl;
        return 1;
    }

    string expression;
    // Read each line (each postfix expression) from the file
    while (getline(inFile, expression)) {
        cout << "Processing expression: " << expression << endl;

        // Create a binaryExpressionTree instance
        binaryExpressionTree exprTree;

        // Build the tree based on the postfix expression
        exprTree.buildTree(expression);

        // Evaluate the expression tree and display the result
        try {
            double result = exprTree.evaluate();
            cout << "Result: " << result << endl;
        }
        catch (const runtime_error& e) {
            cerr << "Error evaluating expression: " << e.what() << endl;
        }

        cout << "---------------------------------" << endl;
    }

    // Close the file
    inFile.close();

    return 0;
}
