#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

// Found at https://www.codewars.com/kata/5390bac347d09b7da40006f6
// This test is currently broken, giving the error "you must return the jaden_case string"

char* to_jaden_case (const char *string, const char* expected)
{
  // write to jaden_case and return it
  const int length = strlen(string);
  char* jaden_case = malloc(sizeof(char) * length);
  bool had_space = true;
  for (int c_ndx = 0; c_ndx < length; c_ndx++) {
    if (had_space) {
      jaden_case[c_ndx] = (char)toupper(string[c_ndx]);
      had_space = false;
    } else {
      if (string[c_ndx] == ' ') {
        had_space = true;
      }
      jaden_case[c_ndx] = string[c_ndx];
    }
  }
  if (strcmp(jaden_case, expected) == 0) {
    printf("Formatted string correctly\n");
  } else {
    printf("Formatted string incorrectly\n");
  }
	return jaden_case;
}

char *to_jaden_case (char *jaden_case, const char *string)
{
  // write to jaden_case and return it
  const int length = strlen(string);
	char* jaden_case = malloc(sizeof(char) * length);
  bool had_space = true;
  for (int c_ndx = 0; c_ndx < length; c_ndx++) {
    if (had_space) {
      jaden_case[c_ndx] = (char)toupper(string[c_ndx]);
      had_space = false;
    } else {
      if (string[c_ndx] == ' ') {
        had_space = true;
      }
      jaden_case[c_ndx] = string[c_ndx];
    }
  }
	return jaden_case;
}

int main(void) {
  to_jaden_case(
		"",
		""
	);
	to_jaden_case(
		"How can mirrors be real if our eyes aren't real",
		"How Can Mirrors Be Real If Our Eyes Aren't Real"
	);
	to_jaden_case(
		"All the rules in this world were made by someone no smarter than you. So make your own.",
		"All The Rules In This World Were Made By Someone No Smarter Than You. So Make Your Own."
	);
	to_jaden_case(
		"School is the tool to brainwash the youth.",
		"School Is The Tool To Brainwash The Youth."
	);
	to_jaden_case(
		"If everybody in the world dropped out of school we would have a much more intelligent society.",
		"If Everybody In The World Dropped Out Of School We Would Have A Much More Intelligent Society."
	);
	to_jaden_case(
		"Dying is mainstream",
		"Dying Is Mainstream"
	);
	to_jaden_case(
		"If there is bread winners, there is bread losers. But you can't toast what isn't real.",
		"If There Is Bread Winners, There Is Bread Losers. But You Can't Toast What Isn't Real."
	);
	to_jaden_case(
		"When you Live your Whole life In a Prison freedom Can be So dull.",
		"When You Live Your Whole Life In A Prison Freedom Can Be So Dull."
	);
	to_jaden_case(
		"The moment that truth is organized it becomes a lie.",
		"The Moment That Truth Is Organized It Becomes A Lie."
	);
	to_jaden_case(
		"Pay attention to the numbers in your life they are vastly important.",
		"Pay Attention To The Numbers In Your Life They Are Vastly Important."
	);
	to_jaden_case(
		"If a book store never runs out of a certain book, dose that mean that nobody reads it, or everybody reads it",
		"If A Book Store Never Runs Out Of A Certain Book, Dose That Mean That Nobody Reads It, Or Everybody Reads It"
	);
  return 0;
}