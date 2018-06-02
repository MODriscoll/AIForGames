#pragma once

// For now...
#include "RanMaths.h"
#include <iostream>

// TO DO:
// Improve layout and naming convention
// Add more functions to hopefully
// help increase performance ( I can use
// more bit concentrated values, like
// in TColour )

// Binary addition
inline unsigned int BitAddition(unsigned int a_d1, unsigned int a_d2)
{
	// Create the carry
	// for the addition
	unsigned int carry = 0;

	// Repeat until all bits
	// have been shifted
	while (a_d2 != 0)
	{
		// Perform a half adder, the sum is
		// the XOR and carry is the AND of
		// the current bit of each number
		carry = a_d1 & a_d2;
		a_d1 = a_d1 ^ a_d2;

		// Shift the current
		// carry by one
		a_d2 = carry << 1;
	}

	// Return the value
	return a_d1;
}

// Binary subtraction
inline unsigned int BitSubtraction(unsigned int a_d1, unsigned a_d2)
{
	// Get the twos compliment of the second number (which 
	// is NOT plus 1 ) and add it to the first number
	return BitAddition(a_d1, BitAddition(~a_d2, 1));
}

// Binary multiplication
inline unsigned int BitMultiply(unsigned int a_d1, unsigned int a_d2)
{
	// Create the int to
	// record the answer
	unsigned int answer = 0;

	// Repeat until all bits
	// have been shifted
	while (a_d2 != 0)
	{
		// Is the current
		// bit positive?
		if (a_d2 & 0b1)
		{
			// Increase the answer
			answer += a_d1;
		}

		// Shift each bit by one
		// in separate direction
		a_d1 <<= 1;
		a_d2 >>= 1;
	}

	// Return the value
	return answer;
}

// Binary division
inline unsigned int BitDivision(unsigned int a_Dividend, unsigned int a_Divisor, unsigned int a_Origdiv, unsigned int& a_Remainder)
{
	// Create the quotient
	int quotient = 1;

	// Is the dividend now 
	// equal to the divisor?
	if (a_Dividend == a_Divisor)
	{
		// Set the remainder to zero
		a_Remainder = 0;

		// Return one
		return 1;
	}
	// Is the dividend now
	// less then the divisor
	else if (a_Dividend < a_Divisor)
	{
		// Set the remainder
		// to the dividend
		a_Remainder = a_Dividend;

		// Return zero
		return 0;
	}

	// Repeat until the divisor
	// is greater than the dividend
	while (a_Divisor <= a_Dividend)
	{
		// Shift the divisor and
		// quotient by 1 to the left
		a_Divisor <<= 1;
		quotient <<= 1;
	}

	// Is the divisor now greater?
	// than the dividend?
	if (a_Dividend < a_Divisor)
	{
		// Shift the divisor and
		// quotient back by one bit
		a_Divisor >>= 1;
		quotient >>= 1;
	}
	
	// Set the quotient to equal
	// itself plus another division
	quotient += BitDivision(a_Dividend - a_Divisor, a_Origdiv, a_Origdiv, a_Remainder);

	// Return the value
	return quotient;
}

// Small unit test
// Will make own header and cpp
// in the Unit tests folder eventually
inline bool UnitTest()
{
	auto rannum = CreateIntGenerator(1, 100);

	unsigned int a = rannum();
	unsigned int b = rannum();

	unsigned int answer = BitAddition(a, b);

	if (answer == (a+b))
	{
		std::cout << "TEST PASSED: bitshift addition "
			<< a << " + " << b << " = " << answer << "\n";
	}
	else
	{
		std::cout << "TEST FAILED: bitshift addition "
			<< a << " + " << b << " = " << answer << ". ( Correct answer is: "
			<< (a + b) << " )" << std::endl;

		return false;
	}

	answer = BitSubtraction(a, b);

	if (answer == (a - b))
	{
		std::cout << "TEST PASSED: bitshift subtraction "
			<< a << " - " << b << " = " << answer << "\n";
	}
	else
	{
		std::cout << "TEST FAILED: bitshift subtraction "
			<< a << " - " << b << " = " << answer << ". ( Correct answer is: "
			<< (a - b) << " )" << std::endl;

		return false;
	}

	answer = BitMultiply(a, b);

	if (answer == (a*b))
	{
		std::cout << "TEST PASSED: bitshift multiplication "
			<< a << " * " << b << " = " << answer << "\n";
	}
	else
	{
		std::cout << "TEST FAILED: bitshift multiplication "
			<< a << " * " << b << " = " << answer << ". ( Correct answer is: "
			<< (a*b) << " )" << std::endl;

		return false;
	}

	unsigned int remainder = 0;	answer = BitDivision(a, b, b, remainder);

	if (answer == (a / b))
	{
		std::cout << "TEST PASSED: bitshift division "
			<< a << " / " << b << " = " << answer <<
			" with remainder " << remainder << std::endl;

		return true;
	}
	else
	{
		std::cout << "TEST FAILED: bitshift division "
			<< a << " / " << b << " = " << answer <<
			" with remainder " << remainder << ". ( Correct answer is: "
			<< (a/b) << " )" << std::endl;

		return false;
	}
}
