# $FreeBSD$

PROG=	true

BINDIR=	/usr/bin

CFLAGS=	-I${.CURDIR:H}/libtrue
LDADD=	-L../libtrue -ltrue

OS!=	uname
.if ${OS} == "FreeBSD" && exists(/usr/lib/libxo.so)
LDADD+=	-lxo
.endif

MAN=

.include <bsd.prog.mk>
