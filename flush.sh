#/usr/bin/env bash

# Цикл работает, ПОКА файл /dev/sda НЕ существует
while [ ! -e /dev/sda ]; do
  sleep 0.5
done
