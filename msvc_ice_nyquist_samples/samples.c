/* samples.c -- various functions for the Nyquist sound data type */

#include "xlisp.h"
#include "sound.h"
#include "samples.h"

/* snd_maxsamp -- compute the maximum value of samples in s */
/**/
double snd_maxsamp(sound_type s)
{
    sample_type result = 0.0F;
    long blocklen;
    s = sound_copy(s);

    while (true) {
        sample_block_type sampblock = sound_get_next(s, &blocklen);
        long i;
        sample_block_values_type sbufp = sampblock->samples;
        if (sampblock == zero_block || blocklen == 0) {
            break;
        }
        for (i = 0; i < blocklen; i++) {
            register sample_type samp = *sbufp++;
            if (result < samp) result = samp;
            else if (result < -samp) result = -samp;
        }
    }
    return (double) (s->scale * result);
}

