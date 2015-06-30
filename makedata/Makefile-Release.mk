#Debug configuration of GetResByHTTP
#Program Name
PROGNAME=getResByHTTP

#Configuration
CONF=Release
#Macros
ARCH=Linux-x86
DESTDIR=dst
BUILDDIR=bld

#Environment
MKDIR=mkdir
RM=rm
CC=gcc
CCC=g++
CXX=g++

#Compiler Flags
CCFLAGS=-O2 -std=c++0x
CXXFLAGS=-O2 -std=c++0x

#Directory for Object files - OBJECTDIR
#Object Files - OBJECTFILES
#Vars will load from makedata/Makefile-Objectives.mk
include makedata/Makefile-Objectives.mk

JUSTDOIT=.yesJustDoIt

build:	${JUSTDOIT}
	@echo "**************************Build started**************************";
	${MAKE}  -f makedata/Makefile-${CONF}.mk ${DESTDIR}/${CONF}/${ARCH}/${PROGNAME}

${DESTDIR}/${CONF}/${ARCH}/${PROGNAME}: ${OBJECTFILES}
	${MKDIR} -p ${DESTDIR}/${CONF}/${ARCH}
#	linker      	dest			  program_name
	${LINK.cc} -o ${DESTDIR}/${CONF}/${ARCH}/${PROGNAME} ${OBJECTFILES} ${LDLIBSOPTIONS}
	@echo "**************************Build finished*************************";

${OBJECTDIR}/src/Action.o: ./src/Action.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Action.o ./src/Action.cpp
-include ${OBJECTDIR}/src/Action.o.d

${OBJECTDIR}/src/AHeader.o: ./src/AHeader.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AHeader.o ./src/AHeader.cpp
-include ${OBJECTDIR}/src/AHeader.o.d

${OBJECTDIR}/src/Content_Length.o: ./src/Content_Length.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Content_Length.o ./src/Content_Length.cpp
-include ${OBJECTDIR}/src/Content_Length.o.d

${OBJECTDIR}/src/HeadersHolder.o: ./src/HeadersHolder.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HeadersHolder.o ./src/HeadersHolder.cpp
-include ${OBJECTDIR}/src/HeadersHolder.o.d

${OBJECTDIR}/src/HostHeader.o: ./src/HostHeader.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HostHeader.o ./src/HostHeader.cpp
-include ${OBJECTDIR}/src/HostHeader.o.d

${OBJECTDIR}/src/HTTPRequest.o: ./src/HTTPRequest.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPRequest.o ./src/HTTPRequest.cpp
-include ${OBJECTDIR}/src/HTTPRequest.o.d

${OBJECTDIR}/src/HTTPRequestErrorsQueue.o: ./src/HTTPRequestErrorsQueue.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPRequestErrorsQueue.o ./src/HTTPRequestErrorsQueue.cpp
-include ${OBJECTDIR}/src/HTTPRequestErrorsQueue.o.d

${OBJECTDIR}/src/HTTPRequestQueue.o: ./src/HTTPRequestQueue.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPRequestQueue.o ./src/HTTPRequestQueue.cpp
-include ${OBJECTDIR}/src/HTTPRequestQueue.o.d

${OBJECTDIR}/src/HTTPResponse.o: ./src/HTTPResponse.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/HTTPResponse.o ./src/HTTPResponse.cpp
-include ${OBJECTDIR}/src/HTTPResponse.o.d

${OBJECTDIR}/src/IPAdress.o: ./src/IPAdress.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/IPAdress.o ./src/IPAdress.cpp
-include ${OBJECTDIR}/src/IPAdress.o.d

${OBJECTDIR}/src/JumboBuff.o: ./src/JumboBuff.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/JumboBuff.o ./src/JumboBuff.cpp
-include ${OBJECTDIR}/src/JumboBuff.o.d

${OBJECTDIR}/src/main.o: ./src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o ./src/main.cpp
-include ${OBJECTDIR}/src/main.o.d

${OBJECTDIR}/src/QueuesMaster.o: ./src/QueuesMaster.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/QueuesMaster.o ./src/QueuesMaster.cpp
-include ${OBJECTDIR}/src/QueuesMaster.o.d

${OBJECTDIR}/src/RecvBysocketQueue.o: ./src/RecvBysocketQueue.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RecvBysocketQueue.o ./src/RecvBysocketQueue.cpp
-include ${OBJECTDIR}/src/RecvBysocketQueue.o.d

${OBJECTDIR}/src/SaveFile.o: ./src/SaveFile.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SaveFile.o ./src/SaveFile.cpp
-include ${OBJECTDIR}/src/SaveFile.o.d

${OBJECTDIR}/src/SendBySocketQueue.o: ./src/SendBySocketQueue.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SendBySocketQueue.o ./src/SendBySocketQueue.cpp
-include ${OBJECTDIR}/src/SendBySocketQueue.o.d

${OBJECTDIR}/src/Task.o: ./src/Task.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Task.o ./src/Task.cpp
-include ${OBJECTDIR}/src/Task.o.d

${OBJECTDIR}/src/TaskHolder.o: ./src/TaskHolder.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/TaskHolder.o ./src/TaskHolder.cpp
-include ${OBJECTDIR}/src/TaskHolder.o.d

${OBJECTDIR}/src/URL.o: ./src/URL.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/URL.o ./src/URL.cpp
-include ${OBJECTDIR}/src/URL.o.d

${OBJECTDIR}/src/utils.o: ./src/utils.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	@if [ -f $@.d ];\
	then \
		${RM} $@.d ;\
	fi
	$(COMPILE.cc) $(CXXFLAGS) -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/utils.o ./src/utils.cpp
-include ${OBJECTDIR}/src/utils.o.d


.yesJustDoIt:
