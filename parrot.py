import olympe
from olympe.messages.skyctrl.CoPiloting import setPilotingSource
from olympe.messages.skyctrl.CoPilotingState import pilotingSource
from olympe.messages.ardrone3.PilotingState import PositionChanged
from olympe.messages.ardrone3.GPSSettingsState import GPSFixStateChanged
from olympe.messages.ardrone3.GPSSettingsState import HomeChanged
import time

SKYCTRL_IP = "192.168.53.1"

if __name__ == "__main__":
    drone = olympe.Drone(SKYCTRL_IP)
    drone.connect()
    drone(setPilotingSource(0)).wait()

    #print("Piloting Source : ", drone.get_state(pilotingSource))
    # Wait for GPS fix
    drone(GPSFixStateChanged(_policy = 'wait'))

    
    print("GPS position before take-off :", drone.get_state(HomeChanged))
    o_alt = ""
    o_lat = "0.0"
    o_lon = "0.0"

    while True:
        #drone(PCMD(1, 1, 1, 1, 2, 0))
        print(" --- Current GPS Position --- ")
        alt = drone.get_state(PositionChanged)['altitude']
        print("Altitude : ", alt )
        lat = drone.get_state(PositionChanged)['latitude']
        print("Latitude : ", lat)
        lon = drone.get_state(PositionChanged)['longitude']
        print("Longitude : ", lon)

        if abs(float(lon) - float(o_lon)) >= 1e-5 or abs(float(lat) - float(o_lat)) >= 1e-5:
            # Update the database. Using the SQL database, the given entry will be updated  

            # Clear the file content
            f = open("data/drones.txt", "w+")
            
            #f.write("- \n") Separate each vehicle data with the '-' character in case we have several vehicles

            # Write the current location data to the file
            f.write("Type : Parrot \n")
            f.write("ID : TJNKR \n")
            f.write("Alt : %.2f\n"%(float(alt)))
            f.write("Lat : %s\n"%(lat))
            f.write("Lon : %s\n"%(lon))
            o_lat = lat
            o_lon = lon
            f.close()
        time.sleep(0.5)
    
    drone.disconnect()
    
