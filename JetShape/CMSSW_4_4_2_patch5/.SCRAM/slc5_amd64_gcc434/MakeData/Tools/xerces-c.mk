xerces-c             := xerces-c
ALL_TOOLS      += xerces-c
xerces-c_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/xerces-c/2.8.0-cms/include
xerces-c_EX_INCLUDE  := $(xerces-c_LOC_INCLUDE)
xerces-c_LOC_LIB := xerces-c
xerces-c_EX_LIB  := $(xerces-c_LOC_LIB)
xerces-c_INIT_FUNC := $$(eval $$(call ProductCommonVars,xerces-c,,,xerces-c))

