[toc]

基于手势控制的智能体感遥控车设计

##### 写在前面的话：

最近突然看到这个项目被关注和fork，首先感谢大家对我的肯定，**写这个前言是为了提示看到本说明的github玩家注意，这个项目虽然是我的毕业设计，但是处于还未完结状态**，他的设计原型为我的另一个仓库【[Remote-Sensing：体感遥控车](https://github.com/Hyf338/Remote-Sensing)】,本设计是在体感遥控车的基础上，进行软硬件的优化。这个项目目前的进度是：

- [x] :heavy_check_mark:硬件设计基本完成，有部分硬件设计的错误和不合理的部分已经在readme文档中指出
- [ ] :x:软件设计：
  - [x]  :diamond_shape_with_a_dot_inside:移植RT-Thread操作系统
  - [x] :part_alternation_mark:PWM电机控制线程，以命令行的方式调节占空比
  - [x] :izakaya_lantern:系​​统指示灯线程
  - [ ] :tv:Oled显示界面设计[裸板实现，还未移植到操作系统]
  - [ ] :milky_way:MPU9250采集三维角度[裸板实现，还未移植到操作系统]

而其核心的算法思想，在我之前的设计【[Remote-Sensing：体感遥控车](https://github.com/Hyf338/Remote-Sensing)】已经体现了，虽然已经毕业了，但还是想把这个东西做得完美一些，不然我大三的作品就可以满足毕业设计的要求了，接下来我也会利用空闲的时间继续完善。

# 简介



# 目录说明

```c
|---Gesture_control_of_smart_car
|--- + Hardware : 硬件电路设计
|--- + Software : 软件RTOS设计
|--- + date : 参考资料，数据手册等
|---  README.md ： 整体说明文档

```



# 系统整体设计
- 本设计主要分为两部分，手持遥控端:raised_hand:和智能遥控车:car:。
    - :raised_hand:持遥控端分为4个子单元：**传感器单元**、**核心控制器单元**、**交互单元**和**电源管理单元**。
        - 传感器单元采用集成陀螺仪，加速度计和磁力计的九轴传感器==mpu9250==，对采集到的数据进行姿态融合，再进行数据滤波和互补，得到俯仰、横滚、偏航角等三维角度信息。
        - 核心控制单元选用功能强大的==STM32== 单片机作为核心控制器。
        - 电源管理单元采用TI公司的 ==线性稳压器TPS7333和TPS7350== 分别稳出5v和3.3v电压，为整个系统提供稳定的电压。
        - 交互单元主要分为两部分，一、串口触摸屏，用于数据显示和人机交互；二、蓝牙模块，进行用户当前手势数据的传输，并且接收智能车的数据回传。
    - :car:智能遥控车端分为5个子单元：**传感器单元**、**核心控制器单元**、**交互单元**、**执行单元**和**电源管理单元**。
        - 为了使为了使设计更加适合于真实的应用场景，传感器单元使用mpu9250传感器用于检测小车的运动状态，利用超声波模块进行障碍物的检测，同时利用ADC进行电压检测。
        - 交互单元采用OLED进行数据的实现，并且利用蓝牙模块向手持遥控器传送小车的基本信息，例如电量、障碍、信号丢失标志位等
        - 核心控制单元综合传感器单元和交互单元的信息，结合PID算法，输出信号通过执行单元，作用于电机。

![系统整体设计框图](https://hyifen.oss-cn-hangzhou.aliyuncs.com/img/遥感车系统功能框图.png)

![系统整体设计框图](/Data/picture/系统整体设计框图.png)

# Hardware
>系统硬件设计首先平台采用Altium Designer电子设计软件，进行原理图的设计和PPCB的绘制。



![原理图设计](https://hyifen.oss-cn-hangzhou.aliyuncs.com/img/20200903230435.png)

![原理图设计](/Data/picture/原理图设计.png)

- [x] PCB - 3D模型示意图

![PCB - 3D模型示意图](https://hyifen.oss-cn-hangzhou.aliyuncs.com/img/20200903230555.png)

![PCB - 3D模型示意图](/Data/picture/PCB - 3D模型示意图.png)

- [x] pcb实物图

  ![pcb实物图](https://hyifen.oss-cn-hangzhou.aliyuncs.com/img/IMG_20200903_231727.jpg)

  ![pcb实物图](/Data/picture/pcb实物图.jpg)
***

- [x] :exclamation:  硬件电路板当前存在的问题和需要改进的地方，可以查看项目中的[Projects](https://github.com/Hyf338/Gesture_control_of_smart_car/projects/1)：
  - PCB中电机H桥驱动模块的VCC线宽不够粗，而且VCC可以不选择5V
  - 5V接口的VCC和GND丝印有误
  - CP2102的VDD为2.7-3.6的电源电压输入

# Software

> 系统软件设计平台采用RT-Thread实时操作系统

- [x] 当前拥有的线程：
  - [ ] LED线程：系统指示灯，定时翻转，用于指示系统没有死机。
  - [ ] PWM线程：电机驱动，用于电机控速，并导出命令，通过finsh命令行的方式，设置PWM占空比。
