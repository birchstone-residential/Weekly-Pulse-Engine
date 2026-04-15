#!/usr/bin/env bash
set -e

export PATH="/opt/cmake/bin:$PATH"
cd /home/birchstonereporting/Weekly-Pulse-Engine
source /home/birchstonereporting/Weekly-Pulse-Engine/venv/bin/activate
exec python3 /home/birchstonereporting/Weekly-Pulse-Engine/scripts/oversee_process.py