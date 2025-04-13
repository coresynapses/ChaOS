#!/bin/bash

if [[ $1 == "--all" ]]; then
    # Run Workload 1
    ./bin/OS conf/workload-1.txt

    # Run Workload 2
    ./bin/OS conf/workload-2.txt

    # Run Workload 3
    ./bin/OS conf/workload-3.txt
elif [[ $1 == "--workload" ]]; then
    case $2 in
	"1") # Run Workload 1
	    ./bin/OS conf/workload-1.txt;;
	"2") # Run Workload 2
	    ./bin/OS conf/workload-2.txt;;
	"3") # Run Workload 3
	    ./bin/OS conf/workload-3.txt;;
	*)
	    echo "Invalid Workload ID";;
    esac
else
    echo "Missing Parameters."
    echo "Pass in the  --all or --workload [n] to run."
fi
