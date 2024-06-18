# READ ME 
Explanation of all the files 

# Files explanation

### Folders 

BUTTRIO: Buttrio data exctracted using the python files 

### Python files 

importDataFromText2: it exctracts rough data from folders DATA and it returns clen data in the same folder with the name of the comune (v 2 of 3)
importDataFromText3: upgrade of the importDataFromText2. Simply, it does all in one function 

### C++ files 

importDistanceTimeMatrices: it imports the time and distance matrix from the folder BUTTRIO within the DATA MANAGEMENT folder, finally it prints data 
importNodes: it imports nodes data from the folder BUTTRIO within the DATA MANAGEMENT folder, finally it prints data
importEdges: it imports edges data from the folder BUTTRIO within the DATA MANAGEMENT folder, finally it prints data

importDistanceTimeMatrices2: upgrade of importDistanceTimeMatrix. The difference is that here there are cleaner e stright functions 

importData: given clean data in a folder, it stores them in 4 matrices (timeMatrix, distanceMatrix, edgesMatrix, nodesMatrix)
