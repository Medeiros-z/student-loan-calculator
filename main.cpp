#include "Loan.h"
#include "Payment.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using std::chrono::year_month_day;

int main() {
    string NewOrLoad;
    cout << "New loan collection or Load from file?\n";
    cout << "Enter 'new' or 'load': ";
    cin >> NewOrLoad;

    if (NewOrLoad == "load") {
        cout << "\n" << "Enter the path of the file: ";
        string filepath;
        cin >> filepath;

        ifstream file(filepath);

        if (!file.is_open()) {
            cerr << "Error when opening the file: " + filepath;
            return 1;
        }

        json data = json::parse(file);
        vector<Loan> loans = data.get<vector<Loan>>();
        for (Loan loan : loans) {
            cout << loan.toString() << endl;
        }

    } else if (NewOrLoad == "new") {
        int numLoans;
        cout << "Enter the number of loans you want to create: ";
        cin >> numLoans;

        while (numLoans > 0) {
            
        }


    } else {
        cerr << "Not a valid command!\n";
        return 1;
    }
}
