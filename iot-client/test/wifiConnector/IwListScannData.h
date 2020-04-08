//
// Created by julian on 19.07.18.
//

#ifndef VIEW_IOT_CLIENT_IWLISTSCANNDATA_H
#define VIEW_IOT_CLIENT_IWLISTSCANNDATA_H

#include <string>
#include <sstream>
#include <vector>

class IwListScannData {

public:
    static std::vector<std::string> parseOnlyOneValid() {
        const auto str = R"(wlp3s0    Scan completed :
          Cell 01 - Address: D8:84:66:4A:22:8A
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=47/70  Signal level=-63 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001081db759703
                    Extra: Last beacon: 4584ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 02 - Address: D8:84:66:4A:4B:29
                    Channel:1
                    Frequency:2.412 GHz (Channel 1)
                    Quality=29/70  Signal level=-81 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b8288239817
                    Extra: Last beacon: 4952ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030101
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1601080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 03 - Address: D8:84:66:4A:22:6A
                    Channel:1
                    Frequency:2.412 GHz (Channel 1)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018bdca777dc0
                    Extra: Last beacon: 4952ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030101
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1601080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 04 - Address: D8:84:66:4A:4B:2C
                    Channel:1
                    Frequency:2.412 GHz (Channel 1)
                    Quality=30/70  Signal level=-80 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b828823a3fb
                    Extra: Last beacon: 4948ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030101
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1601080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 05 - Address: D8:84:66:4A:22:6C
                    Channel:1
                    Frequency:2.412 GHz (Channel 1)
                    Quality=30/70  Signal level=-80 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018bdca77836e
                    Extra: Last beacon: 4948ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030101
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1601080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 06 - Address: D8:84:66:4A:4A:E9
                    Channel:6
                    Frequency:2.437 GHz (Channel 6)
                    Quality=41/70  Signal level=-69 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000005fb71c349cb
                    Extra: Last beacon: 4796ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030106
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1606080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 07 - Address: D8:84:66:4A:28:59
                    Channel:6
                    Frequency:2.437 GHz (Channel 6)
                    Quality=33/70  Signal level=-77 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b73796036c8
                    Extra: Last beacon: 4796ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030106
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1606080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 08 - Address: D8:84:66:4A:4A:EA
                    Channel:6
                    Frequency:2.437 GHz (Channel 6)
                    Quality=41/70  Signal level=-69 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000005fb71c34cc8
                    Extra: Last beacon: 4796ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030106
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1606080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 09 - Address: D8:84:66:4A:28:5A
                    Channel:6
                    Frequency:2.437 GHz (Channel 6)
                    Quality=33/70  Signal level=-77 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b73796039c1
                    Extra: Last beacon: 4796ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030106
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1606080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 10 - Address: D8:84:66:4A:4A:EC
                    Channel:6
                    Frequency:2.437 GHz (Channel 6)
                    Quality=42/70  Signal level=-68 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000005fb71c34fbd
                    Extra: Last beacon: 4796ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030106
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1606080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 11 - Address: D8:84:66:4A:28:5C
                    Channel:6
                    Frequency:2.437 GHz (Channel 6)
                    Quality=33/70  Signal level=-77 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b7379603ca6
                    Extra: Last beacon: 4796ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 030106
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1606080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 12 - Address: D8:84:66:4A:22:89
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=47/70  Signal level=-63 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001081db759573
                    Extra: Last beacon: 4584ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 13 - Address: D8:84:66:4A:22:8C
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=48/70  Signal level=-62 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001081db75988d
                    Extra: Last beacon: 4584ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 14 - Address: D8:84:66:4A:22:AC
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=32/70  Signal level=-78 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b7376d3c37b
                    Extra: Last beacon: 4580ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 15 - Address: D8:84:66:4A:24:48
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:on
                    ESSID:""
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018c45f6e52c4
                    Extra: Last beacon: 4580ms ago
                    IE: Unknown: 0000
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 050401020000
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : PSK
          Cell 16 - Address: D8:84:66:4A:24:49
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018c45f6e53e1
                    Extra: Last beacon: 4580ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 050401020000
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 17 - Address: D8:84:66:4A:24:4A
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018c45f6e5e44
                    Extra: Last beacon: 4580ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 18 - Address: D8:84:66:4A:24:4C
                    Channel:11
                    Frequency:2.462 GHz (Channel 11)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018c45f6e5b8c
                    Extra: Last beacon: 4580ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01080C1218243048606C
                    IE: Unknown: 03010B
                    IE: Unknown: 0706444549010D14
                    IE: Unknown: 2A0104
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D160B080400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 19 - Address: D8:84:66:4A:28:51
                    Channel:36
                    Frequency:5.18 GHz (Channel 36)
                    Quality=33/70  Signal level=-77 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b737afde8f6
                    Extra: Last beacon: 4124ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030124
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1624000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 20 - Address: D8:84:66:4A:22:61
                    Channel:36
                    Frequency:5.18 GHz (Channel 36)
                    Quality=26/70  Signal level=-84 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018bdc9cfb632
                    Extra: Last beacon: 4124ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030124
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1624000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 21 - Address: D8:84:66:4A:28:52
                    Channel:36
                    Frequency:5.18 GHz (Channel 36)
                    Quality=34/70  Signal level=-76 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b737afdec35
                    Extra: Last beacon: 4124ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030124
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1624000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 22 - Address: D8:84:66:4A:22:62
                    Channel:36
                    Frequency:5.18 GHz (Channel 36)
                    Quality=25/70  Signal level=-85 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018bdc9cfb96d
                    Extra: Last beacon: 4124ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030124
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1624000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 23 - Address: D8:84:66:4A:28:54
                    Channel:36
                    Frequency:5.18 GHz (Channel 36)
                    Quality=33/70  Signal level=-77 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b737afdef6c
                    Extra: Last beacon: 4124ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030124
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1624000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 24 - Address: D8:84:66:4A:22:64
                    Channel:36
                    Frequency:5.18 GHz (Channel 36)
                    Quality=25/70  Signal level=-85 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000018bdc9cfbc90
                    Extra: Last beacon: 4124ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030124
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1624000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 25 - Address: D8:84:66:4A:4A:E1
                    Channel:40
                    Frequency:5.2 GHz (Channel 40)
                    Quality=35/70  Signal level=-75 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000005fb71aadd06
                    Extra: Last beacon: 4112ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030128
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1628000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 26 - Address: D8:84:66:4A:4A:E2
                    Channel:40
                    Frequency:5.2 GHz (Channel 40)
                    Quality=36/70  Signal level=-74 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000005fb71aae03f
                    Extra: Last beacon: 4112ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030128
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1628000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 27 - Address: D8:84:66:4A:4A:E4
                    Channel:40
                    Frequency:5.2 GHz (Channel 40)
                    Quality=36/70  Signal level=-74 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=000005fb71aae374
                    Extra: Last beacon: 4112ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030128
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1628000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 28 - Address: D8:84:66:4A:22:81
                    Channel:44
                    Frequency:5.22 GHz (Channel 44)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001081de4628d7
                    Extra: Last beacon: 4076ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 03012C
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D162C000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 29 - Address: D8:84:66:4A:22:82
                    Channel:44
                    Frequency:5.22 GHz (Channel 44)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001081de462a88
                    Extra: Last beacon: 4076ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 03012C
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D162C000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 30 - Address: D8:84:66:4A:22:84
                    Channel:44
                    Frequency:5.22 GHz (Channel 44)
                    Quality=31/70  Signal level=-79 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001081de462c32
                    Extra: Last beacon: 4076ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 03012C
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D162C000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
          Cell 31 - Address: D8:84:66:4A:4B:21
                    Channel:48
                    Frequency:5.24 GHz (Channel 48)
                    Quality=23/70  Signal level=-87 dBm
                    Encryption key:on
                    ESSID:"eduroam"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b82898790af
                    Extra: Last beacon: 4060ms ago
                    IE: Unknown: 0007656475726F616D
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030130
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1630000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
                       Preauthentication Supported
          Cell 32 - Address: D8:84:66:4A:4B:22
                    Channel:48
                    Frequency:5.24 GHz (Channel 48)
                    Quality=24/70  Signal level=-86 dBm
                    Encryption key:on
                    ESSID:"FHWS"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b828987925d
                    Extra: Last beacon: 4060ms ago
                    IE: Unknown: 000446485753
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030130
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1630000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000200000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
                    IE: IEEE 802.11i/WPA2 Version 1
                        Group Cipher : CCMP
                        Pairwise Ciphers (1) : CCMP
                        Authentication Suites (1) : 802.1x
          Cell 33 - Address: D8:84:66:4A:4B:24
                    Channel:48
                    Frequency:5.24 GHz (Channel 48)
                    Quality=22/70  Signal level=-88 dBm
                    Encryption key:off
                    ESSID:"FHWS-Hotspot"
                    Bit Rates:6 Mb/s; 9 Mb/s; 12 Mb/s; 18 Mb/s; 24 Mb/s
                              36 Mb/s; 48 Mb/s; 54 Mb/s
                    Mode:Master
                    Extra:tsf=00001b828987940a
                    Extra: Last beacon: 4060ms ago
                    IE: Unknown: 000C464857532D486F7473706F74
                    IE: Unknown: 01088C129824B048606C
                    IE: Unknown: 030130
                    IE: Unknown: 070A444549240817640B1E00
                    IE: Unknown: 2D1A2D0803FFFFFFFF00000000000000000000000000000000000000
                    IE: Unknown: 3D1630000400000000000000000000000000000000000000
                    IE: Unknown: 7F080010000000000040
                    IE: Unknown: BF0C32708033AAFF0000AAFF0000
                    IE: Unknown: C005000000FCFF
                    IE: Unknown: DD180050F2020101000003A4000027A4000042435E0062322F00
)";

        return toVector(str);

    }

private:

    static std::vector<std::string> toVector(const std::string &str) {
        std::istringstream iss(str);

        std::string line;
        std::vector<std::string> lines;

        while (std::getline(iss, line)) {
            lines.push_back(line);
        }

        return lines;
    }

};

#endif //VIEW_IOT_CLIENT_IWLISTSCANNDATA_H
