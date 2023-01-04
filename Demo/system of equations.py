#ロボット逆運動学の代数的解法のためのプログラム

import sympy
import math
sympy.var('e1,e2,e3,px,py,pz,l0,l1,l2,l3')

C1=(e1 + e1**-1)/2
S1=(e1 - e1**-1)/2j
C2=(e2 + e2**-1)/2
S2=(e2 - e2**-1)/2j
C3=(e3 + e3**-1)/2
S3=(e3 - e3**-1)/2j

eq1 = sympy.Eq( ((l3*C3+l2)*C2 - l3*S2*S3)*C1, px )
eq2 = sympy.Eq( ((l3*C3+l2)*C2 - l3*S2*S3)*S1, py )
eq3 = sympy.Eq( (l3*C3+l2)*S2 + l3*C2*S3*S1+l1+l0, pz )

E =sympy.solve([eq1, eq2, eq3], [e1, e2, e3])

i=0
while i<3:
    theta= math.atan2( E[i].imag , E[i].real )
    i+=1
print(theta[0], theta[1], theta[2])
