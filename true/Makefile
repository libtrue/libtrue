# $FreeBSD$

PROG=	true
SRCS=	true.c

CFLAGS=	-I${.CURDIR:H}/libtrue
LDADD=	-L../libtrue -ltrue -lxo

.if !defined(NO_DTRACE)
SRCS+=	true-dtrace.d
CFLAGS+= -DHAVE_DTRACE
.endif

MAN=

.include <bsd.prog.mk>
