qtextra             := qtextra
ALL_TOOLS      += qtextra
qtextra_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/qt/4.6.3-cms/include/QtScript
qtextra_EX_INCLUDE  := $(qtextra_LOC_INCLUDE)
qtextra_LOC_LIB := QtScript
qtextra_EX_LIB  := $(qtextra_LOC_LIB)
qtextra_LOC_USE := qtbase
qtextra_EX_USE  := $(qtextra_LOC_USE)
qtextra_INIT_FUNC := $$(eval $$(call ProductCommonVars,qtextra,,,qtextra))

