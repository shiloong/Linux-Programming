#!/bin/bash
# Helper to check the alive ip in 192.168.122.x with parallel ping

for ip in 192.168.122.{2..254}
do
        (
        if ping $ip -w1 &> /dev/null
        then
                echo $ip is alive
        fi
        )&
done
wait &> /dev/null
