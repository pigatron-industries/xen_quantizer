#!/bin/bash

jupyter nbconvert Tuning.ipynb --to markdown --output tuning.md 
sed -i -e 's/tuning_files/\/assets\/images\/2022-05-13-tuning/g' tuning.md