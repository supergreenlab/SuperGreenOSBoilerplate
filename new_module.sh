#!/bin/bash

# Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
# Author: Constantin Clauzel <constantin.clauzel@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

if [ "$#" -ne 1 ]; then
  echo "[Usage] $0 module_name"
  exit
fi

mkdir main/$1
echo "Copying files to main/$1"
echo "$(sed "s/CAPS_NAME/${1^^}/g;s/NAME/$1/g"  templates/new_module.yml)" > /tmp/new_module
for i in $(find templates/new_module/*)
do
  FILE="$(basename ${i/.template/})"
  FILE_PATH="main/$1/${FILE/new_module/$1}"
  if [[ "$i" == *".template" ]]; then
    echo "Call mustache for $i to $FILE_PATH"
    mustache /tmp/new_module $i > "$FILE_PATH"
  else
    echo "Copying file $i to $FILE_PATH"
    #cp $i $FILE_PATH
  fi
done

echo "Adding module to main/component.mk"
echo "COMPONENT_SRCDIRS += $1" >> main/component.mk

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"
echo "==="
echo -e "${GREEN}Done${NC}"
echo "==="
echo -e "${RED}Don't forget to add the init_$1(); function call in main/init.c and add $1/$1.h to the list of modules in config.yml${NC}"
