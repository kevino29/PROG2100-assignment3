#include <iostream>
#include <string>
#include <vector>

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

    RationalNumber(int numerator) {
        this->numerator = numerator;
        this->denominator = 1;
    }

    RationalNumber(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
    }

    RationalNumber(string& rationalNumber) {
        vector<string> numbers = parseString(rationalNumber);

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

    string toString() const {
        string output = to_string(this->numerator) + "/" + to_string(this->denominator);
        return output;
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
    string rationalNumber = "34/2";
    RationalNumber rn(rationalNumber);

    cout << rn.toString() << endl;
    return 0;
}
