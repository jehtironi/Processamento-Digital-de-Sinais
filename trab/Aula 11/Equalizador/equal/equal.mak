# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     equal_Debug
#     equal_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files (x86)\Analog Devices\VisualDSP 5.1.2


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "equal_Debug" configuration
#

ifeq ($(MAKECMDGOALS),equal_Debug)

equal_Debug : ./Debug/equal.dxe 

Debug/equal.doj :equal.c $(VDSP)/Blackfin/include/stdio.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/cycles.h $(VDSP)/Blackfin/include/xcycle_count.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/cycle_count_bf.h coefPB.dat coefPA.dat coefPF.dat 
	@echo ".\equal.c"
	$(VDSP)/ccblkfn.exe -c .\equal.c -file-attr ProjectName=equal -g -structs-do-not-overlap -no-multiline -D DO_CYCLE_COUNTS -double-size-32 -decls-strong -warn-protos -proc ADSP-BF533 -o .\Debug\equal.doj -MM

./Debug/equal.dxe :$(VDSP)/Blackfin/ldf/adsp-BF533.ldf $(VDSP)/Blackfin/lib/bf532_rev_0.5/crtsf532y.doj ./Debug/equal.doj $(VDSP)/Blackfin/lib/bf532_rev_0.5/__initsbsz532.doj $(VDSP)/Blackfin/lib/cplbtab533.doj $(VDSP)/Blackfin/lib/bf532_rev_0.5/crtn532y.doj $(VDSP)/Blackfin/lib/bf532_rev_0.5/libsmall532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libio532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libc532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/librt_fileio532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libevent532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libcpp532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libf64ieee532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libdsp532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libsftflt532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libetsi532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/Debug/libssl532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/Debug/libdrv532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/Debug/libusb532y.dlb $(VDSP)/Blackfin/lib/bf532_rev_0.5/libprofile532y.dlb 
	@echo "Linking..."
	$(VDSP)/ccblkfn.exe .\Debug\equal.doj -L .\Debug -add-debug-libpaths -flags-link -od,.\Debug -o .\Debug\equal.dxe -proc ADSP-BF533 -MM

endif

ifeq ($(MAKECMDGOALS),equal_Debug_clean)

equal_Debug_clean:
	-$(RM) "Debug\equal.doj"
	-$(RM) ".\Debug\equal.dxe"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


