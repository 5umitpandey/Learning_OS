#!/bin/bash
echo "------------------------------- System Information ----------------------------"
echo "Hostname:        $(hostname)"
echo "OS Version:      $(lsb_release -d | awk '{print $2, $3}')"
echo "Kernel Version:  $(uname -r)"
echo "CPU Model:       $(lscpu | grep 'Model name' | awk -F ': ' '{print $2}')"
echo "Memory (RAM):    $(free -h | awk '/^Mem:/ {print $2}')"
echo "Disk Usage:      $(df -h / | awk '/\// {print $5}')"
echo "Network Details: $(ip addr show | awk '/inet / {print $2}')"