# Hardware Control
This folder holds code relating to the hardware control parts of the project (angle positioning, calibration, etc.). Most code here will probably be written in C/C++ for Arduino or ESP32.

### Control codes
`pos` (get position) returns position
- Returns `pos OK (aa.aa, zzz.zz)` Where aaa.aa represents the altitude (0=horizon, 90=vertical), and zzz.zz represents azimuth (North=0, East=90, etc.)

`set (x, y)` (set position) sets a position
- Returns `set OK` when command is received

`trace (x1, y1, x2, y2, time)` traces out a sky line from (x1, x2) to (y1, y2) over time
- Returns `trace OK` when command is received

All messages end in newline (enter).

 
