#
# Set location of various cgtools
#
# These variables can be set here or on the command line.  Paths must not
# have spaces.
#
# The CCS_ARMCOMPILER and GCC_ARMCOMPILER variables, in addition to pointing to
# their respective locations, also serve as "switches" for disabling a build
# using those cgtools. To disable a build using a specific cgtool, either set
# the cgtool's variable to empty or delete/comment-out its definition:
#     CCS_ARMCOMPILER ?=
# or
#     #CCS_ARMCOMPILER ?= home/username/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.1.0.LTS
#
# If a cgtool's *_ARMCOMPILER variable is set (non-empty), various sub-makes
# in the installation will attempt to build with that cgtool.  This means
# that if multiple *_ARMCOMPILER cgtool variables are set, the sub-makes
# will build using each non-empty *_ARMCOMPILER cgtool.
#

XDC_INSTALL_DIR        ?= /home/username/ti/xdctools_3_51_03_28_core
SYSCONFIG_TOOL         ?= /home/username/ti/ccs910/ccs/utils/sysconfig/sysconfig_cli.sh


CCS_ARMCOMPILER        ?= /home/username/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.2.LTS
CLANG_ARMCOMPILER      ?= /path/to/clang/compiler
GCC_ARMCOMPILER        ?= /home/username/ti/ccs910/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major

# The IAR compiler is not supported on Linux
# IAR_ARMCOMPILER      ?=

# For Linux
RM     = rm -f
RMDIR  = rm -rf
DEVNULL = /dev/null
ECHOBLANKLINE = echo
