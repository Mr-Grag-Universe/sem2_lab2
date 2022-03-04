#include "template.h"
#include "func_template.h"

#ifdef TYPE
#undef TYPE
#endif
#define TYPE float
#include "func_template.c"

#ifdef TYPE
#undef TYPE
#endif
#define TYPE double
#include "func_template.c"

#ifdef TYPE
#undef TYPE
#endif
#define TYPE int
#include "func_template.c"

#ifdef TYPE
#undef TYPE
#endif
#include "stdlib.h"
#define TYPE size_t
#include "func_template.c"