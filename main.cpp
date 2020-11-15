#include <iostream>
#include <string>
#include <vector>

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
        this->normalize();
        cout << "Default constructor fired!!!" << endl;
    }

    explicit RationalNumber(int numerator) {
        this->numerator = numerator;
        this->denominator = 1;
        this->normalize();
        cout << "Constructor with one int parameter fired!!!" << "\n" << endl;
    }

    RationalNumber(int numerator, int denominator) {
        this->numerator = numerator;
        this->denominator = denominator;
        this->normalize();
        cout << "Constructor with two int parameters fired!!!" << "\n" << endl;
    }

    explicit RationalNumber(string& rationalNumber) {
        vector<string> numbers = parseString(rationalNumber);

        if (!isInteger(numbers[0]))
            throw exception();
        if (!isInteger(numbers[1]))
            throw exception();

        this->numerator = stoi(numbers[0]);
        this->denominator = stoi(numbers[1]);

        this->normalize();
        cout << "Constructor with one string parameter fired!!!" << "\n" << endl;
    }

    RationalNumber& operator=(RationalNumber const& other) {
        if (&other != this) {
            this->numerator = other.getNumerator();
            this->denominator = other.getDenominator();
            this->normalize();
        }
        return *this;
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
        int absoluteNumerator; // absolute value of numerator

        if (this->numerator < 0)
            absoluteNumerator = this->numerator * -1;
        else
            absoluteNumerator = this->numerator;

        if (absoluteNumerator > this->denominator)
            lowerNum = this->denominator;
        else if (this->denominator > absoluteNumerator)
            lowerNum = absoluteNumerator;
        else
            lowerNum = absoluteNumerator;

        for (int i = lowerNum; i > 1; i--) {
            if (absoluteNumerator % i == 0 && this->denominator % i == 0) {
                gcf = i;
                break;
            }
        }
        return gcf;
    }

    string toString() const {
        if (this->isZero)
            return to_string(this->numerator);
        if (this->denominator == 1)
            return to_string(this->numerator);
        if (this->denominator != 1) {
            string output = to_string(this->numerator) + "/" + to_string(this->denominator);
            return output;
        }

        return "Stub!";
    }

    RationalNumber& operator+(RationalNumber& other) {
        int lcd = 1;

        if (this->denominator != other.getDenominator()) {
            lcd = getLCD(this->denominator, other.denominator);

            this->numerator = this->numerator * lcd / this->denominator;
            other.numerator = other.numerator * lcd / other.denominator;

            this->denominator = lcd;
            other.denominator = lcd;
        }

        this->numerator += other.numerator;

        this->normalize();
        other.normalize();
        cout << "Overloaded + operator fired!!!" << endl;
        return *this;
    }

    RationalNumber& operator-(RationalNumber& other) {
        int lcd = 1;

        if (this->denominator != other.getDenominator()) {
            lcd = getLCD(this->denominator, other.denominator);

            this->numerator = this->numerator * lcd / this->denominator;
            other.numerator = other.numerator * lcd / other.denominator;

            this->denominator = lcd;
            other.denominator = lcd;
        }

        this->numerator -= other.numerator;

        this->normalize();
        other.normalize();
        cout << "Overloaded - operator fired!!!" << endl;
        return *this;
    }

    RationalNumber& operator*(RationalNumber& other) {
        this->numerator *= other.numerator;
        this->denominator *= other.denominator;
        this->normalize();

        cout << "Overloaded * operator fired!!!" << endl;
        return *this;
    }

    RationalNumber& operator/(RationalNumber& other) {
        if (!other.isZero) { // check if we are dividing by zero
            this->numerator *= other.denominator;
            this->denominator *= other.numerator;
            this->normalize();
        }
        else {
            cout << "Division by zero." << endl;
        }
        cout << "Overloaded / operator fired!!!" << endl;
        return *this;
    }

    bool operator==(RationalNumber& other) const {
        cout << "Overloaded == operator fired!!!" << endl;
        return ((this->numerator == other.getNumerator()) && (this->denominator == other.getDenominator()));
    }

    friend bool operator>(RationalNumber rn1, RationalNumber rn2);
    friend bool operator<(RationalNumber rn1, RationalNumber rn2);
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

bool operator>(RationalNumber rn1, RationalNumber rn2) {
    rn1 - rn2;
    cout << "Overloaded > operator fired!!!" << endl;
    return (rn1.getNumerator() > 0);
}

bool operator<(RationalNumber rn1, RationalNumber rn2) {
    rn1 - rn2;
    cout << "Overloaded < operator fired!!!" << endl;
    return (rn1.getNumerator() < 0);
}

ostream& operator<<(ostream& os, RationalNumber& rn) {
    os << rn.toString();
    return os;
}

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
            rn2 = RationalNumber(rn);
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