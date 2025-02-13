#include <vector>
#include <string>
#include <iostream>
#include "serialib.h"
using namespace std;
vector<int> getAvailableCOMPorts();
int getTransmitterPort();
int failedToGetTransmitterPort();
serialib connectToTransmitter();
serialib failedToConnectToTransmitter(serialib device, int transmitterPort);
void sendCommand(serialib device, string command);
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
int main()
{
	serialib device = connectToTransmitter();
	return 0;
}