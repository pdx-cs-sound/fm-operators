/*
 * C code for FM operators. Transcribed and reformatted by Bart Massey from
 *
 *     Understanding FM Implementations: A Call for Common Standards
 *     Author(s): Frode Holm
 *     Source: Computer Music Journal, Vol. 16, No. 1 (Spring, 1992), pp. 34-42
 *     Published by: The MIT Press
 *     Stable URL: https://www.jstor.org/stable/3680493
 *     Accessed: 2020-05-24 11:31 UTC
 *     
 * This code appears to borrow from F. Richard Moore's
 * `cmusic` library, as described in his book Elements of
 * Computer Music.
 *
 *     Elements of Computer Music
 *     F. Richard Moore
 *     Pearson, 1990
 *     ISBN 0132525526
 *
 * This library was distributed as part of the UCSD Computer
 * Audio Research Laboratory CARL software distribution.
 *
 *     http://yadegari.org/carl.html
 *     Accessed: 2020-05-24 23:01 UTC
 *
 */

#include <math.h>

/* Wave table length. */
#define TABLEN 48000

typedef struct GenFITL {
    /* Pointer to wave table */
    double *Table;
    /* Table length */
    int L;
    /* Accumulating frequency adder */
    double FreqAdd;
    /* Temporary */
    int Look;
} GenFITL;

/* Initializer. */
void Init(GenFITL * G, double Tab[], int TabLen) {
    G->Table = Tab;
    G->L = TabLen;
    G->FreqAdd = 0;
}

/* Generalized modulus operation. */
/* XXX Original comment: "See (Moore 1990) for details."
 * After reviewing that text and Moore's `cmusic` software
 * I see no such function. The code supplied here is what
 * I believe was intended based on Moore's `osc()` function.
 * --Bart 05/2020
 */
double genmod(double a, int b) {
    while (a > b) {
        a -= b;
    }
    return a;
}

/* Start again at beginning of wave table. */
void Reset(GenFITL * G) {
    G->FreqAdd = 0;
}

/* Osc is the "one-tick" lookup oscillator returning one sample. */
double Osc(GenFITL * G, double Amp, double FreqInc, double Phase) {
    /* Truncate lookup index. */
    G->Look = genmod(G->FreqAdd + Phase, G->L);
    /* Increment FreqAdd. */
    G->FreqAdd = genmod(G->FreqAdd + FreqInc, G->L);
    /* Return sample. */
    return Amp * G->Table[G->Look];
}

/* Carrier and modulating frequencies. */
double Fc, Fm;
/* Modulation index in radians. */
double Index;
/* Index in table-length L. */
double LIndex;
/* Carrier and modulator. */
GenFITL Car, Mod, CosMod;

/* Sine table. */
double Sine[TABLEN];
/* Cosine table. */
double Cosine[TABLEN];

/* Modulator phase in radians. */
double ModPhase;
/* M.P. in table-length. */
double LModPhase;

/* Initialize globals. Original defaults were
   fc0=1, fm0=2, index0=M_PI, modphase0=3*M_PI/2. */
void setup(double fc0, double fm0, double index0, double modphase0) {
    /* Initialize scalar globals. */
    Fc = fc0;
    Fm = fm0;
    Index = index0;
    LIndex = (index0 * TABLEN) / (2 * M_PI);
    ModPhase = modphase0;
    LModPhase = (ModPhase * TABLEN) / (2 * M_PI);

    /* Initialize wave tables. */
    for (int i = 0; i < TABLEN; i++) {
	Sine[i] = sin(2 * M_PI * i / TABLEN);
	Cosine[i] = cos(2 * M_PI * i / TABLEN);
    }

    /* Initialize carrier. */
    Init(&Car, Sine, TABLEN);
    /* Initialize sine modulator. */
    Init(&Mod, Sine, TABLEN);
    /* Initialize cosine modulator. */
    Init(&CosMod, Cosine, TABLEN);
}

/* ALGORITHM 1: Standard FM-function: eq. (16). */
void fm_std(int Duration, double y[]) {
    for (int n = 0; n < Duration; n++)
	y[n] = Osc(&Car, 1, Fc, Osc(&Mod, LIndex, Fm, 0));
}

/* ALGORITHM 2: Original FM-function: eq. (11). */
void fm_orig(int Duration, double y[]) {
    Reset(&Car);
    Reset(&Mod);
    for (int n = 0; n < Duration; n++)
	y[n] = Osc(&Car, 1, Fc + Osc(&Mod, Index * Fm, Fm, 0), 0);
}

/* ALGORITHM 3: Limit of original FM-function: eq. (12). */
void fm_orig_limit(int Duration, double y[]) {
    Reset(&Car);
    Reset(&Mod);
    for (int n = 0; n < Duration; n++)
	y[n] = Osc(&Car, 1, Fc, Osc(&Mod, LIndex, Fm, LModPhase) + LIndex);
}

/* ALGORITHM 4: Approximated standard FM-function: eq. (14). */
void fm_approx_std(int Duration, double y[]) {
    Reset(&Car);
    for (int n = 0; n < Duration; n++)
	y[n] = Osc(&Car, 1, Fc + Osc(&CosMod, Index * Fm, Fm, 0), 0);
}
