# FM Synthesis Operators
Bart Massey *et al*

This is C code for "standard" FM operators. I am not the
author, but I have transcribed, reformatted and completed
it. The code is originally from the paper:

> *Understanding FM Implementations: A Call for Common Standards*  
> Frode Holm  
> Computer Music Journal, Vol. 16, No. 1 (Spring, 1992), pp. 34-42  
> The MIT Press  
> https://www.jstor.org/stable/3680493  
> Accessed: 2020-05-24 11:31 UTC

The paper describes various commonly-used wavetable-based FM
Synthesis operators, with an eye to establishing standard
nomenclature and representations so that "patches" from FM
synthesizers can be reliably reproduced cross-platform. It
contains a great exegesis of the topic.

Unfortunately the code as reproduced in the article is
relatively mangled by various formatting issues: this is
unsurprising given the two-column format, the 90s-style
typewriter font, and the fragmentary nature of some of the
source. A transcription, a bunch of reformatting, and a bit
of finishing-up gave me a C source file that is relatively
readable and compiles cleanly into an object file.

I did this work primarily to aid my understanding of FM
operators for an upgrade of my
[`fm.py`](http://github.com/pdx-cs-sound/fm) Python
synthesizer.

The code here appears to be inspired by code from the
excellent book:

> *Elements of Computer Music*  
> F. Richard Moore  
> Pearson, 1990  
> ISBN 0132525526

That book describes (among many other things) the
construction of `cmusic`, a C library for music
synthesis. `cmusic` was eventually distributed by the UCSD
Computer Audio Research Laboratory as part of their
[CARL](http://yadegari.org/carl.html) software distribution.

## No License

I am not the primary author of any of this code. I thus
cannot offer it under an open source license. I believe
(perhaps incorrectly) that the Fair Use provisions of US
Copyright Law allow you to review it for educational
purposes. If any of the authors of this software object to
this repository, please let me know and I will promptly
remove it.

The CARL repository page states that the CARL software,
including `cmusic`, is being made available under GPL
v2.1+. This differs from the distribution itself, which
refers to a license agreement that must be signed. Holm's
code as presented in this library does not (at first glance)
seem to be directly derived from anything in `cmusic`, so it
is probably not implicitly GPL.
