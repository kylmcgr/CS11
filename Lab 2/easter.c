#include <stdio.h>
/*
 * easter.c: calculates the date of easter for the given years
 * usage: ./easter < $(INFILE) > $(OUTFILE)
 * infile: A list of years between 1582 - 39999
 * outfile: A list of the dates of easter for those years
 */

int calculate_Easter_date(int year);

int main(int argc, char const *argv[]) {
  int year, easter_date;

  /* While true loop to go through all years in input file. */
  while (1) {
    /* Breaks while loop if scan reaches end of file. */
    if (scanf("%d\n", &year) == EOF) {
      break;
    }
    /*
     * Calculates the date of easter, a negative date means March
     * and a positive date means April.
     */
    easter_date = calculate_Easter_date(year);
    /*
     * Prints an error message if the function returns 0.
     * Prints the year, month, and date if the fucntion returned a date.
     */
    if (easter_date == 0) {
      fprintf(stderr, "%d is outside the allowed years: 1582 - 39999\n", year);
    } else if (easter_date < 0) {
      printf("%d - March %d\n", year, -easter_date);
    } else {
      printf("%d - April %d\n", year, easter_date);
    }
  }
  return 0;
}

/*
 * calculate_Easter_date: calculates the date of easter
 * arguments: year: the year who's easter date will be calculated
 * return value: the date of eater, the month is represented by the
 * sign of the date: negative for Marcha or positive for April
 */
int calculate_Easter_date(int year) {
  int golden_year, century, leap_years, moon_correction;
  int sunday, epact, full_moon, easter;

  /* Returns 0 if year is outside of acceptable range. */
  if (year < 1582 || year >= 40000) {
    return 0;
  }
  /* Calculates the golden year for the year. */
  golden_year = (year % 19) + 1;
  /* Calculates the century for the year. */
  century = (year / 100) + 1;
  /* Calculates the skipped leap years for the year. */
  leap_years = (3 * century / 4) - 12;
  /* Calculates the correction due to the moon for the year. */
  moon_correction = ((8 * century + 5) / 25) - 5;
  /* Calculates a Sunday for the year. */
  sunday = (5 * year / 4) - leap_years - 10;
  /* Calculates the epact for the year. */
  epact = (11 * golden_year + 20 + moon_correction - leap_years) % 30;
  /* Correction for the epact. */
  if ((epact == 25 && golden_year > 11) || epact == 24) {
    epact++;
  }
  /* Calculates the date of the full moon. */
  full_moon = 44 - epact;
  /* Correction for the full moon date. */
  if (full_moon < 21) {
    full_moon += 30;
  }
  /* Calculates the date of easter. */
  easter = full_moon + 7 - ((sunday + full_moon) % 7);
  /* If the date is larger than 31 returns the appropriate April date */
  if (easter > 31) {
    return (easter - 31);
  }
  /* Returns the date with a negative sign for March */
  return -easter;
}
