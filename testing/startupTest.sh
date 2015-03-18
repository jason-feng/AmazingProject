#!/bin/bash
log=startupSystemTestLog
cd ..
make clean >> $log
make >> $log

echo >> $log
startTime=`date +"%a_%b_%d_%T_%Y"`
echo "startTime: $startTime" >> $log
echo "hostname: `hostname`" >> $log
echo "operating system: `uname`" >> $log

echo >> $log
echo "Test 1: Not enough arguments" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 3 -d 3 extrarg" >> $log
echo "Expected output: Invalid Number of Arguments" >> $log
printf "Actual output: " >> $log
startup -h pierce.cs.dartmouth.edu -n 3 -d 3 extrarg >> $log 2>&1

echo >> $log
echo "Test 2: Invalid Host Name" >> $log
echo "Input: startup -h pierce.cs.dartmouth.ed -n 3 -d 3" >>$log
echo "Expected output: Invalid directory provided" >> $log
printf "Actual output: " >> $log
startup -h pierce.cs.dartmouth.ed -n 3 -d 3 2>> $log

echo >> $log
echo "Test 3: Number of avatars passed exceeds limit" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 13 -d 8" >>$log
echo "Expected output: Unsuccessful init - Too many avatars" >> $log
printf "Actual output: " >> $log
startup -h pierce.cs.dartmouth.edu -n 13 -d 8 >> $log 2>&1
 
echo >> $log
echo "Test 4: Difficulty level exceeds maximum difficulty" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 3 -d 10" >>$log
echo "Expected output: Unsuccessful init - Bad Difficulty Level" >> $log
printf "Actual output: " >> $log
startup -h pierce.cs.dartmouth.edu -n 3 -d 10 >> $log 2>&1

echo >> $log
echo "Test 5: Sample Run: level 3 difficulty 3 avatars"  >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 3 -d 3" >> $log
echo "Check produced log file" >> $log
echo -e "\n" | startup -h pierce.cs.dartmouth.edu -n 3 -d 3

echo >> $log
echo "Test 6: Sample Run: level 5 difficulty 4 avatars" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 4 -d 5" >>$log
echo "Check produced log file" >> $log
echo -e "\n" | startup -h pierce.cs.dartmouth.edu -n 4 -d 5

echo >> $log
echo "Test 7: Sample Run: level 6 difficulty 5 avatars" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 6 -d 5" >>$log
echo "Check produced log file" >> $log
echo -e "\n" | startup -h pierce.cs.dartmouth.edu -n 6 -d 5

echo >> $log
endTime=`date +"%a_%b_%d_%T_%Y"`
echo "endTime: $endTime" >> $log

make clean
