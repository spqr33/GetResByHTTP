OBJECTDIR=${BUILDDIR}/${CONF}/${ARCH}

OBJECTFILES= \
	${OBJECTDIR}/src/Action.o \
	${OBJECTDIR}/src/AHeader.o \
	${OBJECTDIR}/src/Content_Length.o \
	${OBJECTDIR}/src/HeadersHolder.o \
	${OBJECTDIR}/src/HostHeader.o \
	${OBJECTDIR}/src/HTTPRequest.o \
	${OBJECTDIR}/src/HTTPRequestErrorsQueue.o \
	${OBJECTDIR}/src/HTTPRequestQueue.o \
	${OBJECTDIR}/src/HTTPResponse.o \
	${OBJECTDIR}/src/IPAdress.o \
	${OBJECTDIR}/src/JumboBuff.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/QueuesMaster.o \
	${OBJECTDIR}/src/RecvBysocketQueue.o \
	${OBJECTDIR}/src/SaveFile.o \
	${OBJECTDIR}/src/SendBySocketQueue.o \
	${OBJECTDIR}/src/Task.o \
	${OBJECTDIR}/src/TaskHolder.o \
	${OBJECTDIR}/src/URL.o \
	${OBJECTDIR}/src/utils.o \
