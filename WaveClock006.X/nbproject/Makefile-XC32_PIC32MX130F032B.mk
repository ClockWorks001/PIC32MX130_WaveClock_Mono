#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-XC32_PIC32MX130F032B.mk)" "nbproject/Makefile-local-XC32_PIC32MX130F032B.mk"
include nbproject/Makefile-local-XC32_PIC32MX130F032B.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=XC32_PIC32MX130F032B
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=exceptions.c interrupts.c main.c system.c user.c mmc.c pff.c vRTCC_lib.c vTimer1_lib.c vUSART_CMND_lib.c vUSART_Menu_lib.c vWave_lib.c xprintf.c vWait_lib.c vLcd_I2C_lib.c vSwitch_Menu_lib.c vLcd_Out_lib.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/exceptions.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/user.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/pff.o ${OBJECTDIR}/vRTCC_lib.o ${OBJECTDIR}/vTimer1_lib.o ${OBJECTDIR}/vUSART_CMND_lib.o ${OBJECTDIR}/vUSART_Menu_lib.o ${OBJECTDIR}/vWave_lib.o ${OBJECTDIR}/xprintf.o ${OBJECTDIR}/vWait_lib.o ${OBJECTDIR}/vLcd_I2C_lib.o ${OBJECTDIR}/vSwitch_Menu_lib.o ${OBJECTDIR}/vLcd_Out_lib.o
POSSIBLE_DEPFILES=${OBJECTDIR}/exceptions.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/user.o.d ${OBJECTDIR}/mmc.o.d ${OBJECTDIR}/pff.o.d ${OBJECTDIR}/vRTCC_lib.o.d ${OBJECTDIR}/vTimer1_lib.o.d ${OBJECTDIR}/vUSART_CMND_lib.o.d ${OBJECTDIR}/vUSART_Menu_lib.o.d ${OBJECTDIR}/vWave_lib.o.d ${OBJECTDIR}/xprintf.o.d ${OBJECTDIR}/vWait_lib.o.d ${OBJECTDIR}/vLcd_I2C_lib.o.d ${OBJECTDIR}/vSwitch_Menu_lib.o.d ${OBJECTDIR}/vLcd_Out_lib.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/exceptions.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/user.o ${OBJECTDIR}/mmc.o ${OBJECTDIR}/pff.o ${OBJECTDIR}/vRTCC_lib.o ${OBJECTDIR}/vTimer1_lib.o ${OBJECTDIR}/vUSART_CMND_lib.o ${OBJECTDIR}/vUSART_Menu_lib.o ${OBJECTDIR}/vWave_lib.o ${OBJECTDIR}/xprintf.o ${OBJECTDIR}/vWait_lib.o ${OBJECTDIR}/vLcd_I2C_lib.o ${OBJECTDIR}/vSwitch_Menu_lib.o ${OBJECTDIR}/vLcd_Out_lib.o

