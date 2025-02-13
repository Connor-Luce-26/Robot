#include <vector>
#include <string>
#include <iostream>
#include "serialib.h"
using namespace std;
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
int getTransmitterPort()
{
	cout << "Available COM ports:" << endl;
	for (int i : getAvailableCOMPorts())
	{
		cout << "COM" + to_string(i) << endl;
	}
	cout << "Enter the COM port number of the transmitter: ";
	int port;
	cin >> port;
	return port;
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
		cout << "Failed to connect to transmitter on COM " << to_string(transmitterPort) << endl;
	}
	return device;
}
// void sendCommand(serialib device, string command)
// {
// 	cout << "Sending command: " << command << endl;
// 	if (device.writeString(command.c_str()) == 1)
// 	{
// 		cout << "Command sent" << endl;
// 	}
// 	else
// 	{
// 		cout << "Failed to send command" << endl;
// 	}
// }
int main()
{
	serialib device = connectToTransmitter();
	return 0;
}
