
##"Door locker system "🔐🚪


The project is implemented based on a layered architecture model using 2 Microcontroller "Atmega32" communicating through UART.

💫First Microcontroller :

🔹HMI_ECU : is used for the human-machine interface.
It consists of two sublayers: the HAl layer, which includes the LCD and keypad, and the MACl layer, which includes GPIO, UART, and TIMER.

💫Second Microcontroller:

🔹CONTROL_ECU : is responsible for all processing and decisions in the system, such as password checking, opening the door, and activating the system alarm. It is considered the brain of the system.

This layer also has two sublayers: the HAl layer, which includes the buzzer, EEPROM, and DC motor, and the MACl layer, which includes GPIO, UART, TIMER, and I2C.


💫The system sequence is as follows:

1️⃣ Create a system password by entering a password consisting of 5 numbers. The LCD will display "*" on the screen for each number entered.

2️⃣If the two passwords match, the system now has a password and it is saved inside the EEPROM.

3️⃣The LCD will always display the main system options, which are to open the door or change the password.

4️⃣ If the password is matched, the door is opened using the motor function.

5️⃣ If the password is unmatched, the buzzer will sound for 1 minute, displaying a warning message.
