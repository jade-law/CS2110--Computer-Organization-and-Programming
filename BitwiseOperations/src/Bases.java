/**
 * CS 2110 Spring 2020 HW1
 * Part 2 - Coding with bases
 *
 * @author JADE LAW
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt
 * - You may declare exactly one String variable each in intToOctalString and
 *   and BinaryStringToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int number = 0;
        int pow = 0;
        for (int i = 0; i < binary.length(); i++) {
            int j = binary.length() - i - 1;
            if (binary.charAt(j) == 49) {
                number += (1 << pow);
            }
            pow++;
        }
        return number;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     *
     * You may use multiplication, division, and modulus in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
        int number = 0;
        int base = 1;
        for (int i = 0; i < decimal.length(); i++) {
            int c = decimal.charAt(decimal.length() - i - 1);
            number += (c - 48) * base;
            base *= 10;
        }
        return number;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex)
    {
        int number = 0;
        int base = 0;
        for (int i = 0; i < hex.length(); i++) {
            int j = hex.length() - i - 1;
            if (hex.charAt(j) > 59) {
                number += ((hex.charAt(j) - 55) << base);
            } else {
                number += ((hex.charAt(j) - 48) << base);
            }
            base += 4;
        }
        return number;
    }

    /**
     * Convert a int into a String containing ASCII characters (in octal).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToOctalString(10); // => "12"
     *
     * You may declare one String variable in this method.
     */
    public static String intToOctalString(int octal)
    {
        int o = octal;
        if (o == 0) {
            return "0";
        }
        String str = "";
        while (o != 0) {
            int oct = o & 0b111;
            str = ((char) (oct + 48)) + str;
            o = o >> 3;
        }
        return str;
    }

    /**
     * Convert a String containing ASCII characters representing a number in binary into 
     * a String containing ASCII characters that represent that same value in hexadecimal.
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The length of all the binary strings passed in will be of size 32.
     * The hex String returned should contain 8 characters. 
     *
     * Example: binaryStringToHexString("00000010111110100001101100111000"); // => 02FA1B38
     *
     * You may declare one String variable in this method.
     */
    public static String binaryStringToHexString(String binary)
    {
        String str = "";
        int bin = 0;
        for (int i = 31; i >= 0; i--) {
            if (binary.charAt(i) == 49) {
                bin = bin | (1 << (31 - i));
            }
        }
        int count = 8;
        while (count != 0) {
            int b = bin & 0xF;
            if (b + 48 > 57) {
                str = ((char) (b + 55)) + str;
            } else {
                str = ((char) (b + 48)) + str;
            }
            bin = bin >> 4;
            count--;
        }
        return str;
    }
}
