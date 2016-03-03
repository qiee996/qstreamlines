#!/usr/bin/env python

import sys
import re

LICENSE_BODY = '''
    LICENSE BEGIN

    qstreamlines - Realtime streamlines animator.
    Copyright (C) 2016  Remik Ziemlinski

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    LICENSE END
'''
EXT_C = '.c .C .cc .cpp .cxx .c++ .h .hpp .hxx'.split()
EXT_SH = '.sh .bash .py'.split()
LICENSE_BODY_C = '''/*''' + LICENSE_BODY + '''*/'''
LICENSE_BODY_SH = LICENSE_BODY.replace('\n', '\n#').rstrip('#').lstrip()
LICENSE_RE = '''\s{4}LICENSE BEGIN.*LICENSE END\n'''
LICENSE_RE_C = re.compile(r'''^/\*\n''' + LICENSE_RE + '''\*/''',  re.MULTILINE| re.DOTALL)
LICENSE_RE_SH = re.compile(r'''^#''' + LICENSE_RE,  re.MULTILINE| re.DOTALL)

def add_license_c(fn):
    print(fn)
    lines = ''
    with open(fn) as fin:
        lines = fin.read()

    new_lines, nsubs = LICENSE_RE_C.subn(LICENSE_BODY_C, lines)
    if not nsubs:
        new_lines = lines + LICENSE_BODY_C

    with open(fn, 'w') as fout:
        fout.write(new_lines)

def add_license_sh(fn):
    print(fn)
    lines = ''
    with open(fn) as fin:
        lines = fin.read()

    new_lines, nsubs = LICENSE_RE_SH.subn(LICENSE_BODY_SH, lines)
    if not nsubs:
        new_lines = lines + LICENSE_BODY_SH

    with open(fn, 'w') as fout:
        fout.write(new_lines)

def has_ext(s, exts):
    return any(s.strip().endswith(ext) for ext in exts)

def add_license(fn):
    if has_ext(fn, EXT_C):
        add_license_c(fn)
    elif has_ext(fn, EXT_SH):
        add_license_sh(fn)

if len(sys.argv) < 2:
	sys.exit('Insert license preamble into source code file(s).\n\n'
              'usage: {} file [...]'.format(sys.argv[0]))

files = sys.argv[1:]

for f in files:
    add_license(f)
