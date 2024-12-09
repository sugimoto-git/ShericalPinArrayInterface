# 3軸加速度センサーLIS3DHで振動を測定、HDC1000で温度、湿度を測定し、
# Ambientで記録する

from micropython import mem_info
import utime
import lis3dh
import hdc1000
import math
import ambient

calibp = 10 # キャリブレーション間隔(m秒)
calibn = 10 # キャリブレーション回数

samplingp = 100 # サンプリング間隔(m秒)
samplingn = 300 # サンプリング回数
sampling10 = 30 # サンプリング回数/10

# 10m秒間隔で10回、加速度を読み、キャリブレーション値にする
calib = [0, 0, 0]

def calibration():
    global calib
    c = [0, 0, 0]
    for var in range(calibn):
        a = ac.readAccel()
        c = [e1 + e2 for (e1, e2) in zip(c, a)]
        utime.sleep_ms(calibp)
    calib = list(map(lambda x:x/calibn, c))
    print(calib)

# 1秒間隔で300回(5分間)、加速度を読み、x、y、z、それぞれの
# 最大値と上から10%(30個目)の値を求める

def max10(a, v):
    a.append(v)
    a.sort(reverse=True)
    a.pop()

def do_connect(ssid, password):
    import network
    sta_if = network.WLAN(network.STA_IF)
    if not sta_if.isconnected():
        print('connecting to network...')
        sta_if.active(True)
        sta_if.connect(ssid, password)
        while not sta_if.isconnected():
            pass
    # print('network config:', sta_if.ifconfig())

ac = lis3dh.Lis3dh()
calibration()
hdc = hdc1000.Hdc1000(2)

do_connect('...ssid...', '...password...')
am = ambient.Ambient(100, '...writeKey...')
am2 = ambient.Ambient(101, '...writeKey1...')

while True:
    x = [0 for i in range(sampling10)]
    y = [0 for i in range(sampling10)]
    z = [0 for i in range(sampling10)]

    for var in range(samplingn):
        xyz = ac.readAccel()
        xyzc = [e1 - e2 for (e1, e2) in zip(xyz, calib)]
        max10(x, abs(xyzc[0]))
        max10(y, abs(xyzc[1]))
        max10(z, abs(xyzc[2]))
        utime.sleep_ms(samplingp)

    # print(x)
    # print(y)
    # print(z)

    RtodB = lambda R: round((math.log((R) / 16000 * 9.80665 / 0.00001) / math.log(10) * 20), 1)

    Xmax = RtodB(x[0])
    X10 = RtodB(x[len(x) - 1])
    Ymax = RtodB(y[0])
    Y10 = RtodB(y[len(y) - 1])
    Zmax = RtodB(z[0])
    Z10 = RtodB(z[len(z) - 1])

    str = 'd1: %.1f, d2: %.1f, d3: %.1f, d4: %.1f, d5: %.1f, d6: %.1f' % (Xmax, X10, Ymax, Y10, Zmax, Z10)
    print(str)

    r = am.send({'d1': Xmax, 'd2': X10, 'd3': Ymax, 'd4': Y10, 'd5': Zmax, 'd6': Z10})
    print(r.status_code)
    r.close()

    temp = hdc.readTemp()
    humid = hdc.readHumid()
    str = 'd1: %.1f, d2: %.1f' % (temp, humid)
    print(str)

    r = am2.send({'d1': temp, 'd2': humid})
    print(r.status_code)
    r.close()
    mem_info()
