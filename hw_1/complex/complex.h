#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complexes together
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add ( Complex a, Complex b );

/*! Multiply two complexes together (does not reduce)
 *  \param a The first term
 *  \param b The second term
 */
Complex mutiply ( Complex a, Complex b );

/*! Magnitude two complexes
 *  \param a The first summand
 *  \param b The second summand
 */
double magnitude ( Complex a, Complex b );

/*! Negate two complexes together
 *  \param a The first term
 *  \param b The second term
 */
Complex negate ( Complex a, Complex b );

#endif