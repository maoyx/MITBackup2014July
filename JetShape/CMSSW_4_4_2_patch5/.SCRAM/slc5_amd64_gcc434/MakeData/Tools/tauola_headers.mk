tauola_headers             := tauola_headers
ALL_TOOLS      += tauola_headers
tauola_headers_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/tauola/27.121.5-cms14/include
tauola_headers_EX_INCLUDE  := $(tauola_headers_LOC_INCLUDE)
tauola_headers_INIT_FUNC := $$(eval $$(call ProductCommonVars,tauola_headers,,,tauola_headers))

