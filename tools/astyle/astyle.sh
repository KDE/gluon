#!/bin/sh

find ../.. -path "*/core/gdl" -prune -o -path "*/build" -prune -o -name \*.cpp -o -name \*.h -exec astyle --options=astylerc {} +
