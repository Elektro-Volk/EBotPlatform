mkdir build
mkdir ../ebpbot
cd build
cmake .. && make && mv ./EBP ../../ebpbot/EBP && cd ../../ebpbot && ./EBP
