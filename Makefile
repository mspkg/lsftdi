CC ?= gcc
PREFIX ?= /usr

all:
	${CC} lsftdi.c -lftdi1 -lusb-1.0 -o lsftdi

install:
	test -d ${DESTDIR}${PREFIX}/sbin || mkdir -p ${DESTDIR}${PREFIX}/sbin
	install -pm 755 lsftdi ${DESTDIR}${PREFIX}/sbin

clean:
	rm lsftdi
