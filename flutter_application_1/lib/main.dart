import 'package:flutter/material.dart';
import 'wifiscreen.dart';
import 'bluetoothtest.dart';
import 'hotspotscreen.dart';
import 'alerts.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatelessWidget {
  const MyHomePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            CustomButton(
              text: 'Scan for Wifi',
              width: 260,
              height: 70,
              textsize: 19,
              padding: const EdgeInsets.all(12.0),
              onPressed: () async {
                if ( await ConnectivityChecker.isLocationEnabled() == false) {
                  showCustomAlertDialog(
                    context,
                    'Location is off',
                    'Please enable Location to use this feature.',
                  );
                }
                if ( await ConnectivityChecker.isWifiEnabled() == false) {
                  showCustomAlertDialog(
                    context,
                    'Wifi is Off',
                    'Please enable Wifi to use this feature.',
                  );
                }
                if (await ConnectivityChecker.isLocationEnabled() == true && await ConnectivityChecker.isWifiEnabled() == true){
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (context) => const WifiScreen()),
                  );
                }
              },
            ),

            CustomButton(
              text: 'Hotspot Connection',
              width: 260,
              height: 70,
              textsize: 19,
              padding: const EdgeInsets.all(12.0),
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => const HotspotScreen()),
                );
              },
            ),

            CustomButton(
              text: 'Bluetooth Devices',
              width: 260,
              height: 70,
              textsize: 19,
              padding: const EdgeInsets.all(12.0),
              onPressed: () async {
                if (await ConnectivityChecker.isLocationEnabled() == false) {
                  showCustomAlertDialog(
                    context,
                    'Location is off',
                    'Please enable Location to use this feature.',
                  );
                }
                if(await ConnectivityChecker.isBluetoothEnabled() == false) {
                  showCustomAlertDialog(
                    context,
                    'Bluetooth is Off',
                    'Please enable Bluetooth to use this feature.',
                  );
                }
                if( await ConnectivityChecker.isBluetoothEnabled() == true && await ConnectivityChecker.isLocationEnabled() == true) {
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (context) => const Bluetoothscreen()),
                  );
                }
              },
            ),
          ],
        ),
      ),
    );
  }
}

class CustomButton extends StatelessWidget {
  final String text;
  final double width;
  final double height;
  final double textsize;
  final EdgeInsetsGeometry padding;
  final VoidCallback onPressed;

  const CustomButton({
    super.key,
    required this.text,
    required this.width,
    required this.height,
    required this.padding,
    required this.onPressed,
    required this.textsize,
  });

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: padding,
      child: SizedBox(
        width: width,
        height: height,
        child: ElevatedButton(
          onPressed: onPressed,
          style: ElevatedButton.styleFrom(
            backgroundColor: const Color.fromARGB(255, 118, 183, 237),
          ),
          child: Text(
            text,
            style: TextStyle(
              color: Colors.black,
              fontSize: textsize,
            ),
          ),
        ),
      ),
    );
  }
}
