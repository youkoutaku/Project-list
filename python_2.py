#input

p1=input('What\'s your name?')

print('Answer:'+p1)

n1 = int( input('please input one number:') )
n2 = int( input('please input anther:') )

print(type(n1),type(n2))
print('sum:',n1+n2)

#2-1演算子
b=(a:=2)*2

#変換型の変換
a=int(24.1)
b=float(3)
c=str(68)
print(a,b,c)

#2-2
#文字列の連結
frist='YANG'
last='GUANGZE'
name=frist+last
print(name)
print(name*5)
print(name+str(a))

#フォーマット文字列
print(f'I am {a} years old. I came to japan for {b} years')

#指数表現 2.5e4=2.5×10^4
print(2.1e4)
print(1.9e-4)
#2-3リスト
scores = [50,55,60,65,70]
type(scores)
print(scores)

#リスト成分インデックス
print(scores[0])
print(scores[1])
print(scores[2])
#末尾からのインデックス
print(scores[-1])
print(scores[-2])
days=['Sun','Mon','Tue','Wed','Thu','Fri','Sat']
print(len(days))

#2-4
import math
from re import I #module import

print(math.sqrt(2))
print(math.floor(3.1415926))
print(math.sin(math.radians(30))) #sin(30 deg )

#math.定数
#pi 円周率, e 自然対数の底
r=5
print(r*r*math.pi)

import random
#乱数のモジュール

#randint(a,b) a以上b以下のランダムな整数を返す
a=1
b=100
c=random.randint(a,b)
print(c)

#random.choice() リストや複数などの中からランダムに選択する
janken=['a','b','c']
d=random.choice(janken)
print(d)

#random.randrange(x) 0からx-1までのランダムな整数を返す
#random() oから1までランダムなfloat数

#モジュールに別名をつけて使う  import モジュール名　as 別名
import math as m
print(m.sqrt(2))

#単位関数でのimport. from モジュール名 import 関数  
from math import sqrt
print(sqrt(2))
#単位関数でのimportにより，モジュール名を書かずに関数を直接に使えるようになるs

from math import sqrt, sin, cos
#複数関数でのimport

from math import *
#全ての関数や定数のimport
