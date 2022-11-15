rom ephem import *
from datetime import datetime
import time

#getting the current time
today = datetime.today()
now = today.strftime("%Y/%m/%d %H:%M:%S")


#asking for the planet and creating the tracking time
AB = str.lower(input("What astral body do you want to analyze? (Planets in solar system only) "))
how_long = int(input("How long do you want to track the body? "))
time_unit = str.lower(input("Unit of time?" ))
wait = 0
if time_unit == "hours":
        how_long = (how_long * 3600)
elif time_unit == "minutes":
        how_long = (how_long * 60)
print("\n")

#defining observer position and time with the obvPos class
obvPos = Observer()
obvPos.elevation = 1325
obvPos.lat = 38.47273523
obvPos.lon = -78.8818049
obvPos.date = now


#all of the planets
if AB == "mercury":
        m = Mercury()
        m2 = Mercury(obvPos)
        print("Mercury ALTITUDE: " + str(m2.alt))
        print("Mercury AZIMUTH: " + str(m2.az))
        time.sleep(wait)
        for t in range(0, how_long):
                today = datetime.today()
                now = today.strftime("%Y/%m/%d %H:%M:%S")
                obvPos.date = now
                m2 = Mercury(obvPos)
                print(str(m2.alt))
                print(str(m2.az))
                time.sleep(1)
                print("\n")
 
 venus
elif AB == "venus":
        v = Venus()
        v2 = Venus(obvPos)
        print("Venus ALTITUDE: " + str(v2.alt))
        print("Venus AZIMUTH: " + str(v2.az))
        time.sleep(wait)
        for t in range(0, how_long):
                today = datetime.today()
                now = today.strftime("%Y/%m/%d %H:%M:%S")
                obvPos.date = now
                v2 = Venus(obvPos)
                print(str(v2.alt))
                print(str(v2.az))
                time.sleep(1)
                print("\n")

#mars
elif AB == "mars":
        m = Mars()
        m2 = Mars(obvPos)
        print("Mars ALTITUDE: " + str(m2.alt))
        print("Mars AZIMUTH: " + str(m2.az))
        time.sleep(wait)
        for t in range(0, how_long):
                today = datetime.today()
                now = today.strftime("%Y/%m/%d %H:%M:%S")
                obvPos.date = now
                m2 = Mars(obvPos)
                print(str(m2.alt))
                print(str(m2.az))
                time.sleep(1)
                print("\n")
                
lif AB == "jupiter":
        j = Jupiter()
        j2 = Jupiter(obvPos)
        print("Jupiter ALTITUDE: " + str(j2.alt))
        print("Juptier AZIMUTH: " + str(j2.az))
        time.sleep(wait)
        for t in range(0, how_long):
                today = datetime.today()
                now = today.strftime("%Y/%m/%d %H:%M:%S")
                obvPos.date = now
                j2 = Jupiter(obvPos)
                print(str(j2.alt))
                print(str(j2.az))
                time.sleep(1)
                print("\n")


#saturn
elif AB == "saturn":
        s = Saturn()
        s2 = Saturn(obvPos)
        print("Saturn ALTITUDE: " + str(s2.alt))
        print("Saturn AZIMUTH: " + str(s2.az))
        time.sleep(wait)
        for t in range(0, how_long):
                today = datetime.today()
                now = today.strftime("%Y/%m/%d %H:%M:%S")
                obvPos.date = now
                s2 = Saturn(obvPos)
                print(str(s2.alt))
                print(str(s2.az))
                time.sleep(1)
                print("\n")
                

#neptune tracking
elif AB == "neptune":
        n = Neptune()
        n2 = Neptune(obvPos)
        print("Neptune ALTITUDE: " + str(n2.alt))
        print("Netune AZIMUTH: " + str(n2.az))
        time.sleep(wait)
        for t in range(0, how_long):
                today = datetime.today()
                now = today.strftime("%Y/%m/%d %H:%M:%S")
                obvPos.date = now
                n2 = Neptune(obvPos)
                print(str(n2.alt))
                print(str(n2.az))
                time.sleep(1)
                print("\n")



