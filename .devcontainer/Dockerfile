FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y git sudo && \
    apt install -y cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential && \
    apt install -y g++ libstdc++-arm-none-eabi-newlib && \
    apt install -y python3 && \
    apt install -y tar  && \
    apt install -y libusb-1.0-0-dev

RUN useradd -m -s /bin/bash devuser
RUN usermod -aG sudo devuser
RUN echo 'devuser:password' | chpasswd
USER devuser
WORKDIR /home/devuser