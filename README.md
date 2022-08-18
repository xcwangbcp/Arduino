# Arduino
##   pellet dispenser
摘要：设计一款可以实时检测猴子执行任务状态，并给与固体颗粒奖励的装置，
硬件：使用pad输出实验刺激，feedback是否奖励，蓝牙+arduino，光电感应器用来检测一次成功的食物掉落，motorshield控制stepper的运动
软件：mymou+arduino code
开发记录：
8月11日以前，只能工作10个trial（code：），后来简化程序，减少打印输出后，工作时间在100+trial，但是仍然会有breakdown的记录，过程中会伴随motorshield的芯片发热，使用外设电源为（亿森能12V锂电池组大容量 9V5V移动电源A品18650芯户外监控音响灯带可充电动力电瓶-tmall.com天猫）  的12Vout1输出端为Arduino供电，12vout2为sensor（原装欧姆龙光电开关U型槽型EE-SPX303N EE-SPX403N传感器带1米线-淘宝网 (taobao.com)）供电
8月12日，三块arduino板子，发生不能下载任何程序的故障，其中一块电脑不能在硬件管理器里识别，另外两块可以的(已标记)。
8/15日开始，troubleshooting
1.确认arduino的数字端的输入电压值：less than 5v
2.sensor读取的coding part （constants - Arduino Reference）！
3.Sensor的电路改装，之前电阻为220欧姆，今调整为1K欧姆
