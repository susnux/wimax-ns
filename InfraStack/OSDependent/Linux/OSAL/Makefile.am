noinst_LTLIBRARIES = libosal.la
varlogdir = ${localstatedir}/log
pkgvarlogdir = ${varlogdir}/$(PACKAGE)
pkgsysconfdir = ${sysconfdir}/$(PACKAGE)
pkglocalstatedir= ${localstatedir}/lib/$(PACKAGE)
logrotatedir = ${sysconfdir}/logrotate.d/

logrotate_DATA = wimax.conf

EXTRA_DIST = logrotate.in
CLEANFILES = wimax.conf

wimax.conf: logrotate.in
	sed -e "s|@pkgvarlogdir@|$(pkgvarlogdir)|g" $^ > $@

libosal_la_SOURCES = \
			$(srcdir)/./Primitives/wimax_osal_primitives.c \
			$(srcdir)/./Primitives/wimax_osal_strings.c \
			$(srcdir)/./Primitives/wimax_osal_event.c \
			$(srcdir)/./Primitives/wimax_osal_util.c \
			$(srcdir)/./Primitives/wimax_osal_trace.c \
			$(srcdir)/./Primitives/wimax_osal_win.c \
			$(srcdir)/./Services/wimax_osal_services.c \
			$(srcdir)/./Services/wimax_osal_services.h \
			$(srcdir)/./Services/wimax_osal_config_controller.c \
			$(srcdir)/./Services/wimax_osal_crypt_services.c \
			$(srcdir)/./Services/wimax_osal_win_config_controller_defines.h \
			$(srcdir)/../EventLogMessages/EventLogger.c \
			$(srcdir)/../EventLogMessages/EventLogger.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Primitives/wimax_osal_string.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Primitives/wimax_osal_types.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Primitives/wimax_osal_primitives.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Services/wimax_osal_crypt_services.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Services/wimax_osal_event_logger.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Services/wimax_osal_config_controler.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Services/wimax_osal_services_cmn.h \
			$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Services/wimax_osal_ip_services.h \
			$(srcdir)/./Primitives/wimax_osal_basictypes.h \
			$(srcdir)/./Services/wimax_osal_config_controler_defines.h \
			$(srcdir)/./Primitives/wimax_osal_trace.h \
			$(srcdir)/./Primitives/crtdbg.h \
			$(srcdir)/Primitives/wimax_osal_error.h

libosal_la_LIBADD = @ZLIB_LIBS@

 
#TODO:: Move out the compilations of thesefiles to services project (they are high level absractions with
#       dependencies on higher layers..
#			$(srcdir)/./Services/wimax_osal_event_logger.c 

#TODO:: Check some of these below and their contents if they are still needed. 
#			$(srcdir)/LinuxHandles.h \
#			$(srcdir)/windows_error.h \
#			$(srcdir)/./Primitives/wimax_osal_win.c \
#			$(srcdir)/windows_types.h 



AM_CFLAGS = -lz -I "$(srcdir)/./Primitives" \
	-I "$(srcdir)/./Services" \
	-I "$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Primitives" \
	-I "$(srcdir)/../../../OSAgnostic/OSInterface/OSAL/Services" \
	-I "$(srcdir)/../../../OSAgnostic/OSInterface/OSAL" \
	-I "$(srcdir)/../../../OSAgnostic/Common/CommonServices/" \
	-I "$(srcdir)/../../../OSAgnostic/Common/CommonServices/XmlParser" \
	-I "$(srcdir)/../../../OSAgnostic/OSInterface/InfraStackModules" \
	-I "$(top_srcdir)/InfraStack/OSAgnostic/Common/L4Common/SourceControl" \
	-I "$(top_srcdir)" \
	@ZLIB_CFLAGS@ \
	-D PKG_VAR_LOG_DIR="\"${pkgvarlogdir}\"" \
	-D PKG_DATA_DIR="\"${pkgdatadir}\"" \
	-D LIB_DIR="\"${libdir}\"" \
	-D PKG_SYSCONF_DIR="\"${pkgsysconfdir}\"" \
	-D PKG_LOCALSTATE_DIR="\"${pkglocalstatedir}\"" \
	-D NATIVE_LINUX

