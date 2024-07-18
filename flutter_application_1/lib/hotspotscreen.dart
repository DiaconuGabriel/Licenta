import 'package:flutter/material.dart';
import 'package:path_provider/path_provider.dart';
import 'dart:io';
import 'alerts.dart';

class HotspotScreen extends StatefulWidget {
  const HotspotScreen({super.key});

  @override
  State<HotspotScreen> createState() => _HotspotScreenState();
}

class _HotspotScreenState extends State<HotspotScreen> {
  TextEditingController textFieldController1 = TextEditingController();
  TextEditingController textFieldController2 = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Flex(
          direction: Axis.vertical,
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Container(
              width: 350,
              height: 60,
              color: Colors.blue[50],
              padding: const EdgeInsets.all(1),
              child: TextField(
                controller: textFieldController1,
                decoration: const InputDecoration(
                  labelText: 'Hotspot name',
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
            const Text(""),
            Container(
              width: 350,
              height: 60,
              color: Colors.blue[50],
              padding: const EdgeInsets.all(1),
              child: TextField(
                controller: textFieldController2,
                decoration: const InputDecoration(
                  labelText: 'Hotspot password',
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
                  onPressed: () async{
                    setState(() {
                      FocusScope.of(context).requestFocus(FocusNode());
                    });
                    if (textFieldController1.text.isEmpty | textFieldController2.text.isEmpty) {
                      showCustomAlertDialog(context, '', 'Please fill in all fields');
                      return;
                    }
                    if (textFieldController1.text.isNotEmpty && textFieldController2.text.isNotEmpty){
                      final directory = await getApplicationDocumentsDirectory();
                      final file = File('${directory.path}/password.txt');
                      await file.writeAsString('${textFieldController1.text},${textFieldController2.text}');
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
}