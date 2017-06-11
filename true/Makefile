# $FreeBSD$

PROG=	true

CFLAGS=	-I${.CURDIR:H}/libtrue
LDADD=	-L../libtrue -ltrue

OS!=	uname
.if ${OS} == "FreeBSD"
LDADD+=	-lxo
.endif

MAN=

.include <bsd.prog.mk>
