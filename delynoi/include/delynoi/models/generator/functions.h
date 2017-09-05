#ifndef DELYNOI_FUNCTIONS_H
#define DELYNOI_FUNCTIONS_H

#include "Functor.h"

namespace functions {
    enum independent_variable{x, y, both};

    Functor* constant();
    Functor* constantAlternating();
    Functor* uniform(double delta);
    Functor* random_integer(double min, double max);
    Functor* random_double(double min, double max);
    Functor* sine(double amplitude, double frecuency, double phase);
    Functor* cosine(double amplitude, double frecuency, double phase);
}

#endif
