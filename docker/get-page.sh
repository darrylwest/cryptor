#!/usr/bin/env bash
# dpw@alamo
# 2024-12-15 16:51:24
#

set -eu



echo ""
curl -k https://localhost:29200/

echo "Version: "
curl -k https://localhost:29200/version
