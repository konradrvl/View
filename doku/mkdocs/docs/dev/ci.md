# Continuous integration

Für das Projekt wird [Visual Studio Team Services](https://visualstudio.microsoft.com/de/team-services/) als Continuous integration Platform genutzt.

Dies bietet uns einige Vorteile:

+ Automatisiertes Builds beim pushen
+ Automatisiertes Cross-Compiling
+ Automatisiertes erstellen von Installationspaketen

## Automatisches Buildsystem

### Server

Der Server wird nach jedem push bei welchem im Ordner `/server` eine Änderung geschehen ist, vom Buildsystem neu gebaut. Es werden automatisch Pakete für linux-x64, linux-arm (deb, rpm, tar.gz) und windows-x64 (zip) erstellt. Diese Pakete enthalten die Anwendung mit allen Abhängigkeiten inklusive dem .Net Core Freamwork und können direkt unter den entsprechenden Platformen ausgeführt und installiert werden.

Ablauf:

1. View Frontend Artefakte herunterladen
2. `dotnet restore`
3. `dotnet build`
4. Pakete für alle Platformen mithilfe von [dotnet-packaging](https://github.com/qmfrederik/dotnet-packaging) erstellen.
   Beispiel: `dotnet deb -f netcoreapp2.1 -r linux-x64 -c release`

### IoT-Device

Die IoT-Software wird nach jedem push bei welchem im Ordner `/iot-device` eine Änderung geschehen ist, vom Buildsystem neu gebaut. Es werden automatisch Pakete für linux-amd64 (deb, rpm), linux-armhf (deb) und win-64 (zip) erstellt. Diese Pakete enthalten die Anwendung mit allen Abhängigkeiten und können direkt unter den entsprechenden Platformen ausgeführt und installiert werden.

Ablauf:

1. YOLO Weights und Daten kopieren
2. WiFi-Frontend Artefakte herunterladen
3. Im Ordner build: `cmake -DCMAKE_BUILD_TYPE=Release -DBoost_USE_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF ..` (`-DCMAKE_TOOLCHAIN_FILE=/home/winter/armhf-toolchain.cmake` bei linux-armhf), (`-DCMAKE_TOOLCHAIN_FILE=/home/winter/mingw-w64-toolchain.cmake` bei windows-x86_64)
4. `cmake --build .`
5. `cpack -G DEB` (`-D CPACK_DEBIAN_PACKAGE_ARCHITECTURE=armhf` bei armhf) (nur für linux)
6. `cpack -G RPM` (nur unter linux-amd64)
7. `cpack -G ZIP` (nur unter win-64)

Das Toolchainfile für linux-armhf sieht wie folgt aus:

```
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_NAME Linux)
set(TOOLCHAIN_PREFIX arm-linux-gnueabihf)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

Das Toolchainfile für win-64 setzt: `set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)`