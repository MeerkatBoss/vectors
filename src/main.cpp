#include <cstdio>
#include <unistd.h>

#include "vectors/vectors.h"

int main()
{
  Vec    a = VEC_EMPTY, b = VEC_EMPTY;
  double scale = 1.33;
  VecCtor(&a, 1, 2);
  VecCtor(&b, 4, 5);

  Vec    sum    = VecAdd(&a, &b);
  Vec    diff   = VecSub(&a, &b);
  Vec    scaled = VecScale(&a, scale);
  double angle  = VecAngle(&a, &b);

  dprintf(STDOUT_FILENO, "a = ");
  VecDump(&a, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "b = ");
  VecDump(&b, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a + b = ");
  VecDump(&sum, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a - b = ");
  VecDump(&diff, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "%lg * a = ", scale);
  VecDump(&scaled, STDOUT_FILENO);
  dprintf(STDOUT_FILENO, "a^b = %lg\n", angle);

  VecDtor(&a);
  VecDtor(&b);
  VecDtor(&sum);
  VecDtor(&diff);
  VecDtor(&scaled);
}
