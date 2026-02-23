#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "lists.h"

/*****************************************
Make the framework for doubly linked lists 
*****************************************/

#define LL_TYPE int8_t
#define LL_TAG  i8
#define LL_FMT  "%3d"
#include "lists_template.h"

#define LL_TYPE uint8_t
#define LL_TAG  ui8
#define LL_FMT  "%3d"
#include "lists_template.h"

#define LL_TYPE int16_t
#define LL_TAG  i16
#define LL_FMT  "%5d"
#include "lists_template.h"

#define LL_TYPE uint16_t
#define LL_TAG  ui16
#define LL_FMT  "%5u"
#include "lists_template.h"

#define LL_TYPE int32_t
#define LL_TAG  i32
#define LL_FMT  "%10d"
#include "lists_template.h"

#define LL_TYPE uint32_t
#define LL_TAG  ui32
#define LL_FMT  "%10u"
#include "lists_template.h"

#define LL_TYPE int64_t
#define LL_TAG  i64
#define LL_FMT  "%20lld"
#include "lists_template.h"

#define LL_TYPE uint64_t
#define LL_TAG  ui64
#define LL_FMT  "%20llu"
#include "lists_template.h"

#define LL_TYPE float
#define LL_TAG  f32
#define LL_FMT  "%.4g"
#include "lists_template.h"

#define LL_TYPE double
#define LL_TAG  f64
#define LL_FMT  "%.8g"
#include "lists_template.h"
