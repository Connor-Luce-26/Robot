$serialibPath = "C:\Users\lucerc\OneDrive - Rose-Hulman Institute of Technology\Desktop\Robot\RobotControllerSoftware"
g++.exe -o "C:\Users\lucerc\OneDrive - Rose-Hulman Institute of Technology\Desktop\Robot\RobotControllerSoftware\RobotControllerSoftware.exe" `
    "C:\Users\lucerc\OneDrive - Rose-Hulman Institute of Technology\Desktop\Robot\RobotControllerSoftware\RobotControllerSoftware.cpp" `
    -I"$serialibPath" `
    "$serialibPath\serialib.cpp"
.\RobotControllerSoftware\RobotControllerSoftware.exe