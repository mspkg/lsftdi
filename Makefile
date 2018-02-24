# lsftdi Makefile

CC ?= gcc
CFLAGS ?= -g -O2 -Wall
PREFIX ?= /usr
MANDIR ?=${PREFIX}/share/man

all:
	${CC} ${CFLAGS} lsftdi.c -lftdi1 -lusb-1.0 -o lsftdi

install:
	test -d ${DESTDIR}${PREFIX}/sbin || mkdir -p ${DESTDIR}${PREFIX}/sbin
	install -pm 755 lsftdi ${DESTDIR}${PREFIX}/sbin
	test -d ${DESTDIR}${MANDIR}/man1 || mkdir -p ${DESTDIR}${MANDIR}/man1
	install -pm 444 lsftdi.1 ${MANDIR}/man1

clean:
	rm lsftdi
