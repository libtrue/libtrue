/*-
 * Copyright (c) 2017 Andrew Turner
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#if defined(__FreeBSD__)
#define	WITH_CAPSICUM
#define WITH_XO
#endif

#include <sys/cdefs.h>

#ifdef WITH_CAPSICUM
#include <sys/capsicum.h>
#include <capsicum_helpers.h>
#endif

#include <err.h>
#include <errno.h>
#include <locale.h>
#include <stdbool.h>

#ifdef WITH_XO
#include <libxo/xo.h>
#endif

#include <true.h>

int
main(int argc, char *argv[])
{
	int value;

#ifdef WITH_CAPSICUM
	if (caph_limit_stdio() != 0)
		errx(1, "Failed to limit std{in,out,err}");

	if (cap_enter() != 0 && errno != ENOSYS)
		errx(1, "Failed to enter capability mode");
#endif

#ifdef WITH_XO
	(void) setlocale(LC_CTYPE, "");

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		return (argc);
#endif

	value = get_true();
	if (value == 0)
		errx(1, "Bad true value");

#ifdef WITH_XO
	xo_open_container("true");
	if (!value) {
		xo_errx(1, "Bad true value: %u", value);
	}
	xo_emit("{n:value/%s}\n", value ? "true" : "false");
	xo_close_container("true");
	xo_finish();
#endif

	return (0);
}
