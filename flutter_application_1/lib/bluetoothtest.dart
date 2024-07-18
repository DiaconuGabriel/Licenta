import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:geolocator/geolocator.dart' as ph;
import 'package:path_provider/path_provider.dart';
import 'package:device_info/device_info.dart';
import 'dart:io';
import 'dart:convert';
import 'alerts.dart';
import 'main.dart';

class Bluetoothscreen extends StatefulWidget {
  const Bluetoothscreen({super.key});

  @override
  State<Bluetoothscreen> createState() => _BluetoothscreenState();
}

class _BluetoothscreenState extends State<Bluetoothscreen> {
  DeviceInfoPlugin deviceInfo = DeviceInfoPlugin();
  FlutterBlue flutterBlue = FlutterBlue.instance;
  late BluetoothDevice device;
  List<BluetoothDevice> devices = [];
  StreamSubscription<BluetoothDeviceState>? subscription;
  StreamSubscription<List<int>>? exchange;
  List<String> devicesnames = [];
  bool isScanning = false;
  bool wasconnected = false;

  StreamSubscription<BluetoothState>? bluetoothStateSubscription;
  StreamSubscription<ph.ServiceStatus>? locationstate;

  @override
  void initState() {
    super.initState();
    bluetoothStateSubscription = flutterBlue.state.listen((state) {
      if (state == BluetoothState.off) {
        setState(() {
          isScanning = false;
          devices = [];
          devicesnames = [];
          wasconnected = false;
          // subscription?.cancel();
          exchange?.cancel();
        });
        showCustomAlertDialog(context, 'Bluetooth is Off', 'Please enable Bluetooth to use this feature.');
      }
    });
    locationstate = ph.Geolocator.getServiceStatusStream().listen( (ph.ServiceStatus status) {
      if (status == ph.ServiceStatus.disabled){
        setState(() {
          isScanning = false;
          devices = [];
          devicesnames = [];
          wasconnected = false;
          // subscription?.cancel();
          exchange?.cancel();
        });
        showCustomAlertDialog(context, 'Location is Off', 'Please enable Location to use this feature.');
      }
    });
  }

