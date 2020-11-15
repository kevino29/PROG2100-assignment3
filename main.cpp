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
            if ((this->denominator < 0 && this->numerator < 0) ||  // checks if both numbers are negative, turns both to positive.
                (this->denominator < 0 && this->numerator >= 0)) { // checks if denominator is negative and numerator is positive,
                this->numerator *= -1;                             // I will switch the signs so that the numerator is negative,
                this->denominator *= -1;                           // and the denominator is always positive.
            }

            int gcf = getGCF();

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

    int getGCF() {
        int lowerNum = 0;
        int gcf = 1;

        if (this->numerator > this->denominator)
            lowerNum = this->denominator;
        else if (this->denominator > this->numerator)
            lowerNum = this->numerator;
        else
            lowerNum = this->numerator;

        for (int i = lowerNum; i > 1; i--) {
            if (this->numerator % i == 0 && this->denominator % i == 0) {
                gcf = i;
                break;
            }
        }
        return gcf;
    }

    string toString() const {
        string output = to_string(this->numerator) + "/" + to_string(this->denominator);
        return output;
    }

    RationalNumber& operator+(RationalNumber& other) {
        int lcd = getLCD(this->denominator, other.denominator);


        return *this;
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

    friend ostream& operator<<(ostream& os, RationalNumber& rn);

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

    static int getLCD(int denominator1, int denominator2) {
        int higherNum = 0;
        int lowerNum = 0;
        int lcd = 1;

        if (denominator1 < denominator2) {
            higherNum = denominator2;
            lowerNum = denominator1;
        }
        else if (denominator2 < denominator1) {
            higherNum = denominator1;
            lowerNum = denominator2;
        }
        else
            higherNum = denominator1;

        for (int i = higherNum; i <= denominator1*denominator2; i++) {
            if ((i % higherNum == 0) && (i % lowerNum == 0)) {
                lcd = i;
                break;
            }
        }
        return lcd;
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

ostream& operator<<(ostream& os, RationalNumber& rn) {
    os << rn.toString() << endl;
    return os;
}

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
    rn1 + rn2;
    cout << rn1 << endl;

    // subtract both rational numbers

    // multiply both rational numbers

    // divide both rational numbers

}

int main() {
//    string input;
//
//    while (true) {
//        program();
//        cout << "Try again? (y or n)" << endl;
//        cin >> input;
//
//        if (input == "n")
//            break;
//        else
//            cout << endl;
//    }

    int i = 6;
    int j = 3;

    int k = RationalNumber::getLCD(i, j);

    cout << k << endl;

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