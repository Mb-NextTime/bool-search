#!/bin/bash
cd scripts/ && make > /dev/null && cd ..
./scripts/search "${1,,}"