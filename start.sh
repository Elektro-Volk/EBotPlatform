echo "Building Lua..."
cd third_party/lua
mkdir build || cd build
cmake .. && make
cd ../../..
echo "Building EBotPlatform..."
mkdir ../ebpbot
mkdir build || cd build
cmake .. && make && mv ./EBP ../../ebpbot/EBP && cd ../../ebpbot && ./EBP
