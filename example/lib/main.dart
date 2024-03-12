import 'package:flutter/material.dart';
import 'package:native_add/native_add.dart' as native_add;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      title: 'Image Picker Example',
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key});

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int temp = 0;
  late int sumResult;

  @override
  void initState() {
    super.initState();
    sumResult = native_add.manipulateMatrix();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Image Picker Example'),
      ),
      body: Center(child: Text(temp.toString())),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          setState(() {
            temp = sumResult;
          });
          print(temp.toString());
        },
        tooltip: 'Pick Image',
        child: const Icon(Icons.image),
      ),
    );
  }
}
