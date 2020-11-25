//

// Created by Kevin on 11/25/2020.
//

#ifndef ASSIGNMENT3_RATIONALNUMBER_H
#define ASSIGNMENT3_RATIONALNUMBER_H
using namespace std;

class RationalNumber {
private:
    int numerator;
    int denominator;

public:
    bool isZero;

public:
    RationalNumber() {}

    explicit RationalNumber(int numerator) {}

    RationalNumber(int numerator, int denominator) {}

    explicit RationalNumber(string& rationalNumber) {}

    RationalNumber& operator=(RationalNumber const& other) {}

    int getNumerator() const {}

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

    /// Normalizes/Reduces the rational number.
    void normalize() {
        if (this->denominator != 1 || this->denominator != 0) {
            if ((this->denominator < 0 && this->numerator < 0) ||  // checks if both numbers are negative, turns both to positive.
                (this->denominator < 0 && this->numerator >= 0)) { // checks if denominator is negative and numerator is positive,
                this->numerator *= -1;                             // I will switch the signs so that the numerator is negative,
                this->denominator *= -1;                           // and the denominator is always positive.
            }

            int gcf = getGCF();
            to_string(gcf);

            this->numerator /= gcf;
            this->denominator /= gcf;

            isZero = checkForNumerator();
        }
    }

    /// Checks if the numerator is zero.
    /// \return True if the numerator is zero.
    /// \return False if the numerator is not zero.
    bool checkForNumerator() const {
        if (this->numerator == 0)
            return true;
        else
            return false;
    }

    /// Gets the Greatest Common Factor of the rational number.
    /// \return GCF as an integer.
    int getGCF() {
        int lowerNum = 0;
        int gcf = 1;
        int absoluteNumerator; // absolute value of numerator

        if (this->numerator < 0) // since only the numerator will be negative, we will only get the absolute value of numerator.
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

    /// Gets the rational number as a string.
    /// \return Rational number as a string.
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

        if (this->denominator != other.getDenominator()) { // we need to get lcd if the denominators are not the same
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

        if (this->denominator != other.getDenominator()) { // we need to get lcd if the denominators are not the same
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

    RationalNumber& operator+=(RationalNumber& other) {
        int lcd = 1;

        if (this->denominator != other.getDenominator()) { // we need to get lcd if the denominators are not the same
            lcd = getLCD(this->denominator, other.denominator);

            this->numerator = this->numerator * lcd / this->denominator;
            other.numerator = other.numerator * lcd / other.denominator;

            this->denominator = lcd;
            other.denominator = lcd;
        }

        this->numerator += other.numerator;

        this->normalize();
        other.normalize();
        cout << "Overloaded += operator fired!!!" << endl;
        return *this;
    }

    bool operator==(RationalNumber& other) const {
        cout << "Overloaded == operator fired!!!" << endl;
        return ((this->numerator == other.getNumerator()) && (this->denominator == other.getDenominator()));
    }

    friend bool operator>(RationalNumber rn1, RationalNumber rn2);
    friend bool operator<(RationalNumber rn1, RationalNumber rn2);
    friend ostream& operator<<(ostream& os, RationalNumber& rn);

    /// Checks if the value is an integer.
    /// \return True if the value is an integer.
    /// \return False if the value is not an integer.
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

    /// Gets the Least Common Denominator of two denominator values.
    /// \return The LCD as an integer.
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

    /// Parses the string into a vector of string.
    /// \return The parsed string as a string vector.
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


#endif //ASSIGNMENT3_RATIONALNUMBER_H
