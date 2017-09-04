# 9/9 contest
### tree
#### input
* random generate tree
  * code : random-generate.cpp
  * file : input01~input05, input17~input20
* straight line
  * code : line.cpp
  * file : input06~input07
* flower
  * code : flower.cpp
  * file : input08~input10, input16
* caterpillar
  * code : caterpillar.cpp
  * file : input11~input12
* broom
  * code : broom.cpp
  * file : input13~input14
* perfect binary tree
  * code : perfect2t.cpp
  * file : input15
#### solution code
* complexity n*k : treeDP.cpp
* complexity n^2 : treeDP-n-square.cpp
### triangle
#### input
* regular polygon
  * file : input01
* encircle polygon
  * code : Encircle.cpp
  * file : input02~input10
(缺隨機凸包)
#### convex hull checker
To check if input file is indeed a convex hull. If not, output "NONO"
* code : tuboChecker.cpp
#### max rooted-triangle checker
To check if the algorithm to find the max triangle from a fixed root is correct.
* code : maxTriChecker.cpp
#### solution code
* complexity n*lg(n) : vahideh.cpp
* complexity n^3 : enum.cpp
* complexity n^2 : nsquare.cpp (還沒寫)
#### fake solution code (都還沒寫)
* linear-fake.cpp
  * [a linear time solution on web](https://stackoverflow.com/questions/1621364/how-to-find-largest-triangle-in-convex-hull-aside-from-brute-force-search)
* find-farest-root-fake.cpp
