gdbm             := gdbm
ALL_TOOLS      += gdbm
gdbm_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/gdbm/1.8.3-cms/include
gdbm_EX_INCLUDE  := $(gdbm_LOC_INCLUDE)
gdbm_LOC_LIB := gdbm
gdbm_EX_LIB  := $(gdbm_LOC_LIB)
gdbm_INIT_FUNC := $$(eval $$(call ProductCommonVars,gdbm,,,gdbm))

