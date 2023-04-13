#!/bin/bash

clear
sudo modprobe dummy
sudo ip link add eth1 type dummy
ip link show eth1
sudo ifconfig eth1 hw ether C8:D7:4A:4E:47:50
sudo ip addr add 192.168.0.10/24 brd + dev eth1 label eth1
sudo ip link set dev eth1 up
ifconfig

exit 0