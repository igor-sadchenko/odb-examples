# file      : makefile
# author    : Boris Kolpackov <boris@codesynthesis.com>
# copyright : Copyright (c) 2009-2010 Code Synthesis Tools CC
# license   : GNU GPL; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))build/bootstrap.make

dirs := hello query mapping template
dist_dirs := $(filter-out template,$(dirs))

default := $(out_base)/
dist    := $(out_base)/.dist
test    := $(out_base)/.test
clean   := $(out_base)/.clean

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(dirs)))

$(dist): name := examples
$(dist): export dirs := $(dist_dirs)
$(dist): data_dist := GPLv2 LICENSE README NEWS version tester.bat \
mysql-driver.bat mysql.options
$(dist): exec_dist := bootstrap tester
$(dist): export extra_dist := $(data_dist) $(exec_dist) test.bat \
$(call vc9slns,$(name)) $(call vc10slns,$(name))
$(dist): export version = $(shell cat $(src_root)/version)

$(dist): $(addprefix $(out_base)/,$(addsuffix /.dist,$(dist_dirs)))
	$(call dist-data,$(data_dist))
	$(call dist-exec,$(exec_dist))
	$(call dist-dir,m4)
	$(call meta-automake)
	$(call meta-autoconf)
	$(call meta-vc9slns,$(name))
	$(call meta-vc10slns,$(name))
	$(call meta-vctest,$(name)-mysql-vc10.sln,test.bat)

$(test): $(addprefix $(out_base)/,$(addsuffix /.test,$(dirs)))
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(dirs)))

$(call include,$(bld_root)/dist.make)
$(call include,$(bld_root)/meta/vc9sln.make)
$(call include,$(bld_root)/meta/vc10sln.make)
$(call include,$(bld_root)/meta/vctest.make)
$(call include,$(bld_root)/meta/automake.make)
$(call include,$(bld_root)/meta/autoconf.make)

$(foreach d,$(dirs),$(call import,$(src_base)/$d/makefile))

