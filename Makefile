#############################################################################
# Makefile for building: app
# Generated by qmake (2.01a) (Qt 4.5.2) on: jue oct 15 10:05:28 2009
# Project:  GenomAMf.pro
# Template: app
# Command: /opt/qtsdk-2009.03/qt/bin/qmake -unix CONFIG+=debug_and_release -o Makefile GenomAMf.pro
#############################################################################

first: release
install: release-install
uninstall: release-uninstall
MAKEFILE      = Makefile
QMAKE         = /opt/qtsdk-2009.03/qt/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		release \
		debug

release: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release
release-make_default: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release 
release-make_first: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release first
release-all: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: $(MAKEFILE).Release FORCE
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_default: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug 
debug-make_first: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug first
debug-all: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: $(MAKEFILE).Debug FORCE
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: GenomAMf.pro  /opt/qtsdk-2009.03/qt/mkspecs/linux-g++/qmake.conf /opt/qtsdk-2009.03/qt/mkspecs/common/g++.conf \
		/opt/qtsdk-2009.03/qt/mkspecs/common/unix.conf \
		/opt/qtsdk-2009.03/qt/mkspecs/common/linux.conf \
		/opt/qtsdk-2009.03/qt/mkspecs/qconfig.pri \
		/opt/qtsdk-2009.03/qt/mkspecs/features/qt_functions.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/qt_config.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/exclusive_builds.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/default_pre.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/release.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/debug_and_release.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/default_post.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/warn_on.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/qt.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/unix/thread.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/moc.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/resources.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/uic.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/yacc.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/lex.prf \
		/opt/qtsdk-2009.03/qt/mkspecs/features/include_source_dir.prf \
		/opt/qtsdk-2009.03/qt/lib/libQtGui.prl \
		/opt/qtsdk-2009.03/qt/lib/libQtCore.prl
	$(QMAKE) -unix CONFIG+=debug_and_release -o Makefile GenomAMf.pro
/opt/qtsdk-2009.03/qt/mkspecs/common/g++.conf:
/opt/qtsdk-2009.03/qt/mkspecs/common/unix.conf:
/opt/qtsdk-2009.03/qt/mkspecs/common/linux.conf:
/opt/qtsdk-2009.03/qt/mkspecs/qconfig.pri:
/opt/qtsdk-2009.03/qt/mkspecs/features/qt_functions.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/qt_config.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/exclusive_builds.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/default_pre.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/release.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/debug_and_release.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/default_post.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/warn_on.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/qt.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/unix/thread.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/moc.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/resources.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/uic.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/yacc.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/lex.prf:
/opt/qtsdk-2009.03/qt/mkspecs/features/include_source_dir.prf:
/opt/qtsdk-2009.03/qt/lib/libQtGui.prl:
/opt/qtsdk-2009.03/qt/lib/libQtCore.prl:
qmake: qmake_all FORCE
	@$(QMAKE) -unix CONFIG+=debug_and_release -o Makefile GenomAMf.pro

qmake_all: FORCE

make_default: release-make_default debug-make_default FORCE
make_first: release-make_first debug-make_first FORCE
all: release-all debug-all FORCE
clean: release-clean debug-clean FORCE
distclean: release-distclean debug-distclean FORCE
	-$(DEL_FILE) Makefile

release-mocclean: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables: $(MAKEFILE).Release
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables: $(MAKEFILE).Debug
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile
