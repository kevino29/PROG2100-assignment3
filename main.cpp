#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class RationalNumber {
private:
    int numerator;
    int denominator;

public:
    bool isZero;

public:
    RationalNumber() {
        this->numerator = 0;
        this->denominator = 1;
        isZero = checkForNumerator();
        cout << "Default constructor fired!!!" << endl;
    }

    explicit RationalNumber(int numerator) {
        this->numerator = numerator;
        this->denominator = 1;
        isZero = checkForNumerator();
        cout << "Constructor with one int parameter fired!!!" << endl;
    }

    RationalNumber(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
        isZero = checkForNumerator();
        cout << "Constructor with two int parameters fired!!!" << endl;
    }

    explicit RationalNumber(string& rationalNumber) {
        vector<string> numbers = parseString(rationalNumber);

        if (!isInteger(numbers[0]))
            throw exception();
        if (!isInteger(numbers[1]))
            throw exception();

        this->numerator = stoi(numbers[0]);
        this->denominator = stoi(numbers[1]);

        isZero = checkForNumerator();
        cout << "Constructor with one string parameter fired!!!" << endl;
    }

    int getNumerator() const {
        return numerator;
    }

    void setNumerator(int numerator) {
        this->numerator = numerator;
        isZero = checkForNumerator();
    }

    int getDenominator() const {
        return denominator;
    }

    void setDenominator(int denominator) {
        this->denominator = denominator;
    }

    void normalize() {
        if (this->denominator != 1 || this->denominator != 0) {
            int gcf = getGCF(this->numerator, this->denominator);

            this->numerator /= gcf;
            this->denominator /= gcf;

            isZero = checkForNumerator();
        }
    }

    bool checkForNumerator() const {
        if (this->numerator == 0)
            return true;
        else
            return false;
    }

    string toString() const {
        string output = to_string(this->numerator) + "/" + to_string(this->denominator);
        return output;
    }

    RationalNumber& operator*(RationalNumber& other) {
        this->numerator *= other.numerator;
        this->denominator *= other.denominator;
        this->normalize();
        this->isZero = this->checkForNumerator();

        cout << "Overloaded * operator fired!!!" << endl;
        return *this;
    }

    RationalNumber& operator/(RationalNumber& other) {
        if (!other.isZero) { // check if we are dividing by zero
            this->numerator *= other.denominator;
            this->denominator *= other.numerator;
            this->normalize();
            this->isZero = this->checkForNumerator();
        }
        else { // if we are dividing by zero, we set the operator caller object to zero
            this->numerator = 0;
            this->denominator = 1;
            this->isZero = this->checkForNumerator();
        }
        cout << "Overloaded / operator fired!!!" << endl;
        return *this;
    }

    static int getGCF(int num1, int num2) {
        int lowerNum = 0;
        int gcf = 1;

        if (num2 > num1)
            lowerNum = num1;
        else if (num1 > num2)
            lowerNum = num2;
        else
            lowerNum = num1;

        for (int i = lowerNum; i > 1; i--) {
            if (num1 % i == 0 && num2 % i == 0) {
                gcf = i;
                break;
            }
        }
        return gcf;
    }

    static bool isInteger(string& input) {
        //source: https://www.programiz.com/cpp-programming/library-function/cctype/isdigit
        for (char c : input) {
            if (c == '-' || c == '+')
                continue;
            else if (!isdigit(c))
                return false;
        }
        return true;
    }

    static vector<string> parseString(string& rationalNumber) {
        // source: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
        vector<string> parsedString;
        string delimiter = "/";
        size_t pos = 0;

        while ((pos = rationalNumber.find(delimiter)) != string::npos) {
            parsedString.push_back(rationalNumber.substr(0, pos));
            rationalNumber.erase(0, pos + delimiter.length());
        }
        parsedString.push_back(rationalNumber);

        return parsedString;
    }
};

void program() {
    string input;
    vector<string> numbers;
    RationalNumber rn1;
    RationalNumber rn2;

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
                continue; //checks if the two numbers are integers
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
            rn1 = RationalNumber(num);
        }
        else {
            if (!RationalNumber::isInteger(numbers[0]) || !RationalNumber::isInteger(numbers[1]))
                continue; //checks if the two numbers are integers
            rn1 = RationalNumber(rn);
        }

        break;
    }

    // add both rational numbers together

    // subtract both rational numbers

    // multiply both rational numbers

    // divide both rational numbers


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

//    int input = 0;
//    while (true) {
//        // source: https://stackoverflow.com/questions/16934183/integer-validation-for-input
//        cout << "Enter an integer: " << endl;
//        cin >> input;
//
//        if (cin.good())
//            break;
//        else {
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(),'\n');
//            cout << "Invalid input. Please try again." << endl;
//        }
//    }
    return 0;
}