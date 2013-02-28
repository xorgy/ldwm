# ldwm - less dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = ldwm.c
OBJ = ${SRC:.c=.o}

all: options ldwm

options:
	@echo ldwm build options:
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

ldwm: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f ldwm ${OBJ} ldwm-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p ldwm-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk \
		ldwm.1 ${SRC} ldwm.png ldwm-${VERSION}
	@tar -cf ldwm-${VERSION}.tar ldwm-${VERSION}
	@gzip ldwm-${VERSION}.tar
	@rm -rf ldwm-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ldwm ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/ldwm
	@echo installing manual page to ${DESTDIR}${MANPREFIX}/man1
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < ldwm.1 > ${DESTDIR}${MANPREFIX}/man1/ldwm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/ldwm.1

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/ldwm
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/ldwm.1

.PHONY: all options clean dist install uninstall
