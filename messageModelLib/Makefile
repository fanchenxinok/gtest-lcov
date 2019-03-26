XX = g++
AR = ar
ARFLAG = -rcs
# ��̬�����ӳ�.so��̬�⣬���뾲̬���ʱ����Ҫ�� -fPIC���������
CFLAGS = -g -fPIC

STATIC_LIBS = -lSender -lReceiver -lResponser -lListener -lLogout
#CLIBS = $(addprefix -L./lib/,$(STATIC_LIBS))
#CLIBS += -lpthread -lrt
CLIBS = -L./lib -lSender -lReceiver -lResponser -lListener -lLogout -lpthread -lrt

SUBDIRS = ./logout ./receiver ./responser ./sender ./listener 
 # INCLUDE = a.h b.h ... can't be defined like "INCLUDE = ./*.h"
INCLUDES = $(wildcard ./include/*.h ./sender/*.h ./receiver/*.h ./responser/*.h)
#ָ��ͷ�ļ�Ŀ¼�������оͲ���Ҫ��ͷ�ļ�������·��д������
INCLUDE_DIRS = -I./include -I./sender/ -I./receiver/ -I./responser/ -I./listener -I./logout 

OBJECTS = mainApi.o

export XX CFLAGS AR ARFLAG

TARGET = libSendMsgModel.so          


$(TARGET) : $(OBJECTS) $(SUBDIRS)
	$(XX) -shared -fPIC $< -o $@ $(CLIBS)     # $< ��ʾ�����б��ĵ�һ�� Ҳ���� $(OBJECTS)
	cp $@ ../lib
	sudo cp $@ /usr/lib
	
$(OBJECTS) : %.o : %.cpp 
	$(XX) -c $(CFLAGS) $< -o $@ $(INCLUDE_DIRS)
	
$(SUBDIRS):ECHO
	+$(MAKE) -C $@

ECHO:
	@echo $(SUBDIRS)
	@echo begin compile

.PHONY : clean
clean:
	for dir in $(SUBDIRS);\
	do $(MAKE) -C $$dir clean||exit 1;\
	done
	rm -rf libSendMsgModel* $(OBJECTS)  ./lib/*.a