# CDP_Project
Subject: Software for embedded systems

Attendance and working hours control system is a modern and intuitive way for employers to manage the presence, absence and schedule of employees. Employees can enter data through the built-in software embedded in the Raspberry Pi. Each time the card is moved close to the device (Raspberry Pi), a signal is sent to the database. The database records the information resulting from the card chip, the selected field (selected button) from the device application and the time when the card was loaded. The role of the card is to authenticate the user. After successful authentication, the user name and surname are entered in the device application. The application also contains several buttons through which you can choose: entry, exit, pause, working or private exit. With the help of JavaScript, a web application has been created through which it can be seen when employees have applied for entry or exit from working hours or have reached a situation for overtime work.

Main focus is on the component Queue. Because it is necessary to maintain the orderly sending of information to the component DataBase when it is active or when it is not active. If the component is not active, the data is stored in the device and sent after the component DataBase is turned on. Queue checks if the DataBase is active with each new card is load (if it is need to send a new information).

For reading the card I use the modul RFID-RC522. The Read.py script is use to send information to cdp project. Write.py is for adding a name to the card.

