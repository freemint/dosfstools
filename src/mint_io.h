/*
 * mint_io.h
 *
 * Copyright (C) 2000 Frank Naumann <fnaumann@freemint.de>.
 *
 * %Begin-Header%
 * This file may be redistributed under the terms of the GNU Public
 * License.
 * %End-Header%
 */

# ifdef __MINT__

# ifndef _mint_io_h
# define _mint_io_h

# define BLKGETSIZE		(('b'<< 8) | 1)
# define BLOCKSIZE		(('b'<< 8) | 2)

int gettype(int fd);

/* 64-bit seek over the XHDI backend. */
loff_t llseek(int fd, loff_t offset, int whence);

/* In the filesystem code off_t is forced to 64-bit (mint_lfs.h), but mint_io.c
 * keeps a 32-bit lseek() to match libc. Route the filesystem code's seeks to the
 * 64-bit llseek(). mint_io.c #undefs __USE_FILE_OFFSET64 before including this
 * header, so the macro is inactive there and its own lseek() is left alone. */
#ifdef __USE_FILE_OFFSET64
#define lseek(fd, offset, whence) llseek((fd), (loff_t)(offset), (whence))
#endif

# endif /* _mint_io_h */

# endif /* __MINT__ */
