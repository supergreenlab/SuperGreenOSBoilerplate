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

if [ "$#" -ne 2 ]; then
  echo "[Usage] $0 template_name module_name"
  exit
fi

TEMPLATE_NAME="$1"
MODULE_NAME="$2"

mkdir -p main/$MODULE_NAME
echo "Copying files to main/$MODULE_NAME"
echo "$(sed "s/CAPS_NAME/${MODULE_NAME^^}/g;s/NAME/$MODULE_NAME/g"  templates/$TEMPLATE_NAME.yml)" > /tmp/$TEMPLATE_NAME
for i in $(find templates/$TEMPLATE_NAME/*)
do
  FILE="$(basename ${i/.template/})"
  FILE_PATH="main/$MODULE_NAME/${FILE/$TEMPLATE_NAME/$MODULE_NAME}"
  if [[ "$i" == *".template" ]]; then
    echo "Call mustache for $i to $FILE_PATH"
    mustache /tmp/$TEMPLATE_NAME $i > "$FILE_PATH"
  else
    echo "Copying file $i to $FILE_PATH"
    cp $i $FILE_PATH
  fi
done


if ! grep -q -- "- $MODULE_NAME" config.yml; then
  if [ "$TEMPLATE_NAME" == "new_module" ]; then
    echo "Adding module to custom_modules in config.yml"
    sed -i "/custom_modules:/ a - $MODULE_NAME" config.yml
  elif [ "$TEMPLATE_NAME" == "new_i2c_device" ]; then
    echo "Adding i2c device to i2c_devices in config.yml"
    sed -i "/i2c_devices:/ a - $MODULE_NAME" config.yml
  fi
fi

GREEN="\033[0;32m"
RED="\033[0;31m"
NC="\033[0m"
echo "==="
echo -e "${GREEN}Done${NC}"
echo "==="
echo "Running ./update_template.sh...."
./update_template.sh
