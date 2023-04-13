#!/bin/bash

clear
sudo ip addr del 192.168.0.10/24 brd + dev eth1 label eth1
sudo ip link delete eth1 type dummy
sudo rmmod dummy
ifconfig

exit 0