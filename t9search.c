#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ()
{
 int cisloA, cisloB, cisloC;

 printf("zadaj cisloA: ");
 scanf("%d", &cisloA);

 printf("zadaj cisloB: ");
 scanf("%d", &cisloB);

 printf("zadaj cisloC:");
 scanf("%d", &cisloC);

d = cisloB * cisloB - 4 * cisloA * cisloC;
if (d > 0) {
    x = -cisloB - sqrt(d) / (2 * cisloA);
    y = -cisloB - sqrt(d) / (2 * cisloA);

} else {
    x = -cisloB / (2 * cisloA);
}

}