  @override
  void dispose() {
    if(mounted){
      bluetoothStateSubscription?.cancel();
      locationstate?.cancel();
      subscription?.cancel();
      exchange?.cancel();
      super.dispose();
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'Bluetooth Devices',
          style: TextStyle(
            fontSize: 25,
            color: Color.fromARGB(255, 0, 0, 0),
          ),
        ),
        backgroundColor: const Color.fromARGB(255, 118, 183, 237),
      ),
      body: Column(
        children: [
          const Text(''),
          Expanded(
            flex: 5,
            child: ListView(
              children: _buildDeviceList(),
            ),
          ),
          Expanded(
            flex: 1,
            child: Center(
              child: ElevatedButton(
                onPressed: _requestPermissionsAndStartScan,
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
        ],
      ),
    );
  }

  List<Widget> _buildDeviceList() {
    return List.generate(
      devices.length,
      (index) => Column(
        children: [
          Row(
            children: [
              Expanded(
                child: Padding(
                  padding: const EdgeInsets.only(left: 28, right: 20),
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
                  onPressed: (){if(mounted){_connectToDevice(index);}
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
          const SizedBox(height: 20),
        ],
      ),
    );
  }

  void _connectToDevice(int index) async {
    device = devices.firstWhere((d) => d.name == devicesnames[index]);
    print(device);

    try {
      if (wasconnected == false) {

        final directory = await getApplicationDocumentsDirectory();
        final file = File('${directory.path}/password.txt');
        String credentials = await file.readAsString();
        print(credentials);
        await device.disconnect();
        await device.connect().timeout(const Duration(seconds: 5));
        
        subscription = device.state.listen((BluetoothDeviceState state) async {
          if (state == BluetoothDeviceState.connected) {
            print('Connected to ${device.name}');
          } 
          if (state == BluetoothDeviceState.disconnected) {
            print('Disconnected from ${device.name}');
            await device.disconnect();
            if (mounted){
              setState(() {
                exchange?.cancel();
                wasconnected = false;
                subscription?.cancel();
              });
              }
            }
          });

        List<BluetoothService> services = await device.discoverServices();

        Guid recieveCharacteristicUuid = Guid("19B10001-E8F2-537E-4F6C-D104768A1214");
        Guid sendnameCharacteristicUuid = Guid("19B10002-E8F2-537E-4F6C-D104768A1214");
        Guid sendcredentialsCharacteristicUuid = Guid("19B10003-E8F2-537E-4F6C-D104768A1214");

        BluetoothCharacteristic? recieveCharacteristic;
        BluetoothCharacteristic? sendnameCharacteristic;
        BluetoothCharacteristic? sendcredentialsCharacteristic;

        for (BluetoothService service in services) {
          for (BluetoothCharacteristic characteristic in service.characteristics) {
            if (characteristic.uuid == recieveCharacteristicUuid) {
              recieveCharacteristic = characteristic;
            }
            if (characteristic.uuid == sendnameCharacteristicUuid) {
              sendnameCharacteristic = characteristic;
            }
            if (characteristic.uuid == sendcredentialsCharacteristicUuid) {
              sendcredentialsCharacteristic = characteristic;
            }
          if (recieveCharacteristic != null && sendnameCharacteristic != null && sendcredentialsCharacteristic != null) {
            break;
          }
        }

        if (recieveCharacteristic != null && recieveCharacteristic.properties.notify && Platform.isAndroid) {
          

          AndroidDeviceInfo androidInfo = await deviceInfo.androidInfo;

          await recieveCharacteristic.setNotifyValue(true);
          await sendnameCharacteristic?.write(utf8.encode(androidInfo.model));
          
          exchange = recieveCharacteristic.value.listen((value) async{
            
            String valuerecieved = (utf8.decode(value)).trim();
            print('Received value: $valuerecieved');
            if (valuerecieved == '1'){
              await sendcredentialsCharacteristic?.write(utf8.encode(credentials));
              await recieveCharacteristic?.setNotifyValue(false);
              // await device.disconnect();
              //
              if(mounted){
                showDialog(
                  context: context,
                  builder: (BuildContext context) {
                    return AlertDialog(
                      title: const Text('Connection Successful'),
                      content: Text('Internet credentials have been successfully sent to ${devicesnames[index]}.'),
                      actions: [
                        TextButton(
                          onPressed: () {
                            Navigator.push(
                              context,
                              MaterialPageRoute(builder: (context) => const MyHomePage()),
                            );
                          },
                          child: const Text('Done'),
                        ),
                      ],
                    );
                  },
                );
              }
            }
            if (valuerecieved == '2'){
              await recieveCharacteristic?.setNotifyValue(false);
              await device.disconnect();
              if (mounted){
                showCustomAlertDialog(context, 'Connection Error', '${device.name} rejected the connection.');
                setState(() {
                  wasconnected = false;
                  devices = [];
                  devicesnames = [];
                  subscription?.cancel();
                  exchange?.cancel();
              });
            }
          }
          });
        } else {
          print('Target characteristic not found or does not support notifications');
        }
        if (mounted){
          wasconnected = true;
        }
      }
      }
    } catch (e) {
      print('eroarea este $e');
      if (mounted){
        setState(() {
          wasconnected = false;
          devices = [];
          devicesnames = [];
        });
      }
      showCustomAlertDialog(context, 'Error', 'Failed to connect to device.');
    }
  }

  void _requestPermissionsAndStartScan() async {
    Map<Permission, PermissionStatus> statuses = await [
      Permission.bluetoothScan,
      Permission.bluetoothConnect,
    ].request();

    if (statuses[Permission.bluetoothScan]!.isDenied) {
      print('BLUETOOTH_SCAN permission denied');
      return;
    }

    if (statuses[Permission.bluetoothConnect]!.isDenied) {
      print('BLUETOOTH_CONNECT permission denied');
      return;
    }

    startScan();
  }

  void startScan() async {
    if(await ConnectivityChecker.isBluetoothEnabled() == false) {
      if (mounted) {
        setState(() {
          isScanning = false;
          devices = [];
          devicesnames = [];
          wasconnected = false;
          exchange?.cancel();
          subscription?.cancel();
        });
      showCustomAlertDialog(context,'Bluetooth is Off','Please enable Bluetooth to use this feature.');
      }
    }

    if(await ConnectivityChecker.isLocationEnabled() == false) {
      if(mounted) {
        setState(() {
          isScanning = false;
          devices = [];
          devicesnames = [];
          wasconnected = false;
          subscription?.cancel();
          exchange?.cancel();
        });
      
      showCustomAlertDialog(context,'Location is Off','Please enable Location to use this feature.');
      }
    }

    if (await ConnectivityChecker.isBluetoothEnabled() == true && await ConnectivityChecker.isLocationEnabled() == true) {
        
        flutterBlue.startScan(timeout: const Duration(seconds: 5));

          flutterBlue.scanResults.listen((results) {
          if (mounted) {
            setState(() {
              devicesnames = [];
              devices = [];
              wasconnected = false;
            });
          }
          for (ScanResult result in results) {
            if (result.device.name.trim().isNotEmpty && !devicesnames.contains(result.device.name)) {
              devicesnames.add(result.device.name);
              devices.add(result.device);
            }
          }
        });
      }
    }
  }
