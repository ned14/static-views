#!/usr/bin/env python3

#          Copyright Tom Westerhout 2017.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

# Configuration file for running memory usage benchmarks for
# sort_array.cpp

import sys
import os
import subprocess
import itertools
import random
import re
from pathlib import Path

# Dirty hack to import ../../ProfileMemory.py
sys.path.append(str(Path(os.path.realpath(__file__)).parent.parent))
import ProfileMemory


DEBUG = False

#
# Generates a string of size ints separated by commas.
#
def _generate_data(size : int) -> str:
    random.seed(12345 + size)
    return ', '.join(map(str, map(lambda _: random.randint(0, 10000),
        itertools.repeat(0, size))))

#
# Generates a list [int(k), int(k**2), ..., int(k**m)] with k**m <= n and
# unique elements.
#
def _compute_sizes(n : int, k : float) -> list:
    a = list( set( itertools.takewhile(
        lambda x: x <= n,
        map( lambda i: int(k ** i),
            itertools.count()
        ))))
    a.sort()
    return a

def main():
    args  = ProfileMemory.parse_command_line()
    global DEBUG
    DEBUG = ProfileMemory.DEBUG

    root    = Path(args.root)
    prefix  = Path(args.output)
    configs = { 'b2'             : args.b2
              , 'gnuplot'        : args.gnuplot
              , 'root'           : root
              , 'prefix'         : prefix
              , 'toolset'        : args.toolset
              , 'test-name'      : 'sort'
              , 'target'         : 'compile-sort'
              , 'sizes'          : _compute_sizes(4000, 1.2)
              , 'generator'      : _generate_data
              , 'include_file'   : root / 'sort' / 'sort_array_data.txt'
              , 'results_file'   : prefix / ('sort' + '.' + args.toolset 
                                       + '.dat')
              , 'measure_memory' : root / 'tools' / 'measure_memory'
              , 'temp_file'      : prefix / '.temp-file.txt'
              }

    ProfileMemory.run(configs)
    return 0

if __name__ == '__main__':
    main()
