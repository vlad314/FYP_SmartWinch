import csv
import serial
import Holding_Registers
import minimalmodbus

# enter settings here
winch_id = 1
port_name = 'COM8'
number_of_waypoints = 8
dwell_time = 1



connected = 0
instrument = minimalmodbus
failed_transmission = 0
try:
    instrument = minimalmodbus.Instrument(port_name , winch_id) 
    instrument.serial.baudrate = 115200   # Baudrate
    instrument.serial.bytesize = 8
    instrument.serial.parity   = serial.PARITY_NONE
    instrument.serial.stopbits = 1
    instrument.serial.timeout  = 0.5   # seconds
    instrument.address = winch_id    # this is the slave address number
    instrument.mode = minimalmodbus.MODE_RTU   # rtu or ascii mode
    instrument.debug = False

    if (instrument.serial.is_open == False):
        instrument.serial.open()

    print str(instrument) + '\n\n'
    print "Connection OK."
    
    connected = 1
except:
    print "Connection failed."
    connected = 0



if connected:
    try:
        instrument.write_register(Holding_Registers.Map.Number_of_Waypoints, number_of_waypoints, numberOfDecimals=0, functioncode=16, signed=True)
        instrument.write_register(Holding_Registers.Map.Dwell_Time, dwell_time, numberOfDecimals=0, functioncode=16, signed=True)
        print "Number of waypoint and dwell time sent OK."
    except:    
        print "Number of waypoint and dwell time sent NOT OK."
        failed_transmission = 1
        
    with open('waypoints.csv', 'r') as waypoints:
        waypoints_reader = csv.reader(waypoints)
        next (waypoints_reader) # used to skip the label
        rows = list(waypoints_reader)

        for index in range(0, number_of_waypoints):
            try:
                instrument.write_registers(Holding_Registers.Map.X1+(index*3), [int(rows[index][0]), int(rows[index][1]), int(rows[index][2])])
                print "Waypoint " + str(index) + " OK\t\t" + str(rows[index])
            except:
                print "Waypoint " + str(index) + "NOK\t\t" + str(rows[index])
                failed_transmission = 1



if connected:
    try:
        instrument.serial.close()
        print "Disconnected."
    except:
        print "Disconnect failed." 

if failed_transmission:
    print "Upload Failed."
else:
    print "Upload successful."

