gsl             := gsl
ALL_TOOLS      += gsl
gsl_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/gsl/1.10-cms5/include
gsl_EX_INCLUDE  := $(gsl_LOC_INCLUDE)
gsl_LOC_LIB := gsl gslcblas
gsl_EX_LIB  := $(gsl_LOC_LIB)
gsl_INIT_FUNC := $$(eval $$(call ProductCommonVars,gsl,,,gsl))

