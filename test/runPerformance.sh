#!/bin/bash
IDENTITY=terion@vanklompf.westeurope.cloudapp.azure.com
TRAVIS_BUILD_NUMBER=${1-0}
CXX=${3-gcc_unknown}
TRAVIS_COMMIT_MESSAGE=${2-manual}

HASHFUN_BIN=hashfun_$RANDOM

cp ../hashfun ../$HASHFUN_BIN
cat azure.rsa
scp -Cr -i azure.rsa performance_results.template ../$HASHFUN_BIN $IDENTITY:~
ssh -i azure.rsa $IDENTITY << EOF

 #make sure performance tests won't run in paralell
 echo "Acquiring lock..."
 set -e
 (
 # Wait for lock on /var/lock/.runPerformance.exclusivelock (fd 200) for 20 minutes
 flock -x -w 1200 200

 echo "Lock acquired"
 cp --no-clobber performance_results.template performance_results.csv

 printf "$TRAVIS_BUILD_NUMBER,$CXX,$TRAVIS_COMMIT_MESSAGE," >> performance_results.csv
 echo "Running $HASHFUN_BIN..."
 ./$HASHFUN_BIN -c -n 7 >> performance_results.csv
 rm $HASHFUN_BIN
 ) 200>/var/lock/.runPerformance.exclusivelock
 echo "Lock freed"
EOF
