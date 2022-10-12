from re import X
import sympy as sym

sym.var('x y z')

func_u = x /( (x**2 + y**2 +z**2)**(3/2) ) 
func_v = y /( (x**2 + y**2 +z**2)**(3/2) ) 
func_w = z /( (x**2 + y**2 +z**2)**(3/2) )

yprime_1 = func_w.diff(y)
yprime_2 = func_v.diff(z)

print(yprime_1)
print(yprime_2)

yprime_1 = func_u.diff(z)
yprime_2 = func_w.diff(x)

print(yprime_1)
print(yprime_2)

yprime_1 = func_v.diff(x)
yprime_2 = func_u.diff(y)

print(yprime_1)
print(yprime_2)