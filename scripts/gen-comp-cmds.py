#!/usr/bin/env python3
import os
import sys
import json

CC = os.environ.get('CC', 'cc').removeprefix("ccache ")
CFLAGS = os.environ.get('CFLAGS', '')
BUILD = os.environ.get('BUILD', 'release')

LIBYALC_SRCS = os.environ.get('LIBYALC_C_SRCS', '').split()

def main():
    base_args = [CC] + CFLAGS.split()

    entries = []
    cwd = os.getcwd()

    def add_entry(file_path):
        obj_root = f"build/{BUILD}/obj"
        obj_path = os.path.join(obj_root, os.path.splitext(file_path)[0] + '.o')

        file_norm = file_path.replace('\\', '/')
        obj_norm = obj_path.replace('\\', '/')

        args = base_args + ['-c', file_norm, '-o', obj_norm]
        entries.append({
            "directory": cwd.replace('\\', '/'),
            "arguments": args,
            "file": file_norm
        })

    seen = set()
    for f in LIBYALC_SRCS:
        if f not in seen:
            seen.add(f)
            add_entry(f)

    with open('compile_commands.json', 'w') as out:
        json.dump(entries, out, indent=2)
        out.write('\n')

if __name__ == '__main__':
    main()
