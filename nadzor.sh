#!/bin/bash
if [ $# -ne 1 ]; then
echo "Użycie: $0 <czas_w_sekundach>"
exit 1
fi

sleep "$1" &
PID=$!
echo "Uruchomiono zadanie w tle (PID=$PID)"

cleanup(){
echo
echo "Wykryto przerwanie (Crtl + C)"
echo "Zatrzymanie procesu PID=$PID"
kill "$PID" 2>/dev/null
exit 2
}
trap celanup SIGINT

wait "$PID"

echo "Zadanie zakoncznczyło sie poprawnie"
exit 0
