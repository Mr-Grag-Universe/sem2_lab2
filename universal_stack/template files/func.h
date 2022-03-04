#ifndef ALL_POSSIBLE_SUMS_H_
#define ALL_POSSIBLE_SUMS_H_
#include "template.h"

#ifdef TYPE
#undef TYPE
#endif
#define TYPE float
#include "func_template.h"

#ifdef TYPE
#undef TYPE
#endif
#define TYPE double
#include "func_template.h"

#ifdef TYPE
#undef TYPE
#endif
#define TYPE int
#include "func_template.h"

#endif