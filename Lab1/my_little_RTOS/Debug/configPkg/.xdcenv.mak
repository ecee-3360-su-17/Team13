#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /Users/yushen/ti/tirtos_tivac_2_16_00_08/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;/Applications/ti/ccsv7/ccs_base
override XDCROOT = /Users/yushen/ti/xdctools_3_32_00_06_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /Users/yushen/ti/tirtos_tivac_2_16_00_08/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/tidrivers_tivac_2_16_00_08/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/bios_6_45_01_29/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/ndk_2_25_00_09/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/uia_2_00_05_50/packages;/Users/yushen/ti/tirtos_tivac_2_16_00_08/products/ns_1_11_00_10/packages;/Applications/ti/ccsv7/ccs_base;/Users/yushen/ti/xdctools_3_32_00_06_core/packages;..
HOSTOS = MacOS
endif
