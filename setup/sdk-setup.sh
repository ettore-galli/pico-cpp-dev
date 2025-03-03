
cd ~/pico
git clone https://github.com/raspberrypi/pico-sdk.git --branch master
cd pico-sdk
git submodule update --init
cd ..
git clone https://github.com/raspberrypi/pico-examples.git --branch master

# picotool
git clone https://github.com/raspberrypi/picotool.git
cd picotool

# mpremote
python3 -m venv .venv
. .venv/bin/activate
pip install mpremote