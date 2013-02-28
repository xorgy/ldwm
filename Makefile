# jwm - just window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = jwm.c
OBJ = ${SRC:.c=.o}

all: options jwm

options:
	@echo jwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	@echo creating $@ from config.def.h
	@cp config.def.h $@

jwm: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f jwm ${OBJ} jwm-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p jwm-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk \
		jwm.1 ${SRC} jwm-${VERSION}
	@tar -cf jwm-${VERSION}.tar jwm-${VERSION}
	@gzip jwm-${VERSION}.tar
	@rm -rf jwm-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f jwm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/jwm
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < jwm.1 > ${DESTDIR}${MANPREFIX}/man1/jwm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/jwm.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/jwm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/jwm.1

.PHONY: all options clean dist install uninstall
