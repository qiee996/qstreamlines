#!/usr/bin/env python

import numpy as np

def createXY(nx, ny):
    x = np.linspace(-1, 1, nx)
    y = np.linspace(-1, 1, ny)
    xx, yy = np.meshgrid(x, y)
    return x, y, xx, yy

def createUV(x, y):
    '''Counterclockwise'''
    theta = np.arctan2(y, x)
    u = -np.sin(theta) * abs(theta / np.pi)
    v = np.cos(theta) * abs(theta / np.pi)
    return u, v

def write2d(fn, mesh):
    with open(fn, 'w') as f:
        for row in mesh:
            for col in row:
                f.write(str(col))
                f.write(' ')
            f.write('\n')

def main(argv):
    nx, ny = int(argv[-3]), int(argv[-2])
    fn = argv[-1]
    x, y, xx, yy = createXY(nx, ny)
    u, v = createUV(xx, yy)
    write2d(fn + 'u.txt', u)
    write2d(fn + 'v.txt', v)

if '__main__' == __name__:
    import sys
    sys.exit(main(sys.argv))