# Source Files
SOURCEFILES=exceptions.c interrupts.c main.c system.c user.c mmc.c pff.c vRTCC_lib.c vTimer1_lib.c vUSART_CMND_lib.c vUSART_Menu_lib.c vWave_lib.c xprintf.c vWait_lib.c vLcd_I2C_lib.c vSwitch_Menu_lib.c vLcd_Out_lib.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-XC32_PIC32MX130F032B.mk dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX130F064B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/exceptions.o: exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exceptions.o.d 
	@${RM} ${OBJECTDIR}/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/exceptions.o.d" -o ${OBJECTDIR}/exceptions.o exceptions.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/interrupts.o.d" -o ${OBJECTDIR}/interrupts.o interrupts.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/system.o.d" -o ${OBJECTDIR}/system.o system.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/user.o.d" -o ${OBJECTDIR}/user.o user.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mmc.o: mmc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	@${FIXDEPS} "${OBJECTDIR}/mmc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/pff.o: pff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pff.o.d 
	@${RM} ${OBJECTDIR}/pff.o 
	@${FIXDEPS} "${OBJECTDIR}/pff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/pff.o.d" -o ${OBJECTDIR}/pff.o pff.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vRTCC_lib.o: vRTCC_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vRTCC_lib.o.d 
	@${RM} ${OBJECTDIR}/vRTCC_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vRTCC_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vRTCC_lib.o.d" -o ${OBJECTDIR}/vRTCC_lib.o vRTCC_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vTimer1_lib.o: vTimer1_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vTimer1_lib.o.d 
	@${RM} ${OBJECTDIR}/vTimer1_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vTimer1_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vTimer1_lib.o.d" -o ${OBJECTDIR}/vTimer1_lib.o vTimer1_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vUSART_CMND_lib.o: vUSART_CMND_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vUSART_CMND_lib.o.d 
	@${RM} ${OBJECTDIR}/vUSART_CMND_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vUSART_CMND_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vUSART_CMND_lib.o.d" -o ${OBJECTDIR}/vUSART_CMND_lib.o vUSART_CMND_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vUSART_Menu_lib.o: vUSART_Menu_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vUSART_Menu_lib.o.d 
	@${RM} ${OBJECTDIR}/vUSART_Menu_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vUSART_Menu_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vUSART_Menu_lib.o.d" -o ${OBJECTDIR}/vUSART_Menu_lib.o vUSART_Menu_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vWave_lib.o: vWave_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vWave_lib.o.d 
	@${RM} ${OBJECTDIR}/vWave_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vWave_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vWave_lib.o.d" -o ${OBJECTDIR}/vWave_lib.o vWave_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/xprintf.o: xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/xprintf.o.d 
	@${RM} ${OBJECTDIR}/xprintf.o 
	@${FIXDEPS} "${OBJECTDIR}/xprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/xprintf.o.d" -o ${OBJECTDIR}/xprintf.o xprintf.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vWait_lib.o: vWait_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vWait_lib.o.d 
	@${RM} ${OBJECTDIR}/vWait_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vWait_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vWait_lib.o.d" -o ${OBJECTDIR}/vWait_lib.o vWait_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vLcd_I2C_lib.o: vLcd_I2C_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vLcd_I2C_lib.o.d 
	@${RM} ${OBJECTDIR}/vLcd_I2C_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vLcd_I2C_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vLcd_I2C_lib.o.d" -o ${OBJECTDIR}/vLcd_I2C_lib.o vLcd_I2C_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vSwitch_Menu_lib.o: vSwitch_Menu_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vSwitch_Menu_lib.o.d 
	@${RM} ${OBJECTDIR}/vSwitch_Menu_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vSwitch_Menu_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vSwitch_Menu_lib.o.d" -o ${OBJECTDIR}/vSwitch_Menu_lib.o vSwitch_Menu_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vLcd_Out_lib.o: vLcd_Out_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vLcd_Out_lib.o.d 
	@${RM} ${OBJECTDIR}/vLcd_Out_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vLcd_Out_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vLcd_Out_lib.o.d" -o ${OBJECTDIR}/vLcd_Out_lib.o vLcd_Out_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/exceptions.o: exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/exceptions.o.d 
	@${RM} ${OBJECTDIR}/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/exceptions.o.d" -o ${OBJECTDIR}/exceptions.o exceptions.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/interrupts.o.d" -o ${OBJECTDIR}/interrupts.o interrupts.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/system.o.d" -o ${OBJECTDIR}/system.o system.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/user.o.d 
	@${RM} ${OBJECTDIR}/user.o 
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/user.o.d" -o ${OBJECTDIR}/user.o user.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/mmc.o: mmc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/mmc.o.d 
	@${RM} ${OBJECTDIR}/mmc.o 
	@${FIXDEPS} "${OBJECTDIR}/mmc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/mmc.o.d" -o ${OBJECTDIR}/mmc.o mmc.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/pff.o: pff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/pff.o.d 
	@${RM} ${OBJECTDIR}/pff.o 
	@${FIXDEPS} "${OBJECTDIR}/pff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/pff.o.d" -o ${OBJECTDIR}/pff.o pff.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vRTCC_lib.o: vRTCC_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vRTCC_lib.o.d 
	@${RM} ${OBJECTDIR}/vRTCC_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vRTCC_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vRTCC_lib.o.d" -o ${OBJECTDIR}/vRTCC_lib.o vRTCC_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vTimer1_lib.o: vTimer1_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vTimer1_lib.o.d 
	@${RM} ${OBJECTDIR}/vTimer1_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vTimer1_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vTimer1_lib.o.d" -o ${OBJECTDIR}/vTimer1_lib.o vTimer1_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vUSART_CMND_lib.o: vUSART_CMND_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vUSART_CMND_lib.o.d 
	@${RM} ${OBJECTDIR}/vUSART_CMND_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vUSART_CMND_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vUSART_CMND_lib.o.d" -o ${OBJECTDIR}/vUSART_CMND_lib.o vUSART_CMND_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vUSART_Menu_lib.o: vUSART_Menu_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vUSART_Menu_lib.o.d 
	@${RM} ${OBJECTDIR}/vUSART_Menu_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vUSART_Menu_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vUSART_Menu_lib.o.d" -o ${OBJECTDIR}/vUSART_Menu_lib.o vUSART_Menu_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vWave_lib.o: vWave_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vWave_lib.o.d 
	@${RM} ${OBJECTDIR}/vWave_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vWave_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vWave_lib.o.d" -o ${OBJECTDIR}/vWave_lib.o vWave_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/xprintf.o: xprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/xprintf.o.d 
	@${RM} ${OBJECTDIR}/xprintf.o 
	@${FIXDEPS} "${OBJECTDIR}/xprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/xprintf.o.d" -o ${OBJECTDIR}/xprintf.o xprintf.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vWait_lib.o: vWait_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vWait_lib.o.d 
	@${RM} ${OBJECTDIR}/vWait_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vWait_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vWait_lib.o.d" -o ${OBJECTDIR}/vWait_lib.o vWait_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vLcd_I2C_lib.o: vLcd_I2C_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vLcd_I2C_lib.o.d 
	@${RM} ${OBJECTDIR}/vLcd_I2C_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vLcd_I2C_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vLcd_I2C_lib.o.d" -o ${OBJECTDIR}/vLcd_I2C_lib.o vLcd_I2C_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vSwitch_Menu_lib.o: vSwitch_Menu_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vSwitch_Menu_lib.o.d 
	@${RM} ${OBJECTDIR}/vSwitch_Menu_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vSwitch_Menu_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vSwitch_Menu_lib.o.d" -o ${OBJECTDIR}/vSwitch_Menu_lib.o vSwitch_Menu_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/vLcd_Out_lib.o: vLcd_Out_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/vLcd_Out_lib.o.d 
	@${RM} ${OBJECTDIR}/vLcd_Out_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/vLcd_Out_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-float -O1 -MMD -MF "${OBJECTDIR}/vLcd_Out_lib.o.d" -o ${OBJECTDIR}/vLcd_Out_lib.o vLcd_Out_lib.c    -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mips16 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--gc-sections
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -Os -mips16 -mno-float -o dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_XC32_PIC32MX130F032B=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/WaveClock006.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/XC32_PIC32MX130F032B
	${RM} -r dist/XC32_PIC32MX130F032B

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
