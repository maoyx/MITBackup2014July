herwigpp             := herwigpp
ALL_TOOLS      += herwigpp
herwigpp_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc462/external/herwigpp/2.5.0-cms7/include
herwigpp_EX_INCLUDE  := $(herwigpp_LOC_INCLUDE)
herwigpp_INIT_FUNC := $$(eval $$(call ProductCommonVars,herwigpp,,,herwigpp))

