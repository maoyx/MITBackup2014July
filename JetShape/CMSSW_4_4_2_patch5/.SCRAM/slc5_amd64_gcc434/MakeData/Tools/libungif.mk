libungif             := libungif
ALL_TOOLS      += libungif
libungif_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/libungif/4.1.4-cms/include
libungif_EX_INCLUDE  := $(libungif_LOC_INCLUDE)
libungif_LOC_LIB := ungif
libungif_EX_LIB  := $(libungif_LOC_LIB)
libungif_LOC_USE := libjpg zlib
libungif_EX_USE  := $(libungif_LOC_USE)
libungif_INIT_FUNC := $$(eval $$(call ProductCommonVars,libungif,,,libungif))

