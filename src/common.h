/* common.h - Common functions

   Copyright (C) 1993 Werner Almesberger <werner.almesberger@lrc.di.epfl.ch>
   Copyright (C) 2008-2014 Daniel Baumann <mail@daniel-baumann.ch>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>.

   The complete text of the GNU General Public License
   can be found in /usr/share/common-licenses/GPL-3 file.
*/

#ifndef _COMMON_H
#define _COMMON_H

#include <sys/types.h>

#include <limits.h>
#include <stdint.h>

#ifndef OFF_MAX
	#define OFF_MAX (off_t)((1ULL << (sizeof(off_t) * CHAR_BIT - 1)) - 1)
#endif

extern int interactive;
extern int write_immed;
#ifdef __MINT__
extern int preen;
#else
#define preen 0
#endif
/* Filesystem follows Atari GEMDOS rules rather than MS-DOS: filename
 * character set, FAT12/16 selection, special FAT values, cluster size and
 * sector-count limits.
 * 0: MS-DOS, 1: GEMDOS, -1: decide from the filesystem (--variant=auto).
 * -1 is resolved to 0 or 1 before anything reads it; every other consumer
 * treats this as a plain boolean. */
extern int gemdos_semantics;

/* Characters GEMDOS rejects in a directory entry. A volume label is one such
 * entry in the root directory, mirrored into the boot sector, and both copies
 * have to hold the same string - so this set governs file names and labels
 * alike. MS-DOS has a separate, stricter set for each. */
#define GEMDOS_BAD_CHARS "*?\\/:"

/* program_name used for printing messages; no name will be printed when it is
 * left as NULL */
extern const char *program_name;

void die(const char *msg, ...)
    __attribute((noreturn, format(printf, 1, 2)));

/* Displays a prinf-style message and terminates the program. */

void pdie(const char *msg, ...)
    __attribute((noreturn, format(printf, 1, 2)));

/* Like die, but appends an error message according to the state of errno. */

void *alloc(int size);

/* mallocs SIZE bytes and returns a pointer to the data. Terminates the program
   if malloc fails. */

void *qalloc(void **root, int size);

/* Like alloc, but registers the data area in a list described by ROOT. */

void qfree(void **root);

/* Deallocates all qalloc'ed data areas described by ROOT. */

int min(int a, int b);

/* Returns the smaller integer value of a and b. */

int xasprintf(char **strp, const char *fmt, ...)
    __attribute((format(printf, 2, 3)));

/* Runs asprintf() and terminates the program if it fails. */

int get_choice(int noninteractive_result, const char *noninteractive_msg,
	       int choices, ...);

/*
 * Display a numbered list of choices and accept user input to select one. If
 * interactive is false, it will instead print noninteractive_msg and return
 * noninteractive_result. The number of options must be given in choices and
 * must be more than one and less than ten.
 *
 * The variable arguments are choices times <int val, const char *desc>, where
 * val is the value that is returned when the user selects this option and desc
 * is the string describing this option.
 */

char *get_line(const char *prompt, char *dest, size_t length);

/*
 * Display prompt and read a line, placing it in dest with at most length-1
 * characters plus a null byte. This behaves like printing a prompt and fgets()
 * afterwards with the addition of temporarily enabling canonical input mode
 * with echo if needed.
 */

uint32_t generate_volume_id(void);

/*
 * Generate a 32 bit volume ID
 */

const char *volume_label_bad_chars(void);
int validate_volume_label(char *doslabel);

/*
 * Validate volume label
 */

#endif
