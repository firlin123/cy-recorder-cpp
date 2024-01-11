# cy-recorder-cpp

## Build

### With git submodules
1. Run `git clone --recurse-submodules https://github.com/firlin123/cy-recorder-cpp.git`
2. Run `sudo apt-get install build-essential cmake openssl libssl-dev`
3. Run `cd cy-recorder-cpp`
4. Run `cmake .`
5. Run `make`

### Without git submodules
1. Run `sudo apt-get install build-essential cmake openssl libssl-dev libboost-all-dev libasio-dev rapidjson-dev`
2. Run `git clone https://github.com/zaphoyd/websocketpp.git`
3. Run `sudo cp -r websocketpp/websocketpp /usr/local/include/`
4. Run `git clone https://github.com/socketio/socket.io-client-cpp.git`
5. Run `cd socket.io-client-cpp`
6. Run `cmake .`
7. Run `make`
8. Run `sudo make install`
9. Run `cd ..`
10. Run `git clone https://github.com/firlin123/cy-recorder-cpp.git`
11. Run `cd cy-recorder-cpp`
12. Run `cmake -DUSE_SUBMODULES=OFF .`
13. Run `make`

Tested only on Ubuntu Desktop 23.10.