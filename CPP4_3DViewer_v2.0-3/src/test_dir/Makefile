.SUFFIXES: .o .cpp .v
CC=g++
CFLAGS=-c -Wall -w -Wextra -std=c++17 -c -pipe -O0 -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_PRINTSUPPORT_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I/usr/include/x86_64-linux-gnu/qt6 -I/usr/include/x86_64-linux-gnu/qt6/QtPrintSupport -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets -I/usr/include/x86_64-linux-gnu/qt6/QtGui -I/usr/include/x86_64-linux-gnu/qt6/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt6/mkspecs/linux-g++
LDFLAGS=-Wl,-O1 -Wl,-rpath-link,/usr/lib/x86_64-linux-gnu
LDFLAGS2=-lgtest -lpthread -lGLX -lOpenGL
GCOVFLAGS := -L. --coverage
SOURCES=test.cpp ../model/model_facade.cpp ../model/normalizer.cpp ../model/parser.cpp ../model/transform.cpp
OBJECTS_TEST=$(SOURCES:.cpp=.o)
OBJECTS_REPORT=$(SOURCES:.cpp=.v)
LIBSOS=/usr/lib/x86_64-linux-gnu/libQt6PrintSupport.so /usr/lib/x86_64-linux-gnu/libQt6Widgets.so /usr/lib/x86_64-linux-gnu/libQt6Gui.so /usr/lib/x86_64-linux-gnu/libGLX.so /usr/lib/x86_64-linux-gnu/libOpenGL.so /usr/lib/x86_64-linux-gnu/libQt6Core.so
EXECUTABLE=test.out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS_TEST) 
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS_TEST) $(LIBSOS) $(LDFLAGS2)

test.v: test.cpp
	$(CC) $(CFLAGS) $< -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.cpp.v:
	$(CC) $(CFLAGS) $< $(GCOVFLAGS) -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS_TEST) $(OBJECTS_REPORT)

gcov_report: $(OBJECTS_REPORT) 
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS_REPORT) $(LIBSOS) $(LDFLAGS2) $(GCOVFLAGS)
