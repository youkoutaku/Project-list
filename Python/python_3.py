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