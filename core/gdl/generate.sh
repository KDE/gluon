#!/bin/sh

if [ -e /usr/bin/kdev-pg-qt ]; then
  kdev-pg-qt --output=gdl --namespace=GDL --with-parser --with-lexer --token-text --compatible-error-aware-code gdl.g
else
  echo "This script requires KDevelop-PG-Qt"
fi
