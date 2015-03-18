#!/bin/bash
log=AmazingProjectTestLog
cd ..
make clean >> $log
make >> $log

echo >> $log
startTime=`date +"%a_%b_%d_%T_%Y"`
echo "Starting BATS.sh System Testing, Please wait for logs to be produced, 
should take around 10 minutes. All logs will be created in main directory"
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
echo "Expected output: Could not connect to host: pierce.cs.dartmouth.ed" >> $log
printf "Actual output: " >> $log
startup -h pierce.cs.dartmouth.ed -n 3 -d 3 2>> $log

echo >> $log
echo >> $log
echo "Test 3: Invalid Command Line Option" >> $log
echo "Input: startup -j pierce.cs.dartmouth.ed -n 3 -d 3" >>$log
echo "Expected output: startup: invalid option -- 'j'" >> $log
echo "startup takes options -ndh" >> $log
printf "Actual output: " >> $log
startup -j pierce.cs.dartmouth.edu -d 3 -n 3 2>> $log

echo >> $log
echo >> $log
echo "Test 4: Number of avatars passed exceeds limit" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 13 -d 8" >>$log
echo "Expected output: Unsuccessful init - Too many avatars" >> $log
printf "Actual output: " >> $log
startup -h pierce.cs.dartmouth.edu -n 13 -d 8 >> $log 2>&1
 
echo >> $log
echo "Test 5: Difficulty level exceeds maximum difficulty" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 3 -d 10" >>$log
echo "Expected output: Unsuccessful init - Bad Difficulty Level" >> $log
printf "Actual output: " >> $log
startup -h pierce.cs.dartmouth.edu -n 3 -d 10 >> $log 2>&1

echo >> $log
echo "Test 6: Sample Run: level 3 difficulty 3 avatars"  >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 3 -d 3" >> $log
echo "Check produced log file" >> $log
echo -e "\n" | startup -h pierce.cs.dartmouth.edu -n 3 -d 3

echo >> $log
echo "Test 7: Sample Run: level 5 difficulty 4 avatars" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 4 -d 5" >>$log
echo "Check produced log file" >> $log
echo -e "\n" | startup -h pierce.cs.dartmouth.edu -n 4 -d 5

echo >> $log
echo "Test 8: Sample Run: level 6 difficulty 5 avatars" >> $log
echo "Input: startup -h pierce.cs.dartmouth.edu -n 6 -d 5" >>$log
echo "Check produced log file" >> $log
echo -e "\n" | startup -h pierce.cs.dartmouth.edu -n 6 -d 5

echo >> $log
endTime=`date +"%a_%b_%d_%T_%Y"`
echo "endTime: $endTime" >> $log

make clean
