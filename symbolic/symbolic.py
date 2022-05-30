from sympy import *

def transX(d):
    return Matrix([[1,0,0,d],[0,1,0,0],[0,0,1,0],[0,0,0,1]])
    
def transY(d):
    return Matrix([[1,0,0,0],[0,1,0,d],[0,0,1,0],[0,0,0,1]])

def transZ(d):
    return Matrix([[1,0,0,0],[0,1,0,0],[0,0,1,d],[0,0,0,1]])

def rotX(a):
    return Matrix([[1,0,0,0],[0,cos(a),-sin(a),0],[0,sin(a),cos(a),0],[0,0,0,1]])

def rotY(a):
    return Matrix([[cos(a),0,sin(a),0],[0,1,0,0],[-sin(a),0,cos(a),0],[0,0,0,1]])

def rotZ(a):
    return Matrix([[cos(a),-sin(a),0,0],[sin(a),cos(a),0,0],[0,0,1,0],[0,0,0,1]])

A01 = rotZ("q1")*transZ("l1")*rotX("pi/2")
A12 = rotZ("q2+pi/2")*transX("l2")
A23 = rotZ("q3-pi/2")*transZ("l4")*transX("l3")


A03 = simplify( A01 * A12 * A23)

posX = A03[3]
posY = A03[7]
posZ = A03[11]

print("# POS_X")
print(posX)
print("# POS_Y")
print(posY)
print("# POS_Z")
print(posZ)
