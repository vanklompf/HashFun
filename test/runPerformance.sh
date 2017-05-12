#!/bin/bash
TRAVIS_BUILD_NUMBER=${1-0}
COMPILER=${1-gcc6}
TRAVIS_COMMIT_MESSAGE=${1-manual}

HASHFUN_BIN=hashfun_$RANDOM

cp ../hashfun ../$HASHFUN_BIN
scp -Cr -i azure_ssh performance_results.template ../$HASHFUN_BIN $IDENTITY:~
ssh -i azure_ssh $IDENTITY << EOF

 #make sure performance tests won't run in paralell
 echo "Acquiring lock..."
 set -e
 (
 # Wait for lock on /var/lock/.runPerformance.exclusivelock (fd 200) for 20 minutes
 flock -x -w 1200 200

 echo "Lock acquired"
 cp --no-clobber performance_results.template performance_results.csv
 printf "$TRAVIS_BUILD_NUMBER,$COMPILER,$TRAVIS_COMMIT_MESSAGE," >> performance_results.csv
 echo "Running $HASHFUN_BIN..."
 ./$HASHFUN_BIN -c -n 7 >> performance_results.csv
 rm $HASHFUN_BIN
 ) 200>/var/lock/.runPerformance.exclusivelock
 echo "Lock freed"
EOF
