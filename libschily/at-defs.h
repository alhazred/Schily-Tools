/* @(#)at-defs.h	1.3 18/07/23 Copyright 2011-2018 J. Schilling */
/*
 *	Libschily internal definitions for openat() emulation
 *	and related functions.
 *
 *	Copyright (c) 2011-2018 J. Schilling
 */
/*
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * See the file CDDL.Schily.txt in this distribution for details.
 * A copy of the CDDL is also available via the Internet at
 * http://www.opensource.org/licenses/cddl1.txt
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file CDDL.Schily.txt from this distribution.
 */
#ifndef	_AT_DEFS_H

/*
 * This is a list of errors that are expected to be not a result of
 * a /proc fs problem. If such an error is encountered, then we return
 * after the open() or other call without trying to emulate the *at()
 * interface via savewd()/fchdir()/doit()/restorewd().
 */
#ifdef	ENOSYS
#define	__ENOSYS	ENOSYS
#else
#define	__ENOSYS	EPERM
#endif
#ifdef	EOPNOTSUPP
#define	__EOPNOTSUPP	EOPNOTSUPP
#else
#define	__EOPNOTSUPP	EPERM
#endif

/*
 * XXX: Should we include ENOENT here as our emulation needs
 * XXX: to be able to emulate openat(fd, name, O_CREAT, 666) or
 * XXX: mknodat(fd, name, mode, dev).
 * XXX: Since /proc uses symlinks, it should be safe.
 */
#define	NON_PROCFS_ERRNO(e)					\
			((e) == ENOENT || (e) == ENOTDIR ||	\
			(e) == EACCES || (e) == EPERM ||	\
			(e) == __ENOSYS /* Solaris */ ||	\
			(e) == __EOPNOTSUPP /* FreeBSD */)

/*
 * n refers to an absolute path name.
 */
#define	ABS_NAME(n)	((n)[0] == '/')

#ifdef	min
#undef	min
#endif
#define	min(a, b)	((a) < (b) ? (a):(b))

#ifdef	max
#undef	max
#endif
#define	max(a, b)	((a) < (b) ? (b):(a))

/*
 * From procnameat.c
 */
extern char	*proc_fd2name	__PR((char *buf, int fd, const char *name));

/*
 * From wdabort.c
 */
extern	void	savewd_abort	__PR((int err));
extern	void	fchdir_abort	__PR((int err));
extern	void	restorewd_abort	__PR((int err));

#ifdef	HAVE_LARGEFILES
#define	fstatat	fstatat64
#define	openat	openat64
#endif

#endif	/* _AT_DEFS_H */
