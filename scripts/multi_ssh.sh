#!/bin/sh

# Running one command in multiple remote hosts
# Originally used to swarm join multiple worker nodes

private_key=$1
hosts_file=$2
swarm_join=$3
while IFS= read -r host
do
  ssh -n -i $private_key ubuntu@$host $3
done < "$hosts_file"