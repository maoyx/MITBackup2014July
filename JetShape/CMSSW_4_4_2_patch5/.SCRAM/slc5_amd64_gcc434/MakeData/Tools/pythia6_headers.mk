pythia6_headers             := pythia6_headers
ALL_TOOLS      += pythia6_headers
pythia6_headers_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/pythia6/424-cms3/include
pythia6_headers_EX_INCLUDE  := $(pythia6_headers_LOC_INCLUDE)
pythia6_headers_INIT_FUNC := $$(eval $$(call ProductCommonVars,pythia6_headers,,,pythia6_headers))

