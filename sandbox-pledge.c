/*	$Id$ */
/*
 * Copyright (c) 2015 Kristaps Dzonsons <kristaps@bsd.lv>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_PLEDGE

#include <unistd.h>

#include <stdarg.h>

#include "kcgi.h"
#include "extern.h"

int
ksandbox_pledge_init_child(void *arg, enum sandtype type)
{
	const char *fl;

	fl = "stdio";
	if (SAND_WORKER != type)
		fl = "stdio unix sendfd recvfd";

	if (-1 == pledge(fl, NULL)) {
		XWARN("pledge: %s",
			SAND_WORKER != type ?
			"control" : "worker");
		return(0);
	}
	return(1);
}

#else
int dummy;
#endif
