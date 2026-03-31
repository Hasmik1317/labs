#!/bin/bash
echo "System Information"
echo "------------------"
echo "CPU Info:"
lscpu | grep "Model name"
echo "CPU ID:"
cat /proc/cpuinfo | grep Serial || echo "Not available"
echo "Memory:"
free -h
echo "Disk:"
lsblk
echo "MAC address:"
ip link | grep link/ether
echo "OS version:"
uname -a 
