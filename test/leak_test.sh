#!/bin/bash

while true
do
sleep 1
ps | grep minishell | head -1 | awk '{ print $1 }' | leaks
done
