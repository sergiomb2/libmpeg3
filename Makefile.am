lib_LTLIBRARIES = libmpeg3.la
AM_CFLAGS = $(CPU_CFLAGS) $(LARGEFILE_CFLAGS)
libmpeg3_la_LDFLAGS = -version-info @LIBMPEG3_VERSION_INFO@
libmpeg3_la_LIBADD = @A52DEC_LIBS@ video/libmpeg3_video.la audio/libmpeg3_audio.la -lm \
		     -lpthread
libmpeg3_la_SOURCES = libmpeg3.c mpeg3bits.c mpeg3atrack.c mpeg3css.c \
	mpeg3demux.c \
	mpeg3ifo.c \
	mpeg3io.c \
	mpeg3strack.c \
	mpeg3title.c \
	mpeg3tocutil.c \
	mpeg3vtrack.c \
	workarounds.c

bin_PROGRAMS = mpeg3dump mpeg3peek mpeg3toc mpeg3cat
mpeg3dump_SOURCES = mpeg3dump.c
mpeg3dump_LDADD = libmpeg3.la
mpeg3dump_CFLAGS = $(AM_CFLAGS)
mpeg3peek_SOURCES = mpeg3peek.c
mpeg3peek_LDADD = libmpeg3.la
mpeg3peek_CFLAGS = $(AM_CFLAGS)
mpeg3toc_SOURCES = mpeg3toc.c
mpeg3toc_LDADD = libmpeg3.la
mpeg3toc_CFLAGS = $(AM_CFLAGS)
mpeg3cat_SOURCES = mpeg3cat.c
mpeg3cat_LDADD = libmpeg3.la
mpeg3cat_CFLAGS = $(AM_CFLAGS)
if HAVE_QUICKTIME
bin_PROGRAMS += mpeg2qt
mpeg2qt_SOURCES = mpeg2qt.c
mpeg2qt_LDADD = libmpeg3.la @QUICKTIME_LIBS@
mpeg2qt_CFLAGS = $(AM_CFLAGS) @QUICKTIME_CFLAGS@
endif

SUBDIRS = audio video 

EXTRA_DIST = docs

noinst_HEADERS = bitstream.h \
	ifo.h \
	mpeg3atrack.h \
	mpeg3css.h \
	mpeg3css_fake.c \
	mpeg3demux.h \
	mpeg3io.h \
	mpeg3private.inc \
	mpeg3title.h \
	mpeg3vtrack.h \
	timecode.h \
	workarounds.h

dist_noinst_SCRIPTS = bootstrap

pkgincludedir=$(includedir)/mpeg3
pkginclude_HEADERS=libmpeg3.h mpeg3private.h mpeg3protos.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libmpeg3.pc

LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTC_FLAGS)
