FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y git sudo

RUN useradd -m -s /bin/bash devuser
RUN usermod -aG sudo devuser
RUN echo 'devuser:password' | chpasswd
USER devuser
WORKDIR /home/devuser