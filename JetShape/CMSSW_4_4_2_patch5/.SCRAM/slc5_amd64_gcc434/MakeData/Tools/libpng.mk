libpng             := libpng
ALL_TOOLS      += libpng
libpng_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/libpng/1.2.10-cms4/include
libpng_EX_INCLUDE  := $(libpng_LOC_INCLUDE)
libpng_LOC_LIB := png
libpng_EX_LIB  := $(libpng_LOC_LIB)
libpng_LOC_USE := zlib
libpng_EX_USE  := $(libpng_LOC_USE)
libpng_INIT_FUNC := $$(eval $$(call ProductCommonVars,libpng,,,libpng))

