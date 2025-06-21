#!/usr/bin/env bash


lower=1          # minimum possible value
upper=10        # maximum possible value
secret=$(( RANDOM % upper + lower ))   # random number in [lower, upper]
tries=0

echo "Guess the number between $lower and $upper."

while true; do
    read -rp "Your guess: " guess                 
    [[ $guess =~ ^[0-9]+$ ]] || {                 # input check: must be integer
        echo "Please enter a whole number."; continue; }

    ((tries++))
    if   (( guess < secret )); then
        echo "Too low!"
    elif (( guess > secret )); then
        echo "Too high!"
    else
        echo "🎉 Correct! You got it in $tries tries."
        break
    fi
done
