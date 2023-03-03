from math import sin
from math import cos
import matplotlib.pyplot as plt

T=0.001         #サンプリング周期sT
tau = 0.1       #定数tau
A = tau + T/2   #A
B = -tau +T/2   #B
t = []          #描画するためのx軸(時間t)
x_0 = []        #x_0(t)
dx_0 = []       #dx_0(t)
wt = []         #w(t)
xt = []         #x(t)
dxt = []        #dx(t)
y = []          #y(k)

for i in range(0,10001):#0~10000のi
    i=i*T #0~10000を0~10になる.T=0.001
    t.append(i)
    x_0.append( sin(i) )
    dx_0.append( cos(i) )
    wt.append( 0.01*sin(100*i) )
    xt.append( sin(i) + 0.01*sin(100*i))
    dxt.append( cos(i)+ cos(100*i) )

y.append( ( xt[1] - xt[0] )/A )#y[-1]がないので，先にy[0]を求める

for k in range(1,10001):#1~10000のk
    y.append( (xt[k] - xt[k-1] - B*y[k-1] )/A )
    #式でyを求める

#x_0の描画
p1=plt.figure(figsize=(30,15))#グラフのサイズ
p1=plt.plot(t, x_0, '-',color='blue')#青い線で，描画

p1=plt.hlines([0],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)#横線
p1=plt.hlines([1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)#横線
p1=plt.hlines([-1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5 )#横線

p1=plt.tick_params(axis='x', labelsize=20)#x軸目盛りの文字サイズ
p1=plt.tick_params(axis='y', labelsize=20)#y軸目盛りの文字列サイズ
p1=plt.xlabel("t",fontsize=25)#x軸ラベル
p1=plt.ylabel("x_0",fontsize=25)#y軸ラベル
p1=plt.savefig("x_0(t).png")#画像を保存する

#dx_0の描画
p2=plt.figure(figsize=(30,15))
p2=plt.plot(t, dx_0, '-',color='red')#赤い線で，描画

p2=plt.hlines([0],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)
p2=plt.hlines([1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)
p2=plt.hlines([-1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5 )

p2=plt.tick_params(axis='x', labelsize=20)
p2=plt.tick_params(axis='y', labelsize=20)
p2=plt.xlabel("t",fontsize=25)
p2=plt.ylabel("dx_0",fontsize=25)
p2=plt.savefig("dx_0(t).png")

#xtの描画
p3=plt.figure(figsize=(30,15))
p3=plt.plot(t, xt, '-',color='blue')

p3=plt.hlines([0],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)
p3=plt.hlines([1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)
p3=plt.hlines([-1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5 )

p3=plt.tick_params(axis='x', labelsize=20)
p3=plt.tick_params(axis='y', labelsize=20)
p3=plt.xlabel("t",fontsize=25)
p3=plt.ylabel("x(t)",fontsize=25)
p3=plt.savefig("x(t).png")

#wtの描画
p4=plt.figure(figsize=(30,15))
p4=plt.plot(t, wt, '-',color='blue')

p4=plt.ylim(-0.02, 0.02)#縦軸の範囲を定める
p4=plt.tick_params(axis='x', labelsize=20)
p4=plt.tick_params(axis='y', labelsize=20)
p4=plt.xlabel("t",fontsize=25)
p4=plt.ylabel("w(t)",fontsize=25)
p4=plt.savefig("w(t).png")

#dxtの描画
p5=plt.figure(figsize=(30,15))
p5=plt.plot(t, dxt, '-',color='blue')
p5=plt.plot(t, dx_0, '-',color='red')

p5=plt.hlines([0],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)
p5=plt.hlines([1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)
p5=plt.hlines([-1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5 )

p5=plt.tick_params(axis='x', labelsize=20)
p5=plt.tick_params(axis='y', labelsize=20)
p5=plt.xlabel("t",fontsize=25)
p5=plt.ylabel("dx(t)",fontsize=25)
p5=plt.savefig("dx(t).png")

#filter outout yの描画
p6=plt.figure(figsize=(30,15))
p6=plt.plot(t, y, '-',color='blue')
p6=plt.plot(t, dx_0, '-',color='red')

p6=plt.hlines([0],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)#横線
p6=plt.hlines([1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5)#横線
p6=plt.hlines([-1],t[0], t[-1], color='black', linestyles='dashed', alpha=0.5 )#横線

p6=plt.tick_params(axis='x', labelsize=20)
p6=plt.tick_params(axis='y', labelsize=20)
p6=plt.xlabel("t",fontsize=25)
p6=plt.ylabel("y(k)",fontsize=25)
p6=plt.savefig("y(k).png")