qtdesigner             := qtdesigner
ALL_TOOLS      += qtdesigner
qtdesigner_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/qt/4.6.3-cms/include/QtDesigner
qtdesigner_EX_INCLUDE  := $(qtdesigner_LOC_INCLUDE)
qtdesigner_LOC_LIB := QtDesigner
qtdesigner_EX_LIB  := $(qtdesigner_LOC_LIB)
qtdesigner_LOC_USE := qtbase qt
qtdesigner_EX_USE  := $(qtdesigner_LOC_USE)
qtdesigner_INIT_FUNC := $$(eval $$(call ProductCommonVars,qtdesigner,,,qtdesigner))

