/*
 * C code for FM operators. Transcribed and reformatted by Bart Massey from
 *
 *     Understanding FM Implementations: A Call for Common Standards
 *     Author(s): Frode Holm
 *     Source: Computer Music Journal, Vol. 16, No. 1 (Spring, 1992), pp. 34-42
 *     Published by: The MIT Press
 *     Stable URL: https://www.jstor.org/stable/3680493
 *     Accessed: 24-05-2020 11:31 UTC
 *     
 */

struct GenFitl {
    double *Table; /* Pointer to wave table */
    int L; /* Table length */
    double FreqAdd; /* Accumulating frequency adder */
    int Look; /* Temporary */
}

Init(GenFITL *G, double Tab[], int TabLen) /* Initializer */
{ G->Table = Tab; G->L = TabLen;   
    G->FreqAdd = 0;}

double genmod(double a, int b); /*Generalized modulus operation. */
/* See (Moore 1990) for details */

void Reset(GenFITL *G) {G->FreqAdd = 0;}

/* Osc is the "one-tick" lookup oscillator returning one sample */
double Osc(GenFITL *G, double Amp,
double FreqInc, double Phase) {
/* Truncate lookup index */
G->Look = genmod(G->FreqAdd+Phase, G-L);
/* Increment FreqAdd */
G->FreqAdd = genmod(G-FreqAd +FreqInc,
G->L);
/* Return sample */
return Amp*G->TableG->Look;
}

double Fc=1,Fm=2; /* Carrier and modulating frequencies */
double Index=PI; /* Modulation index in radians */
double LIndex = (Index*TABLEN)
(2*PI); /* Index in table-length L */
GenFITL Car, Mod, CosMod;
 /* Instantiate carrier and modulator */
 Init(&Car,Sine,TABLEN); /* Initialize carrier */
 Init(&Mod,Sine,TABLEN); /* Initialize sine modulator */
 Init(&CosMod,Cosine,TABLEN); /* Initialize cosine modulator */

 /* ALGORITHM 1: Standard FM-function: eq. (16). */
 for (n=O; n<Duration; n++)
 y[n] = Osc(&Car, 1, Fc, Osc(&Mod,
 LIndex, Fm, 0));

 /* ALGORITHM 2: Original FM-function: eq. (11). */
 Reset(&Car); Reset(&Mod);
 for (n=0; n<Duration; n++)
 y[n] = Osc(&Car, 1, Fc + Osc(&Mod,
 Index*Fm, Fm, 0),O);

 /* ALGORITHM 3: Limit of original FM-function: eq. (12). */
 double ModPhase = (3*PI)/2;
 /* Modulator phase in radians */
 double LModPhase = (ModPhase*TABLEN)/(2*PI); /* M.P. in table-length */
Reset(&Car); Reset(&Mod);
for (n=O; n<Duration; n++)
y[n] = Osc(&Car, 1, Fc, Osc(&Mod,
LIndex, Fm, LModPhase) +
 LIndex);

 /* ALGORITHM 4: Approximated standard FM-function: eq. (14). */
 Reset(&Car);
 for (n=O; n<Duration; n++)
 y[n] = Osc(&Car, 1, Fc + Osc(&CosMod,
Index*Fm, Fm, 0), 0);




