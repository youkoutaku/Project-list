#python入門

#print
print(501)

print('hello world')

print('a','b','c')

#ファイルに書き込む
fp=open(r'C:\Users\ygz19\python\t.txt', 'a+')
# or fp=open('C:\\Users\\ygz19\\python\\t.txt', 'a+')
print('hello', file=fp)
fp.close()

#\r,\t,\n,\b
print('hello\nworld')   #newline
print('hello\rworld')   #return 覆盖
print('hello\tworld')   #tab
print('hello\bworld')   #backspace

#\\,\',\"
print('http:\\\\') 
print('he said \'Yes\' . ')

#printにr,Rを使い,転移符号が無効になる．ただし，最後の符号が" \ "にはいけない.
print(r'he said \'Yes\' . ')

#値の位置，型，内容
name_1='YANG'
print('内容',name_1)
print('位置',id(name_1))
print('型',type(name_1))

#int(整数) 0b (二進数) 0o(八進数) 0x(十六進数)
print(10,0b10101,0o256,0x1A)

#float 小数 誤差があるため，decimalを利用
float_1=1.1
float_2=1.3
print(float_1+float_2)

from decimal import Decimal
from turtle import Turtle
print(Decimal('1.1')+Decimal('1.3')) #括弧の中に''を注意

#bool型 True (1), False (0)
boolon_1=True
boolon_2=False
print(boolon_1,type(boolon_1))
print(boolon_2,type(boolon_2))

#文字型 ' ', " ",  ''' '''  """ """(改行可能)
str_1='こにちは'
str_2="こにちは"
str_3='''こに
ちは'''
print(str_1)
print(str_2)
print(str_3)

#変数型の変化 int(), str(), float()
s_1='YANG'
age_1=23
print('私は'+s_1+',今'+age_1+'歳です．')    #同時に異なる型の変化を使えない
print('私は'+s_1+',今'+str(age_1)+'歳です．') #int型変数を文字型に変換する

#多行コメント
'''これ
は
コメント'''

#ファイルの最初にコメントを利用し，ファイルが保存する時のencodeの型を指定できる．

