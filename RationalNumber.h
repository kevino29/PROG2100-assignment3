//

// Created by Kevin on 11/25/2020.
//

#ifndef ASSIGNMENT3_RATIONALNUMBER_H
#define ASSIGNMENT3_RATIONALNUMBER_H
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
    RationalNumber();

    explicit RationalNumber(int);

    RationalNumber(int, int);

    explicit RationalNumber(string&);

    RationalNumber& operator=(RationalNumber const&);

    int getNumerator() const;

    void setNumerator(int);

    int getDenominator() const;

    void setDenominator(int);

    /// Normalizes/Reduces the rational number.
    void normalize();

    /// Checks if the numerator is zero.
    /// \return True if the numerator is zero.
    /// \return False if the numerator is not zero.
    bool checkForNumerator() const;

    /// Gets the Greatest Common Factor of the rational number.
    /// \return GCF as an integer.
    int getGCF();

    /// Gets the rational number as a string.
    /// \return Rational number as a string.
    string toString() const;

    RationalNumber& operator+(RationalNumber&);

    RationalNumber& operator-(RationalNumber&);

    RationalNumber& operator*(RationalNumber&);

    RationalNumber& operator/(RationalNumber&);

    RationalNumber& operator+=(RationalNumber&);

    bool operator==(RationalNumber&) const;

    friend bool operator>(RationalNumber, RationalNumber);
    friend bool operator<(RationalNumber, RationalNumber);
    friend ostream& operator<<(ostream&, RationalNumber&);

    /// Checks if the value is an integer.
    /// \return True if the value is an integer.
    /// \return False if the value is not an integer.
    static bool isInteger(string&);

    /// Gets the Least Common Denominator of two denominator values.
    /// \return The LCD as an integer.
    static int getLCD(int, int);

    /// Parses the string into a vector of string.
    /// \return The parsed string as a string vector.
    static vector<string> parseString(string&);
};

bool operator>(RationalNumber rn1, RationalNumber rn2);

bool operator<(RationalNumber rn1, RationalNumber rn2);

ostream& operator<<(ostream& os, RationalNumber& rn);

#endif //ASSIGNMENT3_RATIONALNUMBER_H
