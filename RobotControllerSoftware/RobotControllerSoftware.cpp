#include <vector>
#include <string>
#include <iostream>
#include "serialib.h"
using namespace std;
// Function declarations
vector<int> getAvailableCOMPorts();
int getTransmitterPort();
int failedToGetTransmitterPort();
serialib connectToTransmitter();
serialib failedToConnectToTransmitter(serialib device, int transmitterPort);
void sendCommand(serialib device, string command);
void connectToRobot(serialib device);
string receiveResponse(serialib device);
void failedToConnectToRobot(serialib device);
string getRobotCommand();
// Function definitions
vector<int> getAvailableCOMPorts()
{
	cout << "Start checking for available COM ports" << endl;
	vector<int> availablePorts;
	serialib device = serialib();
	for (int i=1;i<99;i++)
	{
		string deviceName = "COM" + to_string(i);
		if (device.openDevice(deviceName.c_str(), 115200) == 1)
		{
			availablePorts.push_back(i);
			device.closeDevice();
		}
	}
	cout << "End checking for available COM ports" << endl;
	return availablePorts;
}
int failedToGetTransmitterPort()
{
	cout << "Failed to get transmitter port" << endl;
	cout << "Try again? (yes or no)" << endl;
	string input;
	cin >> input;
	if (input == "yes")
	{
		return getTransmitterPort();
	} else if (input == "no")
	{
		cout << "Exiting program" << endl;
		exit(0);
	}
	else
	{
		cout << "Invalid input" << endl;
		return failedToGetTransmitterPort();
	}
}
int getTransmitterPort()
{
	vector<int> availablePorts = getAvailableCOMPorts();
	cout << "Available COM ports:" << endl;
	for (int i : availablePorts)
	{
		cout << "COM" + to_string(i) << endl;
	}
	cout << "Enter the COM port number of the transmitter: ";
	int port;
	cin >> port;
	for (int i : availablePorts)
	{
		if (i == port)
		{
			return port;
		}
	}
	return failedToGetTransmitterPort();
}
serialib failedToConnectToTransmitter(serialib device, int transmitterPort)
{
	cout << "Failed to connect to transmitter on COM " << to_string(transmitterPort) << endl;
	cout << "Try again? (yes or no)" << endl;
	string input;
	cin >> input;
	if (input == "yes")
	{
		return connectToTransmitter();
	} else if (input == "no")
	{
		cout << "Exiting program" << endl;
		exit(0);
	}
	else
	{
		cout << "Invalid input" << endl;
		return failedToConnectToTransmitter(device, transmitterPort);
	}
}
serialib connectToTransmitter()
{
	serialib device = serialib();
	int transmitterPort = getTransmitterPort();
	cout << "Start connecting to transmitter on COM " << to_string(transmitterPort) << endl;
	string transmitterName = "COM" + to_string(transmitterPort);
	if (device.openDevice(transmitterName.c_str(), 115200) == 1)
	{
		cout << "Connected to transmitter on COM " << to_string(transmitterPort) << endl;
	}
	else
	{
		return failedToConnectToTransmitter(device, transmitterPort);
	}
	return device;
}
void failedToConnectToRobot(serialib device)
{
	cout << "Failed to connect to robot" << endl;
	cout << "Try again? (yes or no)" << endl;
	string input;
	cin >> input;
	if (input == "yes")
	{
		connectToRobot(device);
	} else if (input == "no")
	{
		cout << "Exiting program" << endl;
		exit(0);
	}
	else
	{
		cout << "Invalid input" << endl;
		failedToConnectToRobot(device);
	}
}
void sendCommand(serialib device, string command)
{
	cout << "Sending command: " << command << endl;
	if (device.writeString(command.c_str()) == 1)
	{
		cout << "Command sent" << endl;
	}
	else
	{
		cout << "Failed to send command" << endl;
	}
}
string receiveResponse(serialib device)
{
	cout << "Receiving response" << endl;
	char response[1024];
	if (device.readString(response, '\n', 1000, 1000) == 1)
	{
		cout << "Response received: " << string(response) << endl;
	}
	else
	{
		cout << "Failed to receive response" << endl;
	}
	return string(response);
}
void connectToRobot(serialib device)
{
	cout << "Connecting to robot" << endl;
	sendCommand(device, "connect");
	string response = receiveResponse(device);
	if (response == "connected")
	{
		cout << "Connected to robot" << endl;
	}
	else
	{
		failedToConnectToRobot(device);
	}
}
string getRobotCommand(serialib device)
{
	cout << "Commands:" << endl;
	cout << "sensors" << endl;
	cout << "chassis move to \"x\" \"y\" \"z\"" << endl;
	cout << "chassis turn to \"yaw\"" << endl;
	cout << "arm move to \"x\" \"y\" \"z\"" << endl;
	cout << "arm turn to \"roll\" \"pitch\" \"yaw\"" << endl;
	cout << "gripper open" << endl;
	cout << "gripper close" << endl;
	cout << "close program" << endl;
	cout << "Enter a command for the robot: ";
	string command;
	cin >> command;
	sendCommand(device, command);
	receiveResponse(device);
	return command;

}
int main()
{
	serialib device = connectToTransmitter();
	connectToRobot(device);
	while (true)
	{
		string command = getRobotCommand();
	}
	return 0;
}