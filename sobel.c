#include <stdio.h> /* Sobel.c */
#include <math.h>

int pic[256][256];
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int masky[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};
double ival[256][256], maxival;

main(argc, argv) 
int argc;
char **argv;
{
  int i, j, p, q, mr, sum1, sum2;
  double hi_threshold, low_threshold;
  char throwaway[80];
  FILE *fo1, *fo2, *fo3, *fp1, *fopen();
  char *foobar;

  argc--;
  argv++;
  foobar = *argv;
  fp1 = fopen(foobar, "rb");

  fgets(throwaway, 80, fp1);
  fgets(throwaway, 80, fp1);
  fgets(throwaway, 80, fp1);
  if (!((throwaway[0] == '2') && (throwaway[1] == '5') && (throwaway[2] == '5')))
    fgets(throwaway, 80, fp1);

  argc--;
  argv++;
  foobar = *argv;
  fo1 = fopen(foobar, "wb");

  fprintf(fo1, "P5\n");
  fprintf(fo1, "%d %d\n", 256, 256);
  fprintf(fo1, "255\n");

  argc--;
  argv++;
  foobar = *argv;
  fo2 = fopen(foobar, "wb");

  fprintf(fo2, "P5\n");
  fprintf(fo2, "%d %d\n", 256, 256);
  fprintf(fo2, "255\n");

  argc--;
  argv++;
  foobar = *argv;
  fo3 = fopen(foobar, "wb");

  fprintf(fo3, "P5\n");
  fprintf(fo3, "%d %d\n", 256, 256);
  fprintf(fo3, "255\n");

  argc--;
  argv++;
  foobar = *argv;
  hi_threshold = atoi(foobar);

  argc--;
  argv++;
  foobar = *argv;
  low_threshold = atoi(foobar);

  for (i = 0; i < 256; i++)
  {
    for (j = 0; j < 256; j++)
    {
      pic[i][j] = getc(fp1);
      pic[i][j] &= 0377;
    }
  }

  mr = 1;
  for (i = mr; i < 256 - mr; i++)
  {
    for (j = mr; j < 256 - mr; j++)
    {
      sum1 = 0;
      sum2 = 0;
      for (p = -mr; p <= mr; p++)
      {
        for (q = -mr; q <= mr; q++)
        {
          sum1 += pic[i + p][j + q] * maskx[p + mr][q + mr];
          sum2 += pic[i + p][j + q] * masky[p + mr][q + mr];
        }
      }
      outpicx[i][j] = sum1;
      outpicy[i][j] = sum2;
    }
  }

  maxival = 0;
  for (i = mr; i < 256 - mr; i++)
  {
    for (j = mr; j < 256 - mr; j++)
    {
      ival[i][j] = sqrt((double)((outpicx[i][j] * outpicx[i][j]) +
                                 (outpicy[i][j] * outpicy[i][j])));
      if (ival[i][j] > maxival)
        maxival = ival[i][j];
    }
  }

  for (i = 0; i < 256; i++)
  {
    for (j = 0; j < 256; j++)
    {
      ival[i][j] = (ival[i][j] / maxival) * 255;
      fprintf(fo1, "%c", (char)((int)(ival[i][j])));
    }
  }

  for (i = 0; i < 256; i++)
  {
    for (j = 0; j < 256; j++)
    {
      ival[i][j] = (ival[i][j] / maxival) * 255;
      if ((char)ival[i][j] > low_threshold)
        fprintf(fo2, "%c", (char)255);
      else
        fprintf(fo2, "%c", (char)0);
      if ((char)ival[i][j] > hi_threshold)
        fprintf(fo3, "%c", (char)255);
      else
        fprintf(fo3, "%c", (char)0);
    }
  }
}