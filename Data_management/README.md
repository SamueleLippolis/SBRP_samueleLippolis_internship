# READ ME 
Explanation of all the files 

- [READ ME](#read-me)
- [Files explanation](#files-explanation)
    - [Folders](#folders)
    - [Currents](#currents)
      - [C++ files](#c-files)
      - [Python files](#python-files)
    - [Past files](#past-files)
      - [C++ files](#c-files-1)
      - [Python files](#python-files-1)
- [Data explanation](#data-explanation)
    - [Distance matrix](#distance-matrix)
    - [Time matrix](#time-matrix)
    - [Nodes matrix](#nodes-matrix)
    - [Edge matrix](#edge-matrix)


# Files explanation

### Folders 

Past files: outdated files 

BUTTRIO: Buttrio data exctracted using the python files 


### Currents 

#### C++ files 

buildASolution: the problemInstance class now has 2 new variables related to the buses. There is a function that builds $n_{\text{numBusStops}}$ routes. Each of them goes from depot to a bus stop to all the clusters must be reached for the children taken in the bus stop. 

buildProblemInstances2: buildProblemInstances upgraded. The difference is the introduction of set/get/write methods for all matrix of the class

#### Python files 

importDataFromText3: upgrade of the importDataFromText2. Simply, it does all in one function 

importDataFromText-functions: all needed functions for importDataFromText3


### Past files 

#### C++ files 

importDistanceTimeMatrices: it imports the time and distance matrix from the folder BUTTRIO within the DATA MANAGEMENT folder, finally it prints data 
importNodes: it imports nodes data from the folder BUTTRIO within the DATA MANAGEMENT folder, finally it prints data
importEdges: it imports edges data from the folder BUTTRIO within the DATA MANAGEMENT folder, finally it prints data

importDistanceTimeMatrices2: upgrade of importDistanceTimeMatrix. The difference is that here there are cleaner e stright functions 

importData: given clean data in a folder, it stores them in 4 matrices (timeMatrix, distanceMatrix, edgesMatrix, nodesMatrix)

buildProblemInstances: given a path of the folder of the matrices and the name of the matrices, it builds an object of the class problemInstance with these 4 matrices 

#### Python files 

importDataFromText2: it exctracts rough data from folders DATA and it returns clen data in the same folder with the name of the comune (v 2 of 3)




# Data explanation 
Explaination of the clean data producted by the python function. 

### Distance matrix 
The first row contains indeces. 
Also the first column is just a tuple of indeces. 
The position $(i,j)$ contains the distance between the node $i$ and the node $j$.

An example of this matrix is \
nan,0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0 \
0.0,0.0,360.4,866.2,164.9,1053.0,775.6,2103.2,253.6,950.8,1999.2,965.2,230.0,1576.8,868.4,407.4,480.6,1896.7,772.3 \
1.0,314.8,0.0,1110.2,149.9,1235.5,958.0,2347.2,497.7,1133.3,2243.3,1147.6,474.0,1759.2,1050.9,589.8,724.6,2140.7,954.8 \
2.0,804.0,1048.0,0.0,898.1,1857.0,1579.6,1502.6,681.0,1754.8,1398.6,1769.2,574.0,2380.8,1553.9,1211.3,907.9,1296.0,1576.3 \
... \
16.0,1834.5,2078.5,1296.0,1928.6,2887.5,2610.1,253.7,1711.5,2785.3,149.7,2799.7,1604.5,3411.3,2584.4,2241.8,1306.3,0.0,2606.8 \
17.0,772.3,954.8,1638.5,937.3,280.7,590.2,2875.5,1026.0,318.7,2771.6,1079.9,1002.3,804.4,1102.5,831.7,1252.9,2669.0,0.0

### Time matrix 
The first row contains indeces.
Also the first column is just a tuple of indeces. 
The position $(i,j)$ contains the travel time from the node $i$ to the node $j$.

An example of this matrix is \
nan,0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0 \
0.0,0.0,49.2,80.0,24.7,93.2,78.4,204.3,30.0,98.6,181.7,87.5,20.7,174.2,90.1,44.1,62.7,168.2,69.8 \
1.0,48.8,0.0,128.7,26.3,126.4,111.6,253.0,78.7,131.8,230.4,120.7,69.4,207.4,123.3,77.3,111.4,216.9,103.0 \
2.0,80.8,128.9,0.0,100.5,174.0,159.2,167.6,76.9,179.4,145.0,168.3,60.1,255.0,151.7,124.9,109.6,131.5,150.6 \
... \
16.0,171.1,219.2,138.3,190.8,264.3,249.5,46.0,167.2,269.7,23.4,258.6,150.4,345.3,242.0,215.2,167.8,0.0,240.9 \
17.0,70.2,106.7,150.2,94.9,23.4,64.6,274.5,100.2,40.5,251.9,102.9,90.9,104.4,106.0,75.3,132.9,238.4,0.0

### Nodes matrix 
The nodes matrix has each row giving information about the node. 
The first, second and third column are the index of the node.
The fourth column is the latitude and the fifth column the longitude. 
The sixth column is the node kind.
The seventh column is an integer that represents how many children there are in this node that must be bring to the first cluster. 
The eighth columns is an integer that represents how many children there are in this node that must be bring to the second cluster. 
The ninth columns is an integer that represents how many children there are in this node that must be bring to the third cluster.  
The tenth columns is an integer that represents how many children there are in this node that must be bring to the fourth cluster. 

An example of this matrix is \
0,0,0,13.33352521881336,46.010049138194574,deposito,0,0,0,0 \
1,1,1,13.333070548499375,46.011592135492116,fermata,2,0,0,0 \
2,2,2,13.332481034239262,46.00685608068721,fermata,0,17,0,0 \
... \
13,13,13,13.326947840304118,46.01778681721185,fermata,0,8,0,0 \
14,14,14,13.329811696254819,46.015173106898395,fermata,4,7,0,0 \
15,15,15,13.331240309217243,46.008979472861995,fermata,0,2,0,0 \
16,16,16,13.337971,46.000032,cluster,0,0,0,0 \
17,17,17,13.337188,46.017635,cluster,0,0,0,0


### Edge matrix
In the edge matrix the first row represents the labels.
From the second row on each row represents the data of an edge. 
The first column is the source node (from where the directed edge starts).
The second column is the target node (where the directed edge arrives).
The thrid column is the weight (the travel distance from the source to the target).
The fourth columns is the time (the travle time from the source to the targer).

An example of this matrix is the following: \
source,target,weight,time \
0,1,174.43590656723543,5.814530218907848 \
0,2,364.47050382091714,12.14901679403057 \
0,3,252.11573927177233,8.403857975725744 \
0,4,1210.2216076312898,40.34072025437633 \
0,5,900.8508572996445,30.028361909988153 \
0,6,1384.5418396285968,46.15139465428656 \
0,7,377.41469049361956,12.580489683120652 \
0,8,1032.572500691824,34.41908335639413 \
0,9,1333.271911473912,44.4423970491304 \
0,10,1222.6955972282178,40.75651990760726 \
0,11,436.12062139637516,14.537354046545838 \
0,12,1197.5037531100245,39.91679177033415 \
0,13,1111.675919296485,37.0558639765495 \
0,14,691.2829224784504,23.04276408261501 \
0,15,279.18901352221,9.306300450740334 \
1,2,1110.2,128.7 \
1,3,149.9,26.3 \
1,4,1235.5,126.4 \
1,5,958.0,111.6 \
1,6,2347.2,253.0 \
1,7,497.7,78.7 \
1,8,1133.3,131.8 \
1,9,2243.3,230.4 \
... \
15,11,361.2,54.9 \
15,12,2055.7,235.3 \
15,13,1516.7,147.9 \
15,14,886.3,105.2 \
15,16,1305.0,131.7 \
15,17,1251.3,130.9 \
16,17,1305.0,131.7 \
16,0,0.0,0.0 \
17,16,1306.3,167.8 \
17,0,0.0,0.0