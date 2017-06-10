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
#endif

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#ifdef WITH_CAPSICUM
#include <sys/capsicum.h>
#include <capsicum_helpers.h>
#endif

#include <dlfcn.h>
#include <err.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	bool (*func)(void);
	char buf[16];
	void *handle;
	char *app;

#ifdef WITH_CAPSICUM
	if (caph_limit_stdio() != 0)
		errx(1, "Failed to limit std{in,out,err}");

	app = strstr(argv[0], "true") ? "true" : "false";
	snprintf(buf, sizeof(buf), "lib%s.so", app);
	handle = dlopen(buf, RTLD_GLOBAL | RTLD_LAZY);
	if (handle == NULL)
		errx(1, "Unable to load shared app");

	if (cap_enter() != 0 && errno != ENOSYS)
		errx(1, "Failed to enter capability mode");
#endif

	snprintf(buf, sizeof(buf), "get_%s", app);
	func = dlsym(handle, buf);
	if (func == NULL)
		errx(1, "Fake function");

	return (!(func() == true));
}
