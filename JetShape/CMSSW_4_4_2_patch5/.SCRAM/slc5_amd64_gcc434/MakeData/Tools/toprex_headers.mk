toprex_headers             := toprex_headers
ALL_TOOLS      += toprex_headers
toprex_headers_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/toprex/4.23-cms4/include
toprex_headers_EX_INCLUDE  := $(toprex_headers_LOC_INCLUDE)
toprex_headers_INIT_FUNC := $$(eval $$(call ProductCommonVars,toprex_headers,,,toprex_headers))

