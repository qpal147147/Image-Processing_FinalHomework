# 影像處理期末作業
所有圖片皆使用[免費圖庫](https://www.pexels.com/)照片  
紅眼照片來源 [Wiki](https://commons.wikimedia.org/wiki/File:BoldRedEye.JPG)  
使用[opencv 4.1.1](https://opencv.org/)搭配C++進行處理  
  
編號|實作功能|說明
----|:-----:|----
1   | 描邊   | 針對圖片物體描繪邊框線條
2   | 浮雕、雕刻 | 對圖片轉化成浮雕和雕刻的模樣
3   | 特定範圍去背 | 選取特定物體後進行去背
4   | 人臉偵測 | 偵測人臉
5   | 素描風 | 將圖片轉成素描風格
6   | 去浮水印 | 將畫面上的浮水印進行修復與消除
7   | 毛玻璃 | 將圖片轉成毛玻璃風格
8   | 縮放、明暗、旋轉 | 三合一功能，不用為了使用某一功能而重新處理
9   | 消除紅眼 | 將照片紅眼的影響進行處理與修復
10   | AsciiArt | 將圖片轉成ASCII風格
  
- ### 描邊  
原始圖案|處理後
-------|------
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/dog.jpeg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%8F%8F%E9%82%8A/After.jpg)
  
- ### 浮雕、雕刻
原始圖案|浮雕|雕刻 
------|:-----:|----
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/cat.jpeg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%B5%AE%E9%9B%95_%E9%9B%95%E5%88%BB/Relief.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%B5%AE%E9%9B%95_%E9%9B%95%E5%88%BB/Sculpture.jpg)
  
- ### 特定範圍去背
原始圖案|Mask|處理後 
------|:-----:|----
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E7%89%B9%E5%AE%9A%E7%AF%84%E5%9C%8D%E5%8E%BB%E8%83%8C/Before.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E7%89%B9%E5%AE%9A%E7%AF%84%E5%9C%8D%E5%8E%BB%E8%83%8C/Mask.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E7%89%B9%E5%AE%9A%E7%AF%84%E5%9C%8D%E5%8E%BB%E8%83%8C/After.jpg)
  
- ### 人臉偵測
原始圖案|處理後
-------|------
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/face.jpeg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E4%BA%BA%E8%87%89%E5%81%B5%E6%B8%AC/After.jpg)
  
- ### 素描風
原始圖案|處理後
-------|------
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/people.jpeg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E7%B4%A0%E6%8F%8F%E9%A2%A8/After.jpg)
  
- ### 去浮水印
原始圖案|Mask|處理後
------|:-----:|----
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/watermark.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%B6%88%E9%99%A4%E6%B5%AE%E6%B0%B4%E5%8D%B0/Mask.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%B6%88%E9%99%A4%E6%B5%AE%E6%B0%B4%E5%8D%B0/After.jpg)
  
- ### 毛玻璃  
原始圖案|處理後
-------|------
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/landscape.jpeg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%AF%9B%E7%8E%BB%E7%92%83/After.jpg)
  
- ### 縮放、明暗、旋轉
原始圖案|縮放|明暗|旋轉
------|:-----:|:-----:|----
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/store.jpeg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E7%B8%AE%E6%94%BE_%E6%98%8E%E6%9A%97_%E6%97%8B%E8%BD%89/Zoom.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E7%B8%AE%E6%94%BE_%E6%98%8E%E6%9A%97_%E6%97%8B%E8%BD%89/Brightness.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E7%B8%AE%E6%94%BE_%E6%98%8E%E6%9A%97_%E6%97%8B%E8%BD%89/Spin.jpg)
  
- ### 消除紅眼
原始圖案|Mask|處理後
------|:-----:|----
![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/img%20%26%20mod/image/cat.jpeg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%B5%AE%E9%9B%95_%E9%9B%95%E5%88%BB/Relief.jpg)|![image](https://raw.githubusercontent.com/qpal147147/Image-Processing_FinalHomework/master/SampleImage/%E6%B5%AE%E9%9B%95_%E9%9B%95%E5%88%BB/Sculpture.jpg)
