/*====================TX1下利用opencv读取IP相机方法（相机和TX1直连）=================*/
1、先获取到相机本身的IP地址（假设获取到的IP地址为192.168.1.168）

2、在TX1开发板的Ubuntu系统内给有线网卡设置静态地址，注意地址要跟相机同网段（按照前面假设的相机IP，可将开发板的IP设置成192.168.1.2，子网掩码255.255.255.0，网关192.168.1.1）

3、更改readIPCamera.cpp第30行的内容，将IP改成相机的地址（读取相机采用rtsp协议，端口554，后面的sub表示读取相机子码流）

4、TX1下编译readIPCamera.cpp（注意指令里有单引号）：
g++ -std=c++11 readIPCamera.cpp -O2 -o readIPC -lpthread `pkg-config --cflags --libs opencv`

5、相机上电，相机跟TX1开发板直接用网线相连

6、运行readIPC可执行文件，即可实现TX1下利用opencv读取IP相机（打开后按Esc可退出程序）