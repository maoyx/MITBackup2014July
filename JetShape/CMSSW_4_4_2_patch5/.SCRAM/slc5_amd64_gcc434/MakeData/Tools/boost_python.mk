boost_python             := boost_python
ALL_TOOLS      += boost_python
boost_python_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/external/boost/1.44.0-cms3/include
boost_python_EX_INCLUDE  := $(boost_python_LOC_INCLUDE)
boost_python_LOC_LIB := boost_python
boost_python_EX_LIB  := $(boost_python_LOC_LIB)
boost_python_LOC_USE := elementtree gccxml python
boost_python_EX_USE  := $(boost_python_LOC_USE)
boost_python_INIT_FUNC := $$(eval $$(call ProductCommonVars,boost_python,,,boost_python))

