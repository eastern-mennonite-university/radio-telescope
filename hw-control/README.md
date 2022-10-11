# Hardware Control
This folder holds code relating to the hardware control parts of the project (angle positioning, calibration, etc.). Most code here will probably be written in C/C++ for Arduino or ESP32.

### Control codes
`pos` (get position) returns position
- Returns `pos OK (aa.aa, zzz.zz)` Where aaa.aa represents the altitude (0=horizon, 90=vertical), and zzz.zz represents azimuth (North=0, East=90, etc.)

`set (aa.aa, zzz.zz)` (set position) sets a position
- Returns `set OK` when command is received

`trace (aa.aa, zzz.zz, AA.AA, ZZZ.ZZ, time)` traces out a sky line from (a, z) to (A, Z) over time seconds
- Returns `trace OK` when command is received

All messages end in newline (enter).

 
