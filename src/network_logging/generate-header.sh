#!/bin/bash

path=`dirname "$0"`
dest_file="$path/logging-frame.h"
src_file="$path/logging-frame.html"

rm "$dest_file" 2> /dev/null

cat << EOF >> "$dest_file"
#pragma once

#include <Arduino.h>

const char HTML_FILE[] PROGMEM =
EOF

sed 's/\\/\\\\/g' < "$src_file" | sed 's/"/\\"/g' | sed 's/^/"/' | sed 's/$/\\n"/' >> "$dest_file"
#     'escape back slashes'   'escape double quotes' 'wrap lines in double quotes'

echo ';' >> "$dest_file"
