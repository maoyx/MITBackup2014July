qt             := qt
ALL_TOOLS      += qt
qt_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/qt/4.6.3-cms/include/QtOpenGL /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/qt/4.6.3-cms/include/QtGui
qt_EX_INCLUDE  := $(qt_LOC_INCLUDE)
qt_LOC_LIB := QtOpenGL QtGui
qt_EX_LIB  := $(qt_LOC_LIB)
qt_LOC_USE := qtbase qt3support x11 opengl
qt_EX_USE  := $(qt_LOC_USE)
qt_INIT_FUNC := $$(eval $$(call ProductCommonVars,qt,,,qt))

