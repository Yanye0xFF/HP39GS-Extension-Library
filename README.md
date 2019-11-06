# HP39GS-Extension-Library
##### 拓展库目录
* font：HPGCC自带3*5 ASCII字库包含 `Extended ASCII codes (decimal 128 ~ 255) ISO 8859-1`

* gpio：可用GPIO支持库，受硬件限制可用端口如下：`H7 H6 H3 H2 B2`

* misc：精简打印输出支持

* s3c2410：获取`PCLK / HCLK`频率

* graphics：图形绘制`点 / 线 / 圆 / 矩形 / 5*7 ASCII文字`

##### graphics库说明
使用graphics库中的`draw_text`方法时需要刷入带5*7 ASCII可显示字符的字库`hp39gs_2.22_ascii.bin`  

`hp39gs_2.22_ascii.bin` 字库带GB2312-80字库及 ASCII可显示区域[0x20 ~ 0x7E]字库  

##### graphics 测试样例
基础图形测试：  
``` c
draw_pixel(0, 0);
draw_pixel(1, 1);
draw_pixel(2, 2);

draw_pixel_ex(0, 4, 8);

draw_line(10, 10, 130, 63);

draw_rect(40,0,8,3);

draw_circle(64, 32, 10);
```
测试结果：  
![screen_graphics](https://raw.githubusercontent.com/Yanye0xFF/PictureBed/master/images/hp39extlib/screen_graphics.png)  

ASCII文字测试：  
``` c
draw_text(" !\"#$%&'()*+,-./0123", 0, 0);
draw_text("456789:;<=>?@ABCDEFG", 0, 8);
draw_text("HIJKLMNOPQRSTUVWXYZ[", 0, 16);
draw_text("\\]^_`abcdefghijklmno", 0, 24);
draw_text("pqrstuvwxyz{|}~", 0, 32);
```
测试结果：  
![screen_graphics](https://raw.githubusercontent.com/Yanye0xFF/PictureBed/master/images/hp39extlib/screen_ascii.png)  