import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'package:permission_handler/permission_handler.dart';

class Bluetoothscreen extends StatefulWidget {
  const Bluetoothscreen({super.key});

  @override
  State<Bluetoothscreen> createState() => _BluetoothscreenState();
}

class _BluetoothscreenState extends State<Bluetoothscreen> {
  FlutterBlue flutterBlue = FlutterBlue.instance;
  late BluetoothDevice device;
  List<BluetoothDevice> devices = [];
  StreamSubscription<BluetoothDeviceState>? subscription;
  List<String> devicesnames = [];
  bool isScanning = false;
  bool wasconnected = false;
  bool streamsub = false;

  StreamSubscription<BluetoothState>? _bluetoothStateSubscription;

  @override
  void initState() {
    super.initState();
    _bluetoothStateSubscription = flutterBlue.state.listen((state) {
      if (state == BluetoothState.off) {
        showDialog(
          context: context,
          builder: (BuildContext context) {
            return AlertDialog(
              title: const Text('Bluetooth is Off'),
              content: const Text('Please turn on Bluetooth to connect to devices.'),
              actions: [
                TextButton(
                  onPressed: () {
                    setState(() {
                      isScanning = false;
                      devices = [];
                      devicesnames = [];
                      wasconnected = false;
                      if (mounted) {
                        // device.disconnect();
                        subscription?.cancel();
                      }
                    });
                    Navigator.of(context).pop();
                  },
                  child: const Text('OK'),
                ),
              ],
            );
          },
        );
        if (wasconnected) {
          // device.disconnect();
          wasconnected = false;
        }
      } else if (state == BluetoothState.on) {
      }
    });
  }

