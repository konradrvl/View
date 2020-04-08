# IoT-Software compilieren

Bei der IoT-Software handelt es sich um ein eine in C++ geschriebene Anwendung.

## Voraussetzungen

Die IoT-Software ist plattformunabhängig und sollte auf allen gängigen Betriebssystemen lauffähig sein.
Getestet wurden Linux und Windows.

Das Wifi-connect Modul funktioniert nur unter Linux und wird unter Windows nicht in die Anwendung gelinkt.

### Compiler

Ein C++14 fähiger Compiler.
Getestet wurden:

+ [GCC (auch MinGW) >= 5.4](https://gcc.gnu.org/)
+ [Clang 6.0](https://clang.llvm.org/)
+ Microsoft Visual C++ 2017

### Bibliotheken

+ [Boost Filesystem >= 1.61](https://www.boost.org/)
+ [OpenCV >= 3.3.1](https://opencv.org/)
+ [Für die Tests: Google Test](https://github.com/google/googletest)

## Buildsystem

+ [CMake >= 3.5](https://cmake.org/)

## Compilieren

+ Im Ordner iot-device einen Ordner `build` erstellen
+ `cd build`
+ `cmake ..`
+ `cmake --build .`

## Buildoptionen

Die folgenden Buildoptionen können mit `-D` beim CMake Aufruf angegeben werden.
Beispiel: `cmake -D WITH_WIFI_CONNECTOR=OFF ..`

| Option              | Wert   | Bedeutung                                                                       |
| ------------------- | ------ | ------------------------------------------------------------------------------- |
| WITH_WIFI_CONNECTOR | ON OFF | Gibt an, ob der Wifi Connector mitgebaut werden soll. Nur unter Linux verfügbar. |
| BUILD_SHARED_LIBS | ON OFF| Gibt an, ob die internen Bibliotheken und Abhängigkeiten dynamisch oder statisch in die entstehende executable gelinkt werden. |
| WITH_TESTS | ON OFF | Gibt an, ob die Unit Tests gebaut werden. |