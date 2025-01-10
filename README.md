# Uiautomator 2 to csv converter

## 1. Install termux and break out of the [termux env](https://github.com/hansalemaos/termuxfree)

## 2. Install the provided apks from the [Uiautomator2 project](https://github.com/openatx/android-uiautomator-server)

## 3. Push the source file to the device/emulator
```sh
adb -s 127.0.0.1:5516 push "C:\Users\hansc\source\repos\uiautomator2parser\uiautomator2parser.cpp" /sdcard
```

## 4. Compile it with GCC
```sh
g++ -std=c++2a -O3 -g0 uiautomator2parser.cpp
```

## 5. Start the Uiautomator2 server
```sh
am instrument -w -r -e debug false -e class com.github.uiautomator.stub.Stub com.github.uiautomator.test/androidx.test.runner.AndroidJUnitRunner
```

## 6. Run the app
```sh 
./a.out 

# The app executes by default 
curl -X POST -d '{"jsonrpc": "2.0", "id": "1", "method": "dumpWindowHierarchy", "params": [false, 10000]}' 'http://127.0.0.1:9008/jsonrpc/0'

# If you want to change the command, you can pass a arg that will be executed 

./a.out "my different curl command"

```
