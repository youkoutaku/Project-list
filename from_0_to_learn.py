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

#--------------------------------------------------------------------------------------

#3-1入力
print('長方形の面積を求めます\n')
height = float(input('高さを入力してください\n'))
width = float(input('幅を入力してください\n'))
print(f'the answer is {height*width}.')

#3-2条件分岐
a=18
if a<16:
    print('まだ選挙権はありません')

age=20
if a<13:
    print('無料')
elif a<65:
    print('大人の料金')
else:
    print('割引の料金')

#3項演算子 値1 if 条件式 else 値2
c = a if a>b else b
#if a>b : c=a else: c=b

#3-3論理演算子
#and論理積
a>0 and b>0
#or論理和
a>0 or b>0
#not否定
not a>0

#演算子順位　算術演算子(+ - * /...) > 関係演算子(> < == !=...) > 論理演算子(and or not) 
(a+c>10) and (b<3)

#比較演算子の連結
(a>5) and (a<10)
#まとめられる
5 < a < 10

a < b == c
# (a<b) and (b==c)

#if文と真偽値
if a == True:
    b=c

if a:
    b=c

#ifでnotの利用
if not a:
    b=d
else:
    b=c

#Falseと同等に扱われる値
None #値がない
0 #ゼロ
'' #空の文字列
() #空のタプル(tuple 不可変化型のリスト)
[] #空のリスト
{} #空の辞書

#3-4処理の繰り返し
#while文
i = 0
while i<5:
    print('こにちは')
    i += 1

#for文
for i in [10,20,30,40,50]:
    print(i)
#for 変数 in 反復可能オブジェクト:
#   処理内容
#反復可能オブジェクトの要素が先頭から一つずつ順番に「変数」に代入され，処理内容が実行される．
#全ての要素を参照し，ループを終わる．

#rangeオブジェクト
range(stop)
#0から「stop-1」までの整数

range(start,stop)
#startの値から「stop-1」までの整数

range(start,stop,step)
#startの値から「stop-1」までの整数，増分はstep
#stepがマイナスであれば，startの値から「stop+1」までの整数,step次第に値を小さくなる

for i in range(10):
    print(i)

#ループ処理を中断する.「break」

#ループの中の残りの処理をスキップし，次の繰り返し回に移る．「continue」

#無限ループ
while 1:
    print('こにちは')

#ループ処理のネスト
for a in range(1,10):
    print()#改行するため
    for b in range(1,10):
        print(f'{a}+{b}={a*b}',end='')
    #通常のprintは改行を付けるので，「end=''」をつけて改行せずに出力になる.

#---------------------------------------------------------------------------------------------
#4-1オブジェクト指向
#--------------------------------------------------------------------------------------------

#これまで,'Hello',3や5など，全ての文字列や数字，符号はそれぞれ重複しないID(認識番号)が持っている．
# IDをつけて管理されるデータを インスタンス という．(オブジェクトとも言える)
# 「値」ではなく，print関数を使って「インスタンスの値」を知ることができる．
#その代わりに　id関数を使用し，インスタンスのIDを知ることができる.

a=3
id(a)
b='Hello'
id(b)

#異なる変数に異なる「値」を代入すると，IDが異なるのは当然なことだが，

#同じに変数に異なる「値」を代入すると，IDも異なる．
a=3
id(a)
a='Hello'
id(a)
#それは異なるデータのIDは異なるためである．

#だから，C言語のような構造化言語（変数を宣言し，作った変数に番地をつけて，「値」を入れる）とは違う．
#オブジェクト指向言語では，全ての「値」にID(番地)をつけて，作った変数に「値」の番地を入れる．（ポインタ変数と似るところがある）

#-------------------------------------------------------------------------------
#変数の代入とインスタンスの関係
a=2
b=a
print(a)
#>>>2
print(b)
#>>>2
#変数aと変数bにそれぞれ2の値を持っているというイメージがあるかもしれないが，
#実際に変数aと変数bにそれぞれ「2の値」のID(番地)を持っている．
#つまり，異なる変数に同じな「値」(文字列や数字)を代入しても，変数が持っているIDは同じである．
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#インスタンスの同値性と同一性
a=10
b=10
c=5
print(a == b)
#>>>True
print(a == c)
#>>>False
#「==演算子」でインスタンスの値を比較できる．「aとbは同値である」

a=[1,2,4]
b=[1,2,4]
print(a == b)
#>>>True
#リストの場合は全ての要素が等しいと，インスタンスの値がもちろん等しい．

a=[1,2,4]
b=[1,2,4]
print(a is b)
#>>>False
#「is演算子」でインスタンスのIDを比較できる．
#リストの全ての要素が等しくても，インスタンスのIDが異なる．注意!!!
#同値だけど同一ではない

a=[1,2,4]
b=a
print(a is b)
#>>>True
print(a == b)
#>>>True
a[0]=99
print(b)
#>>>b=[99,2,4]
#同値かつ同一である．
#同値リストはインスタンスのIDが違う．
#b = aにより，aとbは一つのリストのIDを持っているので，同一性がある．

#同値性をチェックする時は，「==」
#同一性をチェックする時は，「is」

#-------------------------------------------------------------------------------

