#include <bits/stdc++.h>
#include "json.hpp"   // nlohmann/json single-header library

using namespace std;
using json = nlohmann::json;

// Multiply polynomial (coeffs) by (x - root)
vector<long long> multiply(const vector<long long>& poly, long long root) {
    vector<long long> res(poly.size() + 1, 0);
    for (int i = 0; i < (int)poly.size(); i++) {
        res[i] += -root * poly[i];
        res[i + 1] += poly[i];
    }
    return res;
}

// Build polynomial from roots
vector<long long> build_polynomial(const vector<long long>& roots) {
    vector<long long> coeff = {1};  // start with 1
    for (long long r : roots) {
        coeff = multiply(coeff, r);
    }
    return coeff;
}

// Safe base conversion (string -> long long)
long long parse_root(const string& value, int base) {
    // try parsing into long long, throw if too large
    try {
        return stoll(value, nullptr, base);
    } catch (const exception& e) {
        cerr << "Error: root value '" << value
             << "' in base " << base
             << " is too large for 64-bit integer.\n";
        cerr << "Consider using a BigInt library (e.g. Boost.Multiprecision).\n";
        exit(1);
    }
}

// Parse JSON, decode roots, and compute coefficients
vector<long long> solve_from_json(const json& data) {
    int n = data["keys"]["n"];
    int k = data["keys"]["k"];
    vector<long long> roots;

    for (auto& [key, val] : data.items()) {
        if (key == "keys") continue;
        int base = stoi(val["base"].get<string>());
        string value = val["value"];
        long long root = parse_root(value, base);
        roots.push_back(root);
    }

    // Use only the first k roots
    if ((int)roots.size() < k) {
        cerr << "Error: not enough roots provided. Need " << k << " but got " << roots.size() << ".\n";
        exit(1);
    }
    roots.resize(k);

    return build_polynomial(roots);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " input.json\n";
        return 1;
    }

    // Read JSON file
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Error: cannot open file " << argv[1] << "\n";
        return 1;
    }

    json data;
    try {
        in >> data;
    } catch (const exception& e) {
        cerr << "Error parsing JSON: " << e.what() << "\n";
        return 1;
    }

    // Solve polynomial
    vector<long long> coeffs = solve_from_json(data);

    // Print result (constant term first)
    cout << "[";
    for (size_t i = 0; i < coeffs.size(); i++) {
        cout << coeffs[i];
        if (i + 1 < coeffs.size()) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
