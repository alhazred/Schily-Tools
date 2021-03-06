/* @(#)nixread.c	1.14 09/06/30 Copyright 1986, 1996-2009 J. Schilling */
/*
 *	Non interruptable extended read
 *
 *	Copyright (c) 1986, 1996-2009 J. Schilling
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

#include "schilyio.h"

EXPORT ssize_t
_nixread(f, buf, count)
	int	f;
	void	*buf;
	size_t	count;
{
	register char	*p = (char *)buf;
	register ssize_t ret;
	register int	total = 0;
		int	oerrno = geterrno();

	if ((ret = (ssize_t)count) < 0) {
		seterrno(EINVAL);
		return ((ssize_t)-1);
	}
	while (count > 0) {
		while ((ret = read(f, p, count)) < 0) {
			if (geterrno() == EINTR) {
				/*
				 * Set back old 'errno' so we don't change the
				 * errno visible to the outside if we did
				 * not fail.
				 */
				seterrno(oerrno);
				continue;
			}
			return (ret);	/* Any other error */
		}
		if (ret == 0)		/* Something went wrong */
			break;

		total += ret;
		count -= ret;
		p += ret;
	}
	return (total);
}