  @override
  void dispose() {
    _bluetoothStateSubscription?.cancel();
    subscription?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Placeholder(
      //adda appbar
      child: Scaffold(
        appBar: 
        AppBar(
          title: const Text(
            'Bluetooth Devices',
            style: TextStyle(
              fontSize: 25,
              color: Color.fromARGB(255, 0, 0, 0),
            ),),
          backgroundColor: const Color.fromARGB(255, 118, 183, 237),
        ),
        body: Column(
          children: [
            const Text(''),
            Expanded(
              flex: 5,
              child: ListView(
                children: [
                  Column(
                    children: List.generate(
                      devices.length,
                      (index) => Column(
                        children: [
                          Row(
                            children: [
                              Expanded(
                                child: Padding(
                                  padding: const EdgeInsets.only(left: 28,right: 20), // Adjust the left padding as desired
                                  child: Text(
                                    devicesnames[index],
                                    style: const TextStyle(fontSize: 20),
                                  ),
                                ),
                              ),
                              Padding(
                                padding: const EdgeInsets.only(right: 25.0),
                                child: ElevatedButton(
                                  style: ButtonStyle(
                                    minimumSize: MaterialStateProperty.all(const Size(110, 5)),
                                    backgroundColor: MaterialStateProperty.all(const Color.fromARGB(255, 118, 183, 237)),
                                    padding: MaterialStateProperty.all(const EdgeInsets.all(14)),
                                    shape: MaterialStateProperty.all(RoundedRectangleBorder(
                                      borderRadius: BorderRadius.circular(35),
                                    )),
                                  ),
                                  onPressed: () async {

                                  
                                    
                                    device = devices.firstWhere((d) => d.name == devicesnames[index]);
                                    // Connect button pressed logic
                                    print(device);

                                    try{                                    
                                      if (wasconnected == false) {
                                        await device.disconnect();
                                        await device.connect().timeout(const Duration(seconds: 5));
                                        wasconnected = true;
                                        
                                        subscription = device.state.listen((BluetoothDeviceState state) async {
                                          if (state == BluetoothDeviceState.connected) {
                                            print('Connected to ${device.name}');
                                            streamsub = true;
                                          } else {
                                            print('Disconnected from ${device.name}');
                                            await device.disconnect();
                                            wasconnected = false;
                                            streamsub = false;
                                          }

                                          bool isBluetoothOn1 = await flutterBlue.isOn;

                                          if(!isBluetoothOn1) {
                                            await device.disconnect();
                                          }

                                          if (streamsub == false) { 
                                            subscription?.cancel();
                                            // devices=[];
                                            // devicesnames=[];   // posibil aici sa fi fost eroarea
                                          }
                                        });
                                      }
                                    } catch (e) {
                                        print('eroarea este $e');
                                        showDialog(
                                          context: context,
                                          builder: (BuildContext context) {
                                            return AlertDialog(
                                              title: const Text('Error'),
                                              content: Text('Failed to connect to device: $e'),
                                              actions: <Widget>[
                                                TextButton(
                                                  child: const Text('OK'),
                                                  onPressed: () {
                                                    setState(() {
                                                      // device.disconnect();
                                                      wasconnected = false;
                                                      devices=[];
                                                      devicesnames=[];
                                                    });
                                                    Navigator.of(context).pop(); // Close the dialog
                                                  },
                                                ),
                                              ],
                                            );
                                          },
                                        );
                                        return;
                                      }
                                    },

                                  child: const Text(
                                    'Connect',
                                    style: TextStyle(
                                      color: Colors.black,
                                      fontSize: 16,
                                    ),
                                  ),
                                ),
                              )
                            ],
                          ),
                          const SizedBox(height: 20), // Spacing between buttons
                        ],
                      ),
                    ),
                  ),
                ],
              ),
            ),
            Expanded(
              flex: 1,
              child: SizedBox(
                child: Center(
                  child: ElevatedButton(
                    onPressed: () async {

                      Map<Permission, PermissionStatus> statuses = await [
                        Permission.bluetoothScan,
                        Permission.bluetoothConnect,
                      ].request();

                      // Check if permissions were granted
                      if (statuses[Permission.bluetoothScan]!.isDenied) {
                        print('BLUETOOTH_SCAN permission denied');
                        return;
                      }

                      if (statuses[Permission.bluetoothConnect]!.isDenied) {
                        print('BLUETOOTH_CONNECT permission denied');
                        return;
                      }

                      startScan();
                    },
                    style: ElevatedButton.styleFrom(
                      backgroundColor: const Color.fromARGB(255, 118, 183, 237),
                      padding: EdgeInsets.zero,
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(100),
                      ),
                    ),
                    child: Container(
                      width: 200,
                      height: 70,
                      alignment: Alignment.center,
                      child: const Text(
                        'Scan for devices',
                        style: TextStyle(
                          color: Colors.black,
                          fontSize: 18,
                        ),
                    ),
                  ),
                ),
              ),
            ),
            )
          ],
        ),
      ),
    );
  }

  void startScan() async {
    // Check if Bluetooth is on
    bool isBluetoothOn = await flutterBlue.isOn;
    if (!isBluetoothOn) {
      showDialog(
        context: context,
        builder: (BuildContext context) {
          return AlertDialog(
            title: const Text('Bluetooth is Off'),
            content: const Text('Please turn on Bluetooth to scan for devices.'),
            actions: [
              TextButton(
                onPressed: () {
                  Navigator.of(context).pop();
                  setState(() {
                    devices=[];
                    devicesnames=[];
                    wasconnected = false;
                    if (mounted) {
                      device.disconnect();
                    }
                  });
                },
                child: const Text('OK'),
              ),
            ],
          );
        },
      );
      return;
    }

    // Check for permission
    PermissionStatus status = await Permission.bluetooth.request();
    if (status.isGranted) {
      setState(() {
        isScanning = true;
      });

      flutterBlue.startScan(timeout: const Duration(seconds: 10));

      flutterBlue.scanResults.listen((results) {
        if (mounted) {
          setState(() {
            devicesnames = [];
            devices=[];
            wasconnected = false;
          });
        }
        for (ScanResult result in results) {
          if (result.device.name.trim().isNotEmpty && !devicesnames.contains(result.device.name)) {
            devicesnames.add(result.device.name);
            devices.add(result.device);
            if (mounted) {
              setState(() {
                devicesnames = devicesnames;
                devices = devices;
              });
            }
          }
        }
        return;
      });
    }
  }
}
