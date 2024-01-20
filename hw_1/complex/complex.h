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
Complex multiply ( Complex a, Complex b );

/*! Return the Magnitude of the complex
 *  \param a The first summand
 */
double magnitude ( Complex a);

/*! Negate the complex
 *  \param a The complex
 */
Complex negate ( Complex a);

#endif