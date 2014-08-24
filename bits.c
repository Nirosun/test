/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  int x = 0x55;
  int tmp = 0x55;
  x = x | (tmp<<8) | (tmp <<16) | (tmp<<24);
  return x;
}
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  int res = !(x^y);
  return res;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int mask = 0xff;
  int pos_m = m << 3;
  int pos_n = n << 3;
  int bits_m = mask & (x >> pos_m);
  int bits_n = mask & (x >> pos_n);
  int mask_m_n = (mask << pos_m) | (mask << pos_n);
  int mask_other = ~mask_m_n;
  int swap_m_n = (bits_m << pos_n) | (bits_n << pos_m);
  int res = swap_m_n | (mask_other & x);
  return res;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  int minus_n = ~n + 1;
  int minus_1 = ~(1) + 1;
  int mask = ~((1 << 31) >> (n + minus_1));
  int res = (x << (32 + minus_n)) | ((x >> n) & mask);
  return res;
}
/* 
 * logicalNeg - implement the ! operator using any of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int tmp = (~x & ~(~x+1)) >> 31;
  int res = tmp & 1;
  return res;
}
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  int res = ~(1 << 31);
  return res;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  int sign_shift = x >> 31;
  int bias = ((~x & (~x + 1)) >> 31) & 1;
  int res = sign_shift + bias;
  return res;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int dif = x + (~y + 1);
  int minus_dif = ~dif + 1;
  int tmp = (~x & minus_dif) | (y & minus_dif) | (~x & y);
  int res = (tmp >> 31) & 1;
  //int res = ((~dif & (~dif + 1)) >> 31) & 1;
  return res;
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  int dif = x + (~y + 1);
  int tmp = ~((dif & ~x & y) | (~dif & x & ~y)); 
  int res = (tmp >> 31) & 1;
  return res;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum possible value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  int res = 0;
  int sum = x + y;
  int ok = 0;
  int s = 0;
  int min = 1 << 31;
  int max = ~min;
  
  s = sum;
  ok = (~x & ~s) | (y & s) | (x & ~y);
  ok = ok >> 31;
  s = s >> 31;  
  res = (ok & sum) + ((~ok) & ((s & max) + ((~s) & min)));
  return res;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int res = 0;
  int pos_now = 15;
  //int dif = 0;
  //int sign_dif = 0;
  int is_high_0 = 0;
  int is_bit_0;
  int sign_x = x >> 31;
  //int x_neg = ~x + 1;
  int minus_1 = ~0;
  int x_equal_0 = 0;
  //int x_equal_m1 = 0;
  //int flag = 0;
  int bits_high = 0;
  int x_new = x;
  //int floor = 0;
  
  x_new = (sign_x & ~x) + (~sign_x & x);
  //8
  bits_high = x_new >> (pos_now + 1);
  is_high_0 = ((!bits_high) << 31) >> 31;
  is_bit_0 = ~((x_new << (32 + ~pos_now)) >> 31);
  pos_now = pos_now + (~is_high_0 & 8) + (is_high_0 & is_bit_0 & (~8 + 1));  
  //4
  bits_high = x_new >> (pos_now + 1);
  is_high_0 = ((!bits_high) << 31) >> 31;
  is_bit_0 = ~((x_new << (32 + ~pos_now)) >> 31);
  pos_now = pos_now + (~is_high_0 & 4) + (is_high_0 & is_bit_0 & (~4 + 1));  
  //2
  bits_high = x_new >> (pos_now + 1);
  is_high_0 = ((!bits_high) << 31) >> 31;
  is_bit_0 = ~((x_new << (32 + ~pos_now)) >> 31);
  pos_now = pos_now + (~is_high_0 & 2) + (is_high_0 & is_bit_0 & (~2 + 1));  
  //1
  bits_high = x_new >> (pos_now + 1);
  is_high_0 = ((!bits_high) << 31) >> 31;
  is_bit_0 = ~((x_new << (32 + ~pos_now)) >> 31);
  pos_now = pos_now + (~is_high_0 & 1) + (is_high_0 & is_bit_0 & minus_1);  
  
  x_equal_0 = ((!x_new) << 31) >> 31;
  //x_equal_m1 = ((!(x_new + 1)) << 31) >> 31; 
  //flag = x_equal_0 ^ x_equal_m1; 
  
  res = pos_now + (x_equal_0 & 1) + (~x_equal_0 & 2);
  //res = pos_now + 2;
  return res;
} 
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  int exp = (uf >> 23) & 0xff; 
  int mask_exp = 0xff << 23;
  int mask_frac_ex = ~(0xff << 24);
  int frac_ex = uf & mask_frac_ex; 
  int last_two_bits = uf & 3;
  int tmp = 0;
  int res = 0;
  
  if (exp == 0 || exp == 1)
  {
    tmp = frac_ex >> 1;
    if (last_two_bits == 3)
    {
      tmp = tmp + 1;
    }
    res = (uf & ~mask_frac_ex) | tmp;
  }
  else if (exp == 0xff)
  {
    res = uf;
  }
  else
  { 
    res = (uf & ~mask_exp) | ((exp - 1) << 23); 
  }
  return res;  
} 
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int res = 0;
  int exp = (uf >> 23) & 0xff;
  int e = exp - 127;
  int mask_frac = ~((1 << 31) >> 8);
  int frac_ex = (uf & mask_frac) | (1 << 23); 
  int mask_sign = 1 << 31;
  int sign = uf & mask_sign;
  int shift = 0;
  //int last_two_bits = 0;
  int tmp = 0;
  
  if (e <= -1)
  {
    res = 0; 
  }
  else if (e <= 23)
  {
    shift = 23 - e;
    //last_two_bits = (frac_ex >> (shift - 1)) & 3;
    tmp = frac_ex >> shift;
    /*if (last_two_bits == 3)
    { 
      tmp = tmp + 1;
    }*/
    if (sign == 0)
    {
      res = tmp;
    }
    else
    {
      res = ~tmp + 1;
    }
  }
  else if (e <= 30)
  {
    shift = e - 23;
    tmp = frac_ex << shift;
    if (sign == 0)
    {
      res = tmp;
    }
    else
    {
      res = ~tmp + 1;
    }
  }
  else
  {
    res = mask_sign;
  }
  
  return res;
}
