valgrind             := valgrind
ALL_TOOLS      += valgrind
valgrind_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/valgrind/3.6.1-cms/include
valgrind_EX_INCLUDE  := $(valgrind_LOC_INCLUDE)
valgrind_INIT_FUNC := $$(eval $$(call ProductCommonVars,valgrind,,,valgrind))

