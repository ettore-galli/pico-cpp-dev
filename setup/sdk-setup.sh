
cd ~/pico
git clone https://github.com/raspberrypi/pico-sdk.git --branch master
cd pico-sdk
git submodule update --init
cd ..
git clone https://github.com/raspberrypi/pico-examples.git --branch master


sudo apt update

sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential

sudo apt install g++ libstdc++-arm-none-eabi-newlib