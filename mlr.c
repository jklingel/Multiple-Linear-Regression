/* multLinearRegression     */
/* Jan Klingel, 06/2026     */
/* Code version for POWER C */
/* and MOS 6502/6510 CPU    */

#include <stdio.h>
#include <math.h>

#define MAXVAL 50 /* Maxium of 50 x and 50 y values */

/* Structure for trainings data */
struct trainingsData {
  float price[MAXVAL];  /* y */
  float square[MAXVAL]; /* x1 */
  float age[MAXVAL];    /* x2 */
};

/* getCorrelation()
   Function to calculate Pearson's 
   correlation coefficient
*/
float getCorrelation(x,y,n)
float x[];
float y[];
int n;
{
  float sum_X = 0, sum_Y = 0, sum_XY = 0;
  float sum_X2 = 0, sum_Y2 = 0;
  int i;
  for (i = 0;i < n;i++) {
    sum_X += x[i];
    sum_Y += y[i];
    sum_XY += x[i] * y[i];
    sum_X2 += x[i] * x[i];
    sum_Y2 += y[i] * y[i];
  }

  /* Numerator calculation (above the 
    fraction bar) */
  float numerator = (n * sum_XY) - (sum_X * sum_Y);

  /* Denominator calculation (below 
    the fraction bar) */
  float denominator = sqrt((n * sum_X2 - (sum_X * sum_X)) * (n * sum_Y2 - (sum_Y * sum_Y)));

  /* Handle edge case where denominator
    is zero (to avoid division by 
     zero error) */
  if (denominator == 0.0)
    return 0.0;

  return(numerator / denominator); 
  /* equals r */
}

int main(void) {
  unsigned int n, i;
  float pprice; /* predicted price = output */
  unsigned int psquare; /* square footage of given house = input 1 */
  unsigned int page; /* age of given house = input 2 */

  /* Reserve memory for the trainings 
    data struct and initialize */
  struct trainingsData td;

  td.price[0] = 280000.0; /* y */
  td.price[1] = 277000.0;
  td.price[2] = 130000.0;
  td.price[3] = 180000.0;
  td.price[4] = 211000.0;
  td.price[5] = 329000.0;
  td.price[6] = 317000.0;
  td.price[7] = 360000.0;
  td.price[8] = 204000.0;
  td.price[9] = 250000.0;
  td.price[10] = '\0';

  td.square[0] = 1852.0; /* x1 */
  td.square[1] = 1975.0;
  td.square[2] = 1176.0;
  td.square[3] = 1550.0;
  td.square[4] = 1458.0;
  td.square[5] = 2689.0;
  td.square[6] = 2259.0;
  td.square[7] = 2763.0;
  td.square[8] = 1325.0;
  td.square[9] = 1992.0;
  td.square[10] = '\0';

  td.age[0] = 2; /* x2 */
  td.age[1] = 5;
  td.age[2] = 10;
  td.age[3] = 6;
  td.age[4] = 7;
  td.age[5] = 3;
  td.age[6] = 4;
  td.age[7] = 3;
  td.age[8] = 5;
  td.age[9] = 6;
  td.age[10] = '\0';

  /* Calculate number of elements in price[]; */
  n = 0;
  while(td.price[n] != '\0')
    n++;
  printf("Number of elements n: %u\n", n);

  /* Calculate means */
  float x1bar,x2bar,ybar;
  x1bar = 0.0;
  x2bar = 0.0;
  ybar = 0.0;  
  for(i=0;i<n;i++) {
    x1bar += td.square[i];
    x2bar += td.age[i];
    ybar  += td.price[i];
  }
  x1bar /= n;
  x2bar /= n;
  ybar /= n;
  printf("x1bar: %.1f\n", x1bar);
  printf("x2bar: %.1f\n", x2bar);
  printf("ybar: %.1f\n", ybar);

  /* Calculate x1x1 */
  float x1x1;
  x1x1 = 0.0;
  for(i=0;i<n;i++)
    x1x1 += td.square[i] * td.square[i];
  printf("x1x1: %.0f\n", x1x1);

  /* Calculate x2x2 */
  float x2x2;
  x2x2 = 0.0;
  for(i=0;i<n;i++)
    x2x2 += td.age[i] * td.age[i];
  printf("x2x2: %.0f\n", x2x2);

  /* Calculate x1y */
  float x1y;
  x1y = 0.0;
  for(i=0;i<n;i++)
    x1y += td.square[i] * td.price[i];
  printf("x1y: %f\n", x1y);

  /* Calculate x2y */
  float x2y;
  x2y = 0.0;
  for(i=0;i<n;i++)
    x2y += td.age[i] * td.price[i];
  printf("x2y: %.0f\n", x2y);

  /* Calculate x1x2 */
  float x1x2;
  x1x2 = 0.0;
  for(i=0;i<n;i++)
    x1x2 += td.square[i] * td.age[i];
  printf("x1x2: %.0f\n", x1x2);

  /* Calculate correlation r between x1 and y */
  float r1;
  r1 = getCorrelation(td.square,td.price,n);
  printf("r1: %f\n", r1);

  /* Calculate correlation r between x2 and y */
  float r2;
  r2 = getCorrelation(td.age,td.price,n);
  printf("r2: %f\n", r2);

  /* Calculate coefficient b0, b1, and b2 */
  float b0, b1, b2 = 0.0;
  b1 = ((x2x2*x1y)-(x1x2*x2y)) / ((x1x1*x2x2)-(x1x2*x1x2));
  b2 = ((x1x1*x2y)-(x1x2*x1y)) / ((x1x1*x2x2)-(x1x2*x1x2));
  b0 = ybar - b1*x1bar - b2*x2bar;
  printf("b0: %f\n", b0);
  printf("b1: %f\n", b1);
  printf("b2: %f\n", b2);

  printf("Enter the square footage of the house: ");
  scanf("%d", &psquare);
  printf("Enter the age of the house in years: ");
  scanf("%d", &page);
  pprice = b0 + b1*psquare + b2*page;
  printf("The estimated house price is: %.0f\n", pprice);
  return(0);
}
