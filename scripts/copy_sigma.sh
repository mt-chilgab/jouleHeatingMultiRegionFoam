#!/bin/bash

# Reading numbers of cores used
setProc=$(cat ./system/decomposeParDict | grep -oP "(?<=numberOfSubdomains)[\s\t]+(\d+)(?=;)")
setProc=$(expr $setProc - 1)

# Names of solid regions
solidList=$(sed -n "/solid\([^)]\)/p" ./constant/regionProperties)
solidList=$(echo $solidList | grep -oP "(?<=\().+(?=\))")

for i in $(seq 0 $setProc)
do
	for j in $solidList
	do
		cp ./constant/"$j"/sigma ./"processor$i"/constant/"$j"/sigma
	done
done

echo "copying sigma done."
