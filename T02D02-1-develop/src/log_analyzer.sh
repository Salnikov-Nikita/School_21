#!/bin/bash

if [[ $# -ne 1 ]]; then
echo "error. no such arguments"
exit 1
fi

if [[ ! -f $1 ]]; then
echo "error. no such file"
fi

FilePath="$1"

echo $(sed -n '$=' "$FilePath")

echo $(cat "$FilePath" | cut -d ' ' -f1 | sort | uniq | wc -l | tr -d ' ')
echo $(cat "$FilePath" | cut -d ' ' -f6 | awk '{gsub(/NULL/, "")}1' | sort | uniq | wc -w)

exit 0