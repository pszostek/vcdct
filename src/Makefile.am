SUBDIRS=libfst libz
AM_CXXFLAGS = -I$(top_srcdir)/src @AM_CXXFLAGS@
AM_LDFLAGS = @AM_LDFLAGS@
bin_PROGRAMS = vcdct
vcdct_SOURCES=common.h fst_writer.h main.cpp parse_exception.h scalar_var.h \
	variable.h container_variable.h var_type.gperf vcd_comparator.cpp vcd_header.h vcd_parser.h \
	vector_var.h file_handling_exception.h fst_writer.cpp scalar_var.cpp trace.h \
	var_type_code.h var_type_hash.hpp vcd_comparator.h vcd_comparator.hpp \
	vcd_parser.cpp vector_var.cpp variable.cpp
vcdct_LDADD = $(top_builddir)/src/libfst/libfst.a $(top_builddir)/src/libz/libz.a
#vcdct_LDADD = $(AM_LDFLAGS)

var_type_hash.hpp: var_type_code.h var_type.gperf
	printf "$(GPERF) -CGD -N IsValidVarType -L C++ -t $(srcdir)/var_type.gperf > var_type_hash.hpp" | sh
