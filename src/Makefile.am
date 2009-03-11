bin_PROGRAMS = cliente1
cliente1_SOURCES = aomap.cpp audioengine.cpp bar.cpp bodydata.cpp bytequeue.cpp \
	cliente1.cpp clienteargentum.cpp clouds.cpp comunicador.cpp configdata.cpp \
	console.cpp customwidgets.cpp entity.cpp factory.cpp fonts.cpp fxanim.cpp \
	graphicsadapter.cpp grhdata.cpp grhmanager.cpp guichanloader.cpp hechizos.cpp helpers.cpp \
	imagemanager.cpp inifile.cpp inventory.cpp maingui.cpp mensajes.cpp paquete.cpp \
	paquetec.cpp particulas.cpp rect.cpp rendererengine.cpp sdl_cursor_helper.cpp \
	sock.cpp stats.cpp vcreation.cpp vdrop.cpp verror.cpp vestadisticas.cpp \
	vlogin.cpp vmain.cpp vpassword.cpp

# set the include path found by configure
AM_CPPFLAGS =  $(LIBSDL_CFLAGS) $(all_includes)

# the library search path.
cliente1_LDFLAGS = $(all_libraries) $(LIBSDL_RPATH)
cliente1_LDADD = $(top_builddir)/src/guichan/sdl/libguichan_sdl.la \
	$(top_builddir)/src/guichan/opengl/libguichan_opengl.la $(top_builddir)/src/guichan/libguichan.la \
	$(top_builddir)/src/guichan/widgets/libguichan_widgets.la $(FREETYPE_LIBS) $(LIBSDL_LIBS) -lGL -lGLU -lm
noinst_HEADERS = aomap.h audioengine.h bar.h basictypes.h bodydata.h \
	bytequeue.h class_types.h clienteargentum.h clouds.h color.h comunicador.h \
	configdata.h console.h customwidgets.h entity.h factory.h fonts.h fxanim.h \
	graphicsadapter.h grhdata.h grhmanager.h guichanloader.h imagemanager.h inifile.h \
	inventory.h maingui.h mensajes.h paquete.h paquetec.h particulas.h rect.h \
	rendererengine.h sock.h vcreation.h vdrop.h verror.h vlogin.h vmain.h vpassword.h

SUBDIRS = guichan
INCLUDES = -I$(top_srcdir)/include $(LIBSDL_CFLAGS) $(FREETYPE_CFLAGS)
