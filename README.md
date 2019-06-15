# 2019-spring-gt-N26070083

## 圖論期末project   作者:劉彥欣   學號:N26070083

功能 : 輸入一conncted graph，並視為無向圖處理，每個點都能被走到的情況下，找出最短路徑。  

提醒 :   
1、使用套件讀檔，input檔的格式要注意，多一個空格可能導致讀取錯誤。  

2、套件讀檔，Vertex會依照字母順序(a.b.c.d)自動排列，e.g.若b出現於a之前，會導致程式出錯  

3、套件的讀檔至多只能吃進10個Vertex。  

4、能解出兩個Vertex中有多條連線，以及Vertex本身有loop的狀況。  

5、run.sh 能一次測多筆測資，測資檔名不能含空白  

	   
一、解題邏輯  

1、判斷輸入是否為一conncted graph，不是的話就無解，終止程式。  

2、找出任兩點之間的最短路徑。  

3、找出圖上所有奇點。  

4、把這些奇點做最小權重匹配，使用奇點之間的最短路徑當作權重。  

5、把額外的邊加在原圖上，使此圖能找得到尤拉環。  

6、找出尤拉環，即得中國郵差路徑。  
參考網站:http://www.csie.ntnu.edu.tw/~u91029/Circuit.html?fbclid=IwAR1_EBUz5agbtVSI6hlIsDrIqSJ0TqxYgwYowt0Kr2qpTR7fCvfp5dkqeB8#4

二、程式碼實作與解釋

1、創建無向圖 : 使用套件讀取input file，並根據input的有向圖network nm，使用add_switch與connected的功能，重新建立一個新的無向圖network nm2，
方法是把原本的單向連接改成雙向連接(e.g.原本的edge為a->c，在新的network中建立成兩條a->c與c->a)以此確保使用套件計算最短路徑時，
兩個方向都能被找到，不會造成a->c有最短路徑，c->a卻沒有最短路徑的情況發生。

2、判斷是否為conncted graph ： 使用套件中的find_paths找出任兩點之間的所有路徑，若有任兩點間找不到任何路徑，表示此圖並非conncted graph。

3、出任兩點之間的最短路徑  :  在步驟1使用find_paths尋找任兩點之間的所有路徑時，紀錄任兩點間的最短路徑，若長度一樣，則使用Vertex的順序較前面的當最短路徑
(e.g. a->c->e 和 a->b->e ，則選擇 a->b->e 最為a、e兩點間的最短路徑)
在此步驟同時也建立最短路徑長的二維vector矩陣，方便第4步驟球最小全匹配時奇點間的最短路徑取用。

4、找出奇點 : 透過尋訪原圖nm的edge，使用「自定義的資料結構」將Vertex和Edge的關係記下來，原因是套件吃進來的Vertex中並沒辦法使用指標找到自己連到edge，後面做其他運算時較為麻煩。
記下關係的同時，也計算出每個Vertex進出自己的edge數，找出奇點且存成vector。

5、將奇點做最小權重匹配 : 兩個奇點為一組，找出所有組合中總權重最小的組合，使用這種將奇點連接的方式消除奇點，整個圖就能產生尤拉環。

6、把額外的邊加在原圖上 : 這些將奇點連接的額外的邊，加到剛剛自定義的資料結構中，方便計算尤拉環。

7、找到尤拉環 : (參考網址:https://iampandiyan.blogspot.com/2013/10/c-program-to-find-euler-path-or-euler.html?fbclid=IwAR18ZRPPpJMIkgESvm505wKEd6MKIyh13tDeSkij1SEGcgKQr3Vr_FASW6Q)

三、執行結果

輸出 postman.txt ，裡面包含最短路徑的走法。
例如 :
Path: a->b->c->d->e->a->>b->f->a

其中的"->"表示該edge被走過一次，而"->>"則代表這是額外加入的edge，也能想像成這條edge被通過第二次以上。

四、使用方式

將測資放入testbench資料夾，執行 run.sh 即可。
