# Polynomial Solver

This project reads polynomial roots from a JSON file (with mixed bases), constructs the polynomial of degree `k-1`, and outputs its coefficients.

## How to Compile
```bash
g++ -std=c++17 solver.cpp -o solver
```

How to Run
Run with any testcase JSON file:
```bash
./solver testcase1.json > output1.txt
./solver testcase2.json > output2.txt
```

Files:
-solver.cpp — C++ implementation.
-json.hpp — JSON parsing library (nlohmann/json single-header).
-testcase1.json — Sample test input.
-testcase2.json — Second test input.
-output1.txt — Output coefficients for testcase1.
-output2.txt — Output coefficients for testcase2.

Sample Output-
-Testcase 1 → [-336, 160, -23, 1]
-Testcase 2 → Big degree-7 polynomial coefficients (see output2.txt).
