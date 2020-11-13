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
    RationalNumber() {
        this->numerator = 0;
        this->denominator = 1;
    }

    explicit RationalNumber(int numerator) {
        this->numerator = numerator;
        this->denominator = 1;
    }

    RationalNumber(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }

    explicit RationalNumber(string& rationalNumber) {
        vector<string> numbers = parseString(rationalNumber);

        this->numerator = stoi(numbers[0]);
        this->denominator = stoi(numbers[1]);
    }

    int getNumerator() const {
        return numerator;
    }

    void setNumerator(int numerator) {
        this->numerator = numerator;
    }

    int getDenominator() const {
        return denominator;
    }

    void setDenominator(int denominator) {
        this->denominator = denominator;
    }

    void normalize() {
        if (this->denominator == 1)

        int gcf = getGCF(this->numerator, this->denominator);
    }

    string toString() const {
        string output = to_string(this->numerator) + "/" + to_string(this->denominator);
        return output;
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

int main() {
    string rationalNumber = "4338/12";
    RationalNumber rn(rationalNumber);

    cout << rn.toString() << endl;

    cout << RationalNumber::getGCF(rn.getNumerator(), rn.getDenominator()) << endl;

    int input = 0;
    while (true) {
        // source: https://stackoverflow.com/questions/16934183/integer-validation-for-input
        cout << "Enter an integer: " << endl;
        cin >> input;

        if (cin.good())
            break;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input. Please try again." << endl;
        }
    }
    return 0;
}