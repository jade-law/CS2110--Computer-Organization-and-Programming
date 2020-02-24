/**
 * CS 2110 Spring 2020 HW1
 * Part 3 - Coding with bitwise operators
 *
 * @author JADE LAW
 *
 * Global rules for this file:
 * - All of these functions must be completed in ONE line. That means they should be
 *   of the form "return [...];", with a single semicolon. No partial credit will be
 *   awarded for any Method that isn't completed in one line.
 *
 * - You may not use conditionals.
 * - You may not declare any variables.
 * - You may not use casting.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - You may not use addition or subtraction
 * - You may not use multiplication, division or modulus
 * 
 * - Basically, the global rules are you can only use logical (&&, ||) and bitwise (&, |, ^, >>, <<) operators.
 *   all in one line.
 *
 * Method-specific rules for this file:
 * - You may not use bit shifting or the exclusive OR operator (^) in xor.
 *
 * Some notes:
 * 
 * All of these functions accept ints as parameters because if you pass in a number
 * (which is of type int by default) into a Method accepting a byte, then the Java
 * compiler will complain even if the number would fit into that type.
 *
 * Now, keep in mind the return value is also an int. Please read the comments about how
 * many significant bits to return and make sure that the other bits are not set or else
 * you will not get any points for that test case.
 * i.e if we ask you to return 6 bits and you return 0xFFFFFFFF, you will lose points.
 *
 * Definitions of types:
 * nibble - 4 bits
 * byte   - 8 bits
 * short  - 16 bits
 * int    - 32 bits
 */
public class Operations
{
    /**
     * Get an specified 4-bit nibble from an int.
     *
     * Ints are made of 8 nibbles, numbered like so:
     *   | N7 | N6 | N5 | N4 | N3 | N2 | N1 | N0 |
     *
     * For a graphical representation of the bits:
     *
     * bit 31                                bit 0
     *    v                                     v
     *    1101 1000 0000 1100 0001 1111 1101 1001
     *   +-------------------+-------------------+
     *   | N7 | N6 | N5 | N4 | N3 | N2 | N1 | N0 |
     *
     * Examples:
     *     getNibble(0x56781234, 0); // => 0x4
     *     getNibble(0x56781234, 2); // => 0x2
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int to get a nibble from.
     * @param which Determines which nibble gets returned - 0 for
     *              least-significant nibble.
     *
     * @return A nibble corresponding to the "which" parameter from num.
     */
    int getNibble(int num, int which)
    {
        return (num >> (which << 2) & 0xF);
    }

    /**
     * Set a specified 8-bit byte in an int with a provided 8-bit value.
     *
     * Ints are made of 4 bytes, numbered like so:
     *   |   B4   |   B2   |   B1   |   B0   |
     *
     * For a graphical representation of the bits:
     *
     * bit 31                             bit 0
     *    v                                 v
     *    11011000 00001100 00011111 11011001
     *   +--------+--------+--------+--------+
     *   |   B3   |   B2   |   B1   |   B0   |
     *
     * Examples:
     *     setByte(0xAAA5BBC6, 0x25, 0); // =>  0xAAA5BB25
     *     setByte(0x56B218F9, 0x80, 3); // =>  0x80B218F9
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int that will be modified.
     * @param a_short The byte to insert into the integer.
     * @param which Selects which byte to modify - 0 for least-significant
     * byte.
     *
     * @return The modified int.
     */
    int setByte(int num, int a_short, int which)
    {
        return (a_short << (which <<3)) | (num & ~(0xFF << (which << 3)));
    }

    /**
     * Pack 4 bytes into an int.
     *
     * The 4 bytes should be placed consecutively in the 32-bit int in the order
     * that they appear in the parameters
     *
     * Example:
     *     pack(0x4B, 0x57, 0xA1, 0x22); // => 0x4B57A122
     *     pack(0xDE, 0xAD, 0xBE, 0xEF); // => 0xDEADBEEF
     *
     * @param b3 Most significant byte (will always be a 8-bit number).
     * @param b2 2nd Most Significant byte (will always be a 8-bit number).
     * @param b1 3rd Most significant byte (will always be a 8-bit number).
     * @param b0 Least significant byte (will always be a 8-bit number).
     *
     * @return a 32-bit value formatted like so: b2b1s0
     */
    int pack(int b3, int b2, int b1, int b0)
    {
        return (b3 << 24 | b2 << 16 | b1 << 8 | b0);
    }

    /**
     * Extract a range of bits from a number.
     *
     * Examples:
     *     bitRange(0x00001234, 0, 4);  // => 0x00000004
     *     bitRange(0x00001234, 4, 8);  // => 0x00000023
     *     bitRange(0x12345678, 0, 28); // => 0x02345678
     *     bitRange(0x55555555, 5, 7);  // => 0x0000002A
     *
     * Note: We will only pass in values 1 to 32 for n.
     *
     * @param num An n-bit 2's complement number.
     * @param s The starting bit to grab
     * @param n The number of bits to return.
     * @return The n-bit number num[s:s+n-1].
     */
    int bitRange(int num, int s, int n)
    {
        return ((num >> s) & ~(~0 << n));
    }

    /**
     * NOTE: For this method, you may only use &, |, and ~.
     *
     * Perform an exclusive-nor on two 32-bit ints.
     *
     * Examples:
     *     xnor(0xFF00FF00, 0x00FF00FF); // => 0x00000000
     *     xnor(0x12345678, 0x87654321); // => 0x6AAEEAA6
     *
     * @param num1 An int
     * @param num2 Another int
     *
     * @return num1 XNOR num2
     */
    int xnor(int num1, int num2)
    {
        return ~((num1 & ~ num2) | (num2 & ~ num1));
    }

    /**
     * Return true if the given number is multiple of 4.
     *
     * Examples:
     *     multipleOf4(32); // => true
     *     multipleOf4(13);   // => false
     *
     * Note: Make sure you handle ALL the cases!
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 4 else false.
     */

    boolean multipleOf4(int num)
    {
        return (num != 0) && (num == (num & ~0x3));
    }

    /**
     * Return true if the given number is multiple of 128.
     *
     * Examples:
     *     multipleOf128(256); // => true
     *     multipleOf128(135); // => false
     *
     * Note: Make sure you handle ALL the cases!
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 128 else false.
     */

    boolean multipleOf128(int num)
    {
        return (num != 0) && (num == (num & ~0x7F));
    }
}
