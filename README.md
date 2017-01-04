# Bus Tracking System

## 设备：

1. Linkit one + GPS
2. 正文科技LoRa通信模组
3. 超声波测距模组 HC-SR04 * 2

## 流程图

![](https://ws3.sinaimg.cn/large/6177e8b1jw1fbej484tnhj20x80sujv7.jpg)

## 工作原理

### 人数统计原理

#### 说明

门外,门内各一个超声波测距感应器。一个垂直向下放置，一个水平放置。通过检测距离是否到阈值内，若到阈值内则触发感应器，当一个感应器被触发之后，进入一段等待期，若在等待期内另一个感应器被触发，测算计入，清空感应器触发状态。否则取消所有感应器被触发的状态。

* 当门外的感应器被触发，在等待期内触发了门后的感应器，则算进入一人。
* 当门内的感应器被触发，在等待期内触发了门前的感应器，则算出去一人。

等待期的长短由门前门后的距离所决定，一般这个距离比较短，所以等待期相对于人上车的速度也比较短。基本上不会出现一个人等待期内进入两个人的情况。

#### 状态机

下面用状态机来表示这一个过程:

![](https://ws2.sinaimg.cn/large/6177e8b1jw1fbejmzfq6lj21720mijtq.jpg)

* S : 初始状态，程序启动，维护一个人数统计变量counter，初始化0，进入状态1
* State 1 : 程序监测两个超声波测距模组
  * cond1: 当车门外的感应器被触发(达到阈值距离之内)，进入State 2
  * cond2: 当车门内的感应器被触发，进入State 3
* State 2 : 进入等待期，监测车门后超声波模组，累加等待期计时器时间
  * cond3: 等待期结束，车门内超声波模组未被触发，清空等待期计时器，重新进入State 1
  * cond5: 等待期内，车门内超声波模组被触发，进入State 4 
* State 3: 进入等待期，监测门外超声波模组，累加等待期计时器时间
  * cond4: 等待期结束，车门外超声波模组未被触发，清空等待期计时器，重新进入State 1
  * cond5: 等待期内，车门外超声波模组，进入State 5
* State 4: 计进来一个人，车内人数counter + 1，清空等待期计时器，重新进入State 1
* State 5: 计出去一个人，车内人数counter - 1，清空等待期计时器，重新进入State 1

PS:

[counting_people_state](https://github.com/Kinpzz/Bus-Tracking/tree/master/counting_people_state)是使用了状态机的版本(待测试)，使用状态机更容易编程

[counting_people](https://github.com/Kinpzz/Bus-Tracking/tree/master/counting_people)是使用了非状态机的版本

## 效果

![](https://ws1.sinaimg.cn/large/6177e8b1jw1fbejz9ycxhj21hs0nstcj.jpg)