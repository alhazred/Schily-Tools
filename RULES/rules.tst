#ident "@(#)rules.tst	1.3 21/04/28 "
###########################################################################
# Written 2016 by J. Schilling
###########################################################################
#
# Test rules
#
###########################################################################
# Copyright (c) J. Schilling
###########################################################################
# The contents of this file are subject to the terms of the
# Common Development and Distribution License, Version 1.0 only
# (the "License").  You may not use this file except in compliance
# with the License.
#
# See the file CDDL.Schily.txt in this distribution for details.
# A copy of the CDDL is also available via the Internet at
# http://www.opensource.org/licenses/cddl1.txt
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file CDDL.Schily.txt from this distribution.
###########################################################################

tests:
	$(NOECHO)DIR=tests;							\
	if [ -d ./$$DIR -a -r ./$$DIR/Makefile ] ; then			\
		cd ./$$DIR && "$(MAKE)" $(MAKEMACS) XARCH=$(XARCH) DIRNAME=$(CURWDIR)/$$DIR $@;	\
	else								\
		echo "NOTICE: Partial source ($(CURWDIR)/$$DIR) missing";\
	fi								\
