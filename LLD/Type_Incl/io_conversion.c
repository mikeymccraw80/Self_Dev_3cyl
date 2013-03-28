
#include "reuse.h"
#include "io_conversion.h"

const uint32_t POWER_OF_10[] =
   { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

//=============================================================================
// mult_div64
//=============================================================================
uint32_t mult_div64(
   uint32_t a,
   uint32_t b,
   uint32_t c )
{
   uint32_t result;
   unsigned long long a2 = a;
   unsigned long long b2 = b;
   unsigned long long e2;
   if (c == 0)
   {
       result = UINT32_MAX;
   }
   else
   {
       e2 = a2 * b2;
       result = (uint32_t)( e2 / c );
   }
   return result;
}

//=============================================================================
// mult_div64_shift
//=============================================================================
uint32_t mult_div64_shift(
   uint32_t a,
   uint32_t b,
   uint32_t c,
   uint32_t d )
{
   uint32_t result;
   unsigned long long a2 = a;
   unsigned long long b2 = b;
   unsigned long long e2;
   if (c == 0)
   {
       result = UINT32_MAX;
   }
   else
   {
       e2 = a2 * b2;
       result = (uint32_t)( ( e2 / c ) >> d  );
   }
   return result;
}

//=============================================================================
// mult_shift_div64
//=============================================================================
uint32_t mult_shift_div64(
   uint32_t a,
   uint32_t b,
   uint32_t c,
   uint32_t d )
{
   uint32_t result;
   unsigned long long a2 = a;
   unsigned long long b2 = b;
   unsigned long long e2;
   if (c == 0)
   {
       result = UINT32_MAX;
   }
   else
   {
       e2 = a2 * b2;
       e2 = e2 << d;
       result = (uint32_t)( e2 / c );
   }
   return result;
}

//=============================================================================
// umult64_shift
//=============================================================================
int32_t mult64_shift(
   int32_t  a,
   uint32_t b,
   uint32_t c )
{
   int32_t result;
   signed long long a2 = a;
   unsigned long long b2 = b;
   unsigned long long e2;

   e2 = a2 * b2;
   e2 = e2 >> c;
   result = (uint32_t)e2;

   return result;
}

//=============================================================================
// umult64_shift
//=============================================================================
uint32_t umult64_shift(
   uint32_t a,
   uint32_t b,
   uint32_t c )
{
   uint32_t result;
   unsigned long long a2 = a;
   unsigned long long b2 = b;
   unsigned long long e2;

   e2 = a2 * b2;
   e2 = e2 >> c;
   result = (uint32_t)e2;

   return result;
}
