#!/bin/sh

find ../.. -name \*.cpp -o -name \*.h -exec astyle --options=astylerc {} +
