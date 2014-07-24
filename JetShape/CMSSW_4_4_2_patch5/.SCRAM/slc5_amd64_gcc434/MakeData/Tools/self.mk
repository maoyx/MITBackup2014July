self             := self
ALL_TOOLS      += self
self_LOC_INCLUDE := /osg/app/cmssoft/cms/slc5_amd64_gcc434/cms/cmssw-patch/CMSSW_4_4_2_patch5/src /osg/app/cmssoft/cms/slc5_amd64_gcc434/cms/cmssw-patch/CMSSW_4_4_2_patch5/include
self_EX_INCLUDE  := $(self_LOC_INCLUDE)
self_LOC_LIBDIR := /osg/app/cmssoft/cms/slc5_amd64_gcc434/cms/cmssw-patch/CMSSW_4_4_2_patch5/lib/slc5_amd64_gcc434 /osg/app/cmssoft/cms/slc5_amd64_gcc434/cms/cmssw-patch/CMSSW_4_4_2_patch5/external/slc5_amd64_gcc434/lib
self_EX_LIBDIR  := $(self_LOC_LIBDIR)
self_LOC_LIBDIR += $(cmssw_EX_LIBDIR)
self_EX_LIBDIR  += $(cmssw_EX_LIBDIR)
self_LOC_FLAGS_SYMLINK_DEPTH_CMSSW_SEARCH_PATH  := 2
self_EX_FLAGS_SYMLINK_DEPTH_CMSSW_SEARCH_PATH   := $(self_LOC_FLAGS_SYMLINK_DEPTH_CMSSW_SEARCH_PATH)
self_LOC_FLAGS_SKIP_TOOLS_SYMLINK  := cxxcompiler ccompiler
self_EX_FLAGS_SKIP_TOOLS_SYMLINK   := $(self_LOC_FLAGS_SKIP_TOOLS_SYMLINK)
self_LOC_FLAGS_EXTERNAL_SYMLINK  := PATH LIBDIR CMSSW_SEARCH_PATH
self_EX_FLAGS_EXTERNAL_SYMLINK   := $(self_LOC_FLAGS_EXTERNAL_SYMLINK)
self_LOC_FLAGS_NO_EXTERNAL_RUNTIME  := LD_LIBRARY_PATH PATH CMSSW_SEARCH_PATH
self_EX_FLAGS_NO_EXTERNAL_RUNTIME   := $(self_LOC_FLAGS_NO_EXTERNAL_RUNTIME)
self_INIT_FUNC := $$(eval $$(call ProductCommonVars,self,,20000,self))

