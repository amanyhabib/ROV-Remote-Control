import serial
import time
import sys
import termios
import tty

# Set up serial communication with the Arduino (adjust the port and baud rate)
arduino_port = '/dev/ttyUSB0'  # Modify with your actual serial port (can also be /dev/ttyACM0)
baud_rate = 9600
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

# Function to capture key presses
def get_key():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

# Function to send command to Arduino
def send_command(command):
    print(f"Sending command: {command}")
    ser.write(command.encode())

# Main control loop
def main():
    print("Control ROV:")
    print("W - Move Forward")
    print("S - Move Backward")
    print("A - Turn Left")
    print("D - Turn Right")
    print("U - Move Up (Vertical)")
    print("Q - Move Down (Vertical)")
    print("X - Stop")

    try:
        while True:
            key = get_key()  # Capture a key press
            if key == 'w' or key == 'W':
                send_command('w')  # Forward
            elif key == 's' or key == 'S':
                send_command('s')  # Backward
            elif key == 'a' or key == 'A':
                send_command('a')  # Left
            elif key == 'd' or key == 'D':
                send_command('d')  # Right
            elif key == 'u' or key == 'U':
                send_command('u')  # Up (Vertical)
            elif key == 'q' or key == 'Q':
                send_command('q')  # Down (Vertical)
            elif key == 'x' or key == 'X':
                send_command('x')  # Stop
            elif key == 'q':  # Quit the program
                print("Exiting...")
                break
            else:
                print("Unknown command")
            
            time.sleep(0.1)

    except KeyboardInterrupt:
        print("Program interrupted. Exiting...")
        ser.close()
        sys.exit()

if __name__ == '__main__':
    main()
