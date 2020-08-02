
#include "price.h"

std::string digitsToWords (size_t number)
{
    static const std::string ones[] = {"","one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    static const std::string teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen","sixteen", "seventeen", "eighteen", "nineteen"};
    static const std::string tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    if (number < 10)
    {
        return ones[number];
    }
    else if (number < 20)
    {
        return teens [number - 10];
    }
    else if (number < 100)
    {
        return tens[number / 10] + ((number % 10 != 0) ? " " + digitsToWords(number % 10) : "");
    }
    else if (number < 1000)
    {
        return digitsToWords(number / 100) + " hundred" + ((number % 100 != 0) ? " and " + digitsToWords(number % 100) : "");
    }
    else if (number < 1000000)
    {
        return digitsToWords(number / 1000) + " thousand" + ((number % 1000 != 0) ? " " + digitsToWords(number % 1000) : "");
    }
    else if (number < 1000000000)
    {
        return digitsToWords(number / 1000000) + " million" + ((number % 1000000 != 0) ? " " + digitsToWords(number % 1000000) : "");
    }
    else if (number < 1000000000000)
    {
        return digitsToWords(number / 1000000000) + " billion" + ((number % 1000000000 != 0) ? " " + digitsToWords(number % 1000000000) : "");
    }

    return "error";
}

int countDigit(int n)
{
    if (n == 0)
        return 0;

    return 1 + countDigit(n / 10);
}