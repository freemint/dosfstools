/* mint_lfs.h - force a 64-bit off_t for the MiNT build.
 *
 * mintlib ships the LFS64 types (off64_t/loff_t) but, unlike glibc, refuses to
 * widen off_t itself: features.h wraps the
 *     _FILE_OFFSET_BITS == 64  ->  __USE_FILE_OFFSET64
 * step in "#ifndef __MINT__" (commented "not yet"), because mintlib has no
 * 64-bit file-seek syscall layer (no lseek64 etc.).  So -D_FILE_OFFSET_BITS=64
 * is a silent no-op on MiNT and off_t stays 32-bit.
 *
 * dosfstools does not need mintlib's seek layer: mint_io.c provides its own
 * 64-bit XHDI read/write/llseek and only ever operates on block devices.  So we
 * can safely force __USE_FILE_OFFSET64 on, which widens off_t to 64-bit and lets
 * the filesystem-offset code address volumes larger than 2 GB.  (struct stat is
 * unaffected: bits/stat.h declares st_size with the raw __off_t.)
 *
 * This header is force-included (-include, see configure.ac/Makefile.am) ahead
 * of every system header, so it runs *after* <features.h> has done its #undef
 * and *before* <sys/types.h> typedefs off_t.  mint_io.c, the 32-bit libc-facing
 * boundary, #undefs the macro again at its top.
 */
#include <features.h>
#ifdef __MINT__
#define __USE_FILE_OFFSET64 1
#endif
