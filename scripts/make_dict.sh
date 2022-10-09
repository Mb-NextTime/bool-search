#!/bin/bash

cd scripts/ && make > /dev/null && cd ..
cd data/processed && ./../../scripts/vocab * && cd ../..