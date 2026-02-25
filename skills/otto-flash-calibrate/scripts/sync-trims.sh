#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 \"Trims (LL, RL, LF, RF): 18, -23, 0, -10\"" >&2
  exit 1
fi

input="$1"
if [[ "$input" =~ ^[[:space:]]*Trims[[:space:]]*\(LL,[[:space:]]*RL,[[:space:]]*LF,[[:space:]]*RF\):[[:space:]]*(-?[0-9]+),[[:space:]]*(-?[0-9]+),[[:space:]]*(-?[0-9]+),[[:space:]]*(-?[0-9]+)[[:space:]]*$ ]]; then
  ll="${BASH_REMATCH[1]}"
  rl="${BASH_REMATCH[2]}"
  lf="${BASH_REMATCH[3]}"
  rf="${BASH_REMATCH[4]}"
elif [[ "$input" =~ ^[[:space:]]*(-?[0-9]+),[[:space:]]*(-?[0-9]+),[[:space:]]*(-?[0-9]+),[[:space:]]*(-?[0-9]+)[[:space:]]*$ ]]; then
  ll="${BASH_REMATCH[1]}"
  rl="${BASH_REMATCH[2]}"
  lf="${BASH_REMATCH[3]}"
  rf="${BASH_REMATCH[4]}"
else
  echo "Input format not recognized." >&2
  echo "Expected: \"Trims (LL, RL, LF, RF): 18, -23, 0, -10\" or \"18,-23,0,-10\"" >&2
  exit 1
fi

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
config_file="${repo_root}/include/otto_robot_config.h"

if [[ ! -f "${config_file}" ]]; then
  echo "Missing config file: ${config_file}" >&2
  exit 1
fi

perl -0pi -e "s/constexpr int TRIM_LEFT_HIP = -?\d+;/constexpr int TRIM_LEFT_HIP = ${ll};/" "${config_file}"
perl -0pi -e "s/constexpr int TRIM_RIGHT_HIP = -?\d+;/constexpr int TRIM_RIGHT_HIP = ${rl};/" "${config_file}"
perl -0pi -e "s/constexpr int TRIM_LEFT_FOOT = -?\d+;/constexpr int TRIM_LEFT_FOOT = ${lf};/" "${config_file}"
perl -0pi -e "s/constexpr int TRIM_RIGHT_FOOT = -?\d+;/constexpr int TRIM_RIGHT_FOOT = ${rf};/" "${config_file}"

echo "Updated trims in ${config_file}"
echo "LL=${ll}, RL=${rl}, LF=${lf}, RF=${rf}"
