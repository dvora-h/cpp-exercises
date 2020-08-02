
#ifndef FIXED_POINT_PRICE_H
#define FIXED_POINT_PRICE_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

//TODO: Finish change from price to fixed point

template <unsigned int SIZE, typename T = int> class FixedPoint;
template <unsigned int SIZE, typename T> std::ostream& operator<< (std::ostream& os, const FixedPoint<SIZE, T>& price);
template <unsigned int SIZE, typename T>
class FixedPoint {
public:
    FixedPoint<SIZE, T>(T dollar=0, short cent=0, bool sign = false);
    T getDollar()const;
    short getCent()const;
    bool isNegative()const;
    unsigned int getNumOfDig()const;
    FixedPoint<SIZE, T>& operator=(const FixedPoint<SIZE, T>& price);
    FixedPoint<SIZE, T>& operator=(T price);
    FixedPoint<SIZE, T>& operator+=(const FixedPoint<SIZE, T>& add);
    FixedPoint<SIZE, T>& operator-=(const FixedPoint<SIZE, T>& sub);
    FixedPoint<SIZE, T>& operator+=(T add);
    FixedPoint<SIZE, T>& operator-=(T sub);
    FixedPoint<SIZE, T>& operator++();
    FixedPoint<SIZE, T> operator++(int);
    FixedPoint<SIZE, T>& operator--();
    FixedPoint<SIZE, T> operator--(int);
    operator double();
    friend std::ostream& operator<< <>(std::ostream& os, const FixedPoint<SIZE, T>& price);
    std::string asString()const;
    size_t getPrecision()const;

private:
    T m_dollar;
    unsigned short m_cent;
    bool m_sign;
    unsigned int m_number_of_digits;
};

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>::FixedPoint(T dollar, short cent, bool sign):m_dollar(abs(dollar)),
                                                                m_cent(abs(cent)),
                                                                m_sign(sign),
                                                                m_number_of_digits(pow(10, SIZE))
{

    if (dollar < 0 || cent < 0){
        m_sign = true;
    }
    if (unsigned (cent) - (m_number_of_digits-1) > 0){
        m_cent = abs(cent) % m_number_of_digits;
        m_dollar += abs(cent)/m_number_of_digits;
    }
}

template <unsigned int SIZE, typename T>
inline T FixedPoint<SIZE, T>::getDollar() const { return m_dollar;}

template <unsigned int SIZE, typename T>
inline short FixedPoint<SIZE, T>::getCent() const { return m_cent; }

template <unsigned int SIZE, typename T>
inline unsigned int FixedPoint<SIZE, T>::getNumOfDig()const{ return m_number_of_digits; }

template <unsigned int SIZE, typename T>
inline bool FixedPoint<SIZE, T>::isNegative() const { return m_sign; }

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> operator-(const FixedPoint<SIZE, T>& price, const FixedPoint<SIZE, T>& minus)
{
    if (minus.isNegative())
    {
        return price + (-minus);
    }
    if (price.isNegative())
    {
        return -((-price) + minus);
    }
    if (price < minus)
    {
        return -(minus - price);
    }

    size_t dollar;
    short cent;
    dollar = price.getDollar() - minus.getDollar();
    cent = price.getCent() - minus.getCent();
    if (cent < 0)
    {
        dollar -= 1;
        cent = cent+price.getNumOfDig();
    }

    return FixedPoint<SIZE, T>(dollar, cent);
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> operator-(const FixedPoint<SIZE, T>& price, const T minus)
{
    return price - FixedPoint<SIZE, T>(minus);
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> operator*(const FixedPoint<SIZE, T>& price, const FixedPoint<SIZE, T>& mult)
{
    double d1 = double(price)*double(mult);
    T dollar = int(d1);
    short cent = (d1 - dollar) * pow(10, SIZE);

    return FixedPoint<SIZE, T>(dollar, cent);
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> operator+(const FixedPoint<SIZE, T>& price, const FixedPoint<SIZE, T>& add)
{
    if (add.isNegative())
    {
        return price - (-add);
    }
    if (price.isNegative())
    {
        return add - (-price);
    }

    return FixedPoint<SIZE, T>(price.getDollar() + add.getDollar(), price.getCent() + add.getCent());
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> operator+(const FixedPoint<SIZE, T>& price, T add)
{
    return price + FixedPoint<SIZE, T>(add);
}

template <unsigned int SIZE, typename T>
FixedPoint<SIZE, T> operator/(const FixedPoint<SIZE, T>& price, const FixedPoint<SIZE, T>& div);

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> operator-(const FixedPoint<SIZE, T>& price)
{
    return FixedPoint<SIZE, T>(price.getDollar(), price.getCent(), !price.isNegative());
}

template <unsigned int SIZE, typename T>
inline bool operator<(const FixedPoint<SIZE, T>& price1, const FixedPoint<SIZE, T>& price2)
{
    if (price1.isNegative())
    {
        if (price2.isNegative())
        {
            if (price1.getDollar() != price2.getDollar())
            {
                return price1.getDollar() > price2.getDollar();
            }

            return price1.getCent() > price2.getCent();
        }

        return true;
    }

    if (price2.isNegative())
    {
        return false;
    }

    if(price1.getDollar() != price2.getDollar())
    {
        return price1.getDollar() < price2.getDollar();
    }

    return price1.getCent() < price2.getCent();
}

template <unsigned int SIZE, typename T>
inline bool operator<=(const FixedPoint<SIZE, T>& price1, const FixedPoint<SIZE, T>& price2)
{
    return !(price1 > price2);
}

template <unsigned int SIZE, typename T>
inline bool operator>=(const FixedPoint<SIZE, T>& price1, const FixedPoint<SIZE, T>& price2)
{
    return !(price1 < price2);
}

template <unsigned int SIZE, typename T>
inline bool operator>(const FixedPoint<SIZE, T>& price1, const FixedPoint<SIZE, T>& price2)
{
    return price2 < price1;
}

template <unsigned int SIZE, typename T>
inline bool operator==(const FixedPoint<SIZE, T>& price1, const FixedPoint<SIZE, T>& price2)
{
    return (price1.getCent() == price2.getCent() && price1.getCent() == price2.getCent() && price1.isNegative() == price2.isNegative());
}

template <unsigned int SIZE, typename T>
inline bool operator!=(const FixedPoint<SIZE, T>& price1, const FixedPoint<SIZE, T>& price2)
{
    return !(price1 == price2);
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator=(const FixedPoint<SIZE, T>& price)
{
    m_dollar = price.getDollar();
    m_cent = price.getCent();
    m_sign = price.isNegative();

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator=(T price)
{
    *this = FixedPoint<SIZE, T>(price);

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator+=(const FixedPoint<SIZE, T>& add)
{
    *this = *this + add;

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator+=(T add)
{
    *this = *this + FixedPoint<SIZE, T>(add);

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator-=(const FixedPoint<SIZE, T>& sub)
{
    *this = *this - sub;

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator-=(T sub)
{
    FixedPoint<SIZE, T> p(sub);
    *this = *this - p;

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator++()
{
    *this += FixedPoint<SIZE, T>(1);

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> FixedPoint<SIZE, T>::operator++(int)
{
    FixedPoint<SIZE, T> res(*this);
    *this += FixedPoint<SIZE, T>(1);

    return res;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>& FixedPoint<SIZE, T>::operator--()
{
    *this -= FixedPoint<SIZE, T>(1);

    return *this;
}

template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T> FixedPoint<SIZE, T>::operator--(int)
{
    FixedPoint<SIZE, T> res(*this);
    *this -= FixedPoint<SIZE, T>(1);

    return res;
}
template <unsigned int SIZE, typename T>
inline FixedPoint<SIZE, T>::operator double()
{
    const double d = isNegative() ? (double(m_dollar)+double(m_cent) / m_number_of_digits) * -1: double(m_dollar) + double(m_cent) / m_number_of_digits;

    return d;
}

int countDigit(int n);

template <unsigned int SIZE, typename T>
inline std::ostream&  operator <<(std::ostream& os ,const FixedPoint<SIZE, T> &p)
{
    if (p.m_sign)
    {
        os << "-";
    }
    os << p.m_dollar << '.';
    if(p.getCent() == 0)
    {
        for (unsigned int i = 0; i < SIZE - countDigit(p.getCent()) - 1; i++)
        {
            std::cout << "0";
        }
    }
    else
    {
        for (unsigned int i = 0; i < SIZE - countDigit(p.getCent()); i++)
        {
            std::cout << "0";
        }
    }
    os << p.getCent() << " dollars " << std::endl;

    return os;
}

template <unsigned int SIZE, typename T>
inline std::string FixedPoint<SIZE, T>::asString() const
{
    std::string s;
    std::stringstream out;
    if(m_sign)
    {
        s += "-";
    }
    T dollar = m_dollar;
    short cent = m_cent;
    out << dollar << ".";
    if(m_cent == 0)
    {
        for (unsigned int i = 0; i < SIZE - countDigit(m_cent)-1; i++)
        {
            out << "0";
        }
    }
    else
    {
        for (unsigned int i = 0; i < SIZE - countDigit(m_cent); i++)
        {
            out << "0";
        }
    }
    out << cent;
    s += out.str();

    return s;
}

template <unsigned int SIZE, typename T>
inline size_t FixedPoint<SIZE, T>::getPrecision() const
{
    std::string s = asString();
    for(size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            return i;
        }
    }

    return 0;
}
std::string digitsToWords (size_t number);

template <unsigned int SIZE, typename T>
inline std::string makeMoney(FixedPoint<SIZE, T> price)
{
    std::string dollarstr = digitsToWords(price.getDollar());
    std::string centstr = digitsToWords(price.getCent());
    return price.isNegative()? "minus " + dollarstr + " dollars and " + centstr + " cents" : dollarstr + " dollars and " + centstr + " cents";
}

#endif //FIXED_POINT_PRICE_H
