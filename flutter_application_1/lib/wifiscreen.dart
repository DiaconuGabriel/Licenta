import 'package:flutter/material.dart';
import 'package:network_info_plus/network_info_plus.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:path_provider/path_provider.dart';
import 'dart:io';
import 'alerts.dart';

class WifiScreen extends StatefulWidget {
  const WifiScreen({super.key});

  @override
  State<WifiScreen> createState() => _WifiScreen();
}

class _WifiScreen extends State<WifiScreen> {
  String _connectionStatus = 'Unknown';
  final NetworkInfo _networkInfo = NetworkInfo();
  final TextEditingController _networkNameController = TextEditingController();

  @override
  void initState() {
    super.initState();
    _initNetworkInfo();
  }
  
  @override
  void dispose() {
    _networkNameController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Flex(
          direction: Axis.vertical,
          mainAxisAlignment: MainAxisAlignment.center, 
          children: [
            Text(
              _connectionStatus,
              style: const TextStyle(
                fontSize: 22,
              ),
            ),
            Container(
              width: 350,
              height: 60,
              color: Colors.blue[50],
              padding: const EdgeInsets.all(1),
              child: TextField(
                controller: _networkNameController,
                decoration: const InputDecoration(
                  labelText: 'Wifi Password',
                  labelStyle: TextStyle(color: Colors.black),
                  enabledBorder: OutlineInputBorder(
                    borderSide: BorderSide(color: Colors.blue),
                  ),
                  focusedBorder: OutlineInputBorder(
                    borderSide: BorderSide(color: Colors.blue),
                  ),
                ),
              ),
            ),
            SizedBox(
              width: 255,
              height: 130,
              child: Padding(
                padding: const EdgeInsets.all(32),
                child: ElevatedButton(
                  style: ElevatedButton.styleFrom(
                    foregroundColor: Colors.black,
                    backgroundColor: const Color.fromARGB(255, 155, 209, 252)
                  ),
                  onPressed:  () async {
                    setState(() {
                      FocusScope.of(context).requestFocus(FocusNode());
                    });
                    if(_connectionStatus.substring(12,_connectionStatus.length-2).isEmpty | _networkNameController.text.isEmpty){
                      showCustomAlertDialog(context, '', 'Please enter a password.');
                    }
                    if(_connectionStatus.substring(12,_connectionStatus.length-2).isNotEmpty && _networkNameController.text.isNotEmpty){
                      final directory = await getApplicationDocumentsDirectory();
                      final file = File('${directory.path}/password.txt');
                      await file.writeAsString('${_connectionStatus.substring(12,_connectionStatus.length-2)},${_networkNameController.text}');
                      print(await file.readAsString());
                      Navigator.pop(context);
                    }
                  },
                  child: const Text(
                    'Set',
                    style: TextStyle(
                      fontSize: 18,
                    ),
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Future<void> _initNetworkInfo() async {
    String? wifiName;

    PermissionStatus status = await Permission.location.status;
    if (!status.isGranted) {
      status = await Permission.location.request();
    }

    if (status.isGranted) {
      try {
        wifiName = await _networkInfo.getWifiName();
      } catch (e) {
        wifiName = 'Failed to get Wifi Name';
      }

      setState(() {
        _connectionStatus = 'Wifi Name: $wifiName\n';
      });
    }
  }

}