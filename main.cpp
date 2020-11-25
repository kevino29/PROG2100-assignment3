#include <iostream>
#include <string>
#include <vector>
#include "RationalNumber.h"

using namespace std;

void program() {
    string input;
    vector<string> numbers;
    bool boolean;
    RationalNumber rn1;
    RationalNumber rn2;
    RationalNumber rn3; // A copy of rn1, mainly used to do math with
    RationalNumber rn4; // A copy of rn2, mainly used to do math with
    cout << endl; //line break

    while (true) { //gets the first rational number
        cout << "Enter first fraction: " << endl;
        cin >> input;

        numbers = RationalNumber::parseString(input);

        if (numbers.size() == 1) { // this means that the user gave a whole number
            if (!RationalNumber::isInteger(numbers[0])) //checks if the input is an integer
                continue;
            int num = stoi(numbers[0]);
            rn1 = RationalNumber(num);
        }
        else { // this means that the user gave a fraction
            if (!RationalNumber::isInteger(numbers[0]) || !RationalNumber::isInteger(numbers[1]))
                continue; // checks if the two numbers are integers
            if (stoi(numbers[1]) == 0)
                continue; // checks if the denominator is zero
            rn1 = RationalNumber(stoi(numbers[0]), stoi(numbers[1]));
        }
        break;
    }

    while (true) { //gets the second rational number
        cout << "Enter second fraction: " << endl;
        cin >> input;
        string rn = input;

        numbers = RationalNumber::parseString(input);

        if (numbers.size() == 1) { // this means that the user gave a whole number
            if (!RationalNumber::isInteger(numbers[0])) //checks if the input is an integer
                continue;
            int num = stoi(numbers[0]);
            rn2 = RationalNumber(num);
        }
        else {
            if (!RationalNumber::isInteger(numbers[0]) || !RationalNumber::isInteger(numbers[1]))
                continue; // checks if the two numbers are integers
            if (stoi(numbers[1]) == 0)
                continue; // checks if the denominator is zero

            try { // it will throw an exception if this fails
                rn2 = RationalNumber(rn);
            }
            catch (exception& e) {
                cout << "Unexpected exception. Please try again." << endl;
            }
        }
        break;
    }

    cout << "Rational Number 1: " << rn1 << endl;
    cout << "Rational Number 2: " << rn2 << "\n" << endl;

    // add both rational numbers together
    rn3 = rn1;
    rn4 = rn2;
    rn3 + rn4;
    cout << rn1 << " + " << rn2 << " = " << rn3 << "\n" << endl;

    // subtract rn2 from rn1
    rn3 = rn1;
    rn4 = rn2;
    rn3 - rn4;
    cout << rn1 << " - " << rn2 << " = " << rn3 << "\n" << endl;

    // multiply both rational numbers
    rn3 = rn1;
    rn4 = rn2;
    rn3 * rn4;
    cout << rn1 << " * " << rn2 << " = " << rn3 << "\n" << endl;

    // divide rn1 by rn2
    rn3 = rn1;
    rn4 = rn2;
    rn3 / rn4;
    cout << rn1 << " / " << rn2 << " = " << rn3 << "\n" << endl;

    // plus equals rn1 and rn2
    rn3 = rn1;
    rn4 = rn2;
    rn3 += rn4;
    cout << rn1 << " += " << rn2 << " is " << rn3 << "\n" << endl;

    cout << boolalpha;

    // check if first rational number is greater than the second
    boolean = rn1 > rn2;
    cout << rn1 << " > " << rn2 << " : " << boolean << "\n" << endl;

    // check if first rational number is less than the second
    boolean = rn1 < rn2;
    cout << rn1 << " < " << rn2 << " : " << boolean << "\n" << endl;

    // check if first rational number is to the second
    boolean = rn1 == rn2;
    cout << rn1 << " == " << rn2 << " : " << boolean << "\n" << endl;
}

int main() {
    string input;

    while (true) {
        program();
        cout << "Try again? (y or n)" << endl;
        cin >> input;

        if (input == "n")
            break;
        else
            cout << endl;
    }
    return 0;
}