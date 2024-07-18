import 'package:flutter/material.dart';
import 'package:connectivity_plus/connectivity_plus.dart';
import 'package:geolocator/geolocator.dart';
import 'package:flutter_blue/flutter_blue.dart';

class ConnectivityChecker {
  static Future isWifiEnabled() async {
    final List<ConnectivityResult> connectivityResult = await (Connectivity().checkConnectivity());
    if (connectivityResult.contains(ConnectivityResult.wifi)) {
      return true;
    }
    else {
      return false;
    }
    
  }

  static Future isLocationEnabled() async {
    bool serviceEnabled = await Geolocator.isLocationServiceEnabled();
    if (!serviceEnabled) {
      return false;}
    if (serviceEnabled) {
      return true;}
  }

  static Future isBluetoothEnabled() async {
    BluetoothState state = await FlutterBlue.instance.state.first;
    if (state == BluetoothState.off) {
      return false;
    }
    if (state == BluetoothState.on) {
      return true;
    }
  }
}

void showCustomAlertDialog(BuildContext context, String title, String message) {
  showDialog(
    context: context,
    builder: (BuildContext context) {
      return AlertDialog(
        title: Text(title),
        content: Text(message),
        actions: <Widget>[
          TextButton(
            child: const Text('OK'),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      );
    },
  );
}
