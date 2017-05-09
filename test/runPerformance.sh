#!/bin/bash

USER=terion
HOST=vanklompf.westeurope.cloudapp.azure.com
FULLIDENTITY=$USER@$HOST


scp -Cr -i azure_ssh performance_results.template ../hashfun $FULLIDENTITY:~
ssh -i azure_ssh $FULLIDENTITY << EOF
cp --no-clobber performance_results.template performance_results.cvs
printf "$TRAVIS_BUILD_NUMBER,$COMPILER,$TRAVIS_COMMIT_MESSAGE," >> performance_results.cvs
./hashfun -c -n 5 >> performance_results.cvs
EOF
